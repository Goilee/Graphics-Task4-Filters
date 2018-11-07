#include "photoshop.h"

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

    QImage matrixTransmition(QImage image)
    {
        // TODO
        return image;
    }
}
