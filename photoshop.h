#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include <QImage>

namespace photoshop
{
    QImage Grayscale(QImage image);
    QImage EdgeDetection(QImage image);
    QImage Blur(QImage image);
    QImage Sharpen(QImage image);
    QImage Identical(QImage image);
    QImage Negative(QImage image);
    QImage Embossing(QImage image);
    QImage Watercolor(QImage image);
    QImage Gamma(QImage image);
    QImage MatrixTransmition(QImage image);
}

#endif // PHOTOSHOP_H
