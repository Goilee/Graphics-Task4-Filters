#ifndef PHOTOSHOP_H
#define PHOTOSHOP_H

#include <QImage>
#include "mask.h"

namespace photoshop
{
    QImage grayscale(QImage image);
    QImage edgeDetection(QImage image);
    QImage blur(QImage image);
    QImage sharpen(QImage image);
    QImage identical(QImage image);
    QImage negative(QImage image);
    QImage embossing(QImage image);
    QImage watercolor(QImage image);
    QImage gamma(QImage image);
    QImage matrixTransmition(QImage image, Mask mask);
}

#endif // PHOTOSHOP_H
