#include "photoshop.h"

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

    QImage edgeDetection(QImage image)
    {
        // TODO
        return image;
    }

    QImage blur(QImage image)
    {
        // TODO
        return image;
    }

    QImage sharpen(QImage image)
    {
        // TODO
        return image;
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
        // TODO
        return image;
    }

    QImage watercolor(QImage image)
    {
        // TODO
        return image;
    }

    QImage gamma(QImage image)
    {
        // TODO
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
