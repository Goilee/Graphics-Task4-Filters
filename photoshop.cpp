#include "photoshop.h"
#include <math.h>

int doubleToColorComponent(double val)
{
    if (val > 255)
    {
        return 255;
    }
    else if (val < 0)
    {
        return 0;
    }
    else return (int) (val + 0.5);
}

namespace photoshop
{
    QImage grayscale(QImage image)
    {
        int width = image.width();
        int height = image.height();
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                QColor color = image.pixelColor(x, y);
                int new_rgb = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
                if (new_rgb < 0)
                {
                    new_rgb = 0;
                }
                else if (new_rgb > 255)
                {
                    new_rgb = 255;
                }
                image.setPixelColor(x, y, QColor(new_rgb, new_rgb, new_rgb));
            }
        }
        return image;
    }

    QImage edgeDetection(QImage image, int red_threshold, int green_threshold, int blue_threshold)
    {
        Mask mask = Mask();
        mask.set(-1, -1, 0);
        mask.set(-1, 0, -1);
        mask.set(-1, 1, 0);
        mask.set(0, -1, -1);
        mask.set(0, 0, 4);
        mask.set(0, 1, -1);
        mask.set(1, -1, 0);
        mask.set(1, 0, -1);
        mask.set(1, 1, 0);
        mask.setNorm(1);
        mask.setRedShift(0);
        mask.setGreenShift(0);
        mask.setBlueShift(0);
        QImage result = photoshop::matrixTransmition(image, mask);

        int height = result.height();
        int width = result.width();
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                QColor color = result.pixelColor(x, y);
                if (color.red() > red_threshold)
                {
                    color.setRed(255);
                }
                else
                {
                    color.setRed(0);
                }
                if (color.green() > green_threshold)
                {
                    color.setGreen(255);
                }
                else
                {
                    color.setGreen(0);
                }
                if (color.blue() > blue_threshold)
                {
                    color.setBlue(255);
                }
                else
                {
                    color.setBlue(0);
                }
                result.setPixelColor(x, y, color);
            }
        }

        return result;
    }

    QImage blur(QImage image)
    {
        Mask mask = Mask();
        mask.set(-1, -1, 1);
        mask.set(-1, 0, 2);
        mask.set(-1, 1, 1);
        mask.set(0, -1, 2);
        mask.set(0, 0, 4);
        mask.set(0, 1, 2);
        mask.set(1, -1, 1);
        mask.set(1, 0, 2);
        mask.set(1, 1, 1);
        mask.autoNorm();
        mask.setRedShift(0);
        mask.setGreenShift(0);
        mask.setBlueShift(0);
        return photoshop::matrixTransmition(image, mask);
    }

    QImage sharpen(QImage image)
    {
        Mask mask = Mask();
        mask.set(-1, -1, 0);
        mask.set(-1, 0, -1);
        mask.set(-1, 1, 0);
        mask.set(0, -1, -1);
        mask.set(0, 0, 5);
        mask.set(0, 1, -1);
        mask.set(1, -1, 0);
        mask.set(1, 0, -1);
        mask.set(1, 1, 0);
        mask.autoNorm();
        mask.setRedShift(0);
        mask.setGreenShift(0);
        mask.setBlueShift(0);
        return photoshop::matrixTransmition(image, mask);
    }

    QImage identical(QImage image)
    {
        return image;
    }

    QImage negative(QImage image)
    {
        int width = image.width();
        int height = image.height();
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                QColor color = image.pixelColor(x, y);
                int red = 255 - color.red();
                int green = 255 - color.green();
                int blue = 255 - color.blue();
                image.setPixelColor(x, y, QColor(red, green, blue));
            }
        }
        return image;
    }

    QImage embossing(QImage image)
    {
        Mask mask = Mask();
        mask.set(-1, -1, 0);
        mask.set(-1, 0, -1);
        mask.set(-1, 1, 0);
        mask.set(0, -1, 1);
        mask.set(0, 0, 0);
        mask.set(0, 1, -1);
        mask.set(1, -1, 0);
        mask.set(1, 0, 1);
        mask.set(1, 1, 0);
        mask.setNorm(1);
        mask.setRedShift(128);
        mask.setGreenShift(128);
        mask.setBlueShift(128);
        return photoshop::grayscale(photoshop::matrixTransmition(image, mask));
    }

    QImage watercolor(QImage image)
    {
        QImage result = QImage(image);
        int width = image.width();
        int height = image.height();
        for (int y = 2; y < height - 2; y++)
        {
            for (int x = 2; x < width - 2; x++)
            {
                std::vector<int> red_list = std::vector<int>();
                std::vector<int> green_list = std::vector<int>();
                std::vector<int> blue_list = std::vector<int>();
                for (int i = -2; i < 3; i++)
                {
                    for (int j = -2; j < 3; j++)
                    {
                        QColor color = image.pixelColor(x + i, y + j);
                        red_list.push_back(color.red());
                        green_list.push_back(color.green());
                        blue_list.push_back(color.blue());
                    }
                }
                std::sort(red_list.begin(), red_list.end());
                std::sort(green_list.begin(), green_list.end());
                std::sort(blue_list.begin(), blue_list.end());

                result.setPixelColor(x, y, QColor(red_list.at(12), green_list.at(12), blue_list.at(12)));
            }
        }

        return photoshop::sharpen(result);
    }

    QImage gamma(QImage image, double gamma)
    {
        int width = image.width();
        int height = image.height();
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                QColor color = image.pixelColor(x, y);
                int red = (int) (pow((double)color.red() / 255, gamma) * 255 + 0.5);
                int green = (int) (pow((double)color.green() / 255, gamma) * 255 + 0.5);
                int blue = (int) (pow((double)color.blue() / 255, gamma) * 255 + 0.5);
                image.setPixelColor(x, y, QColor(red, green, blue));
            }
        }
        return image;
    }

    QImage matrixTransmition(QImage image, Mask mask)
    {
        int width = image.width();
        int height = image.height();
        QImage result = QImage(image);
        for (int y = 1; y < height - 1; y++)
        {
            for (int x = 1; x < width - 1; x++)  // без краев
            {
                double red = 0;
                double green = 0;
                double blue = 0;
                for (int i = -1; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        QColor color = image.pixelColor(x + i, y + j);
                        double k = mask.at(i, j);
                        red += color.red() * k;
                        green += color.green() * k;
                        blue += color.blue() * k;
                    }
                }
                double norm = mask.norm();
                red = red / norm + mask.red_shift();
                green = green / norm + mask.green_shift();
                blue = blue / norm + mask.blue_shift();
                result.setPixelColor(x, y, QColor(doubleToColorComponent(red), doubleToColorComponent(green), doubleToColorComponent(blue)));
            }
        }
        /*for (int x = 0; x < width; x++)  // y = 0
        {
            double red = 0;
            double green = 0;
            double blue = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    QColor color = image.pixelColor(x + i, j);
                    double k = mask.at(i, j);
                    red += color.red() * k;
                    green += color.green() * k;
                    blue += color.blue() * k;
                }
            }
            double summ = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    summ += mask.at(i, j);
                }
            }
            double norm = mask.norm() * (summ - mask.at(-1, -1) - mask.at(0, -1) - mask.at(1, -1)) / summ;
            red = red / norm + mask.red_shift();
            green = green / norm + mask.green_shift();
            blue = blue / norm + mask.blue_shift();
            result.setPixelColor(x, 0, QColor(doubleToColorComponent(red), doubleToColorComponent(green), doubleToColorComponent(blue)));
        }*/
        return result;
    }
}
