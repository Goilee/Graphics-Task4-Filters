#include "model.h"

Model::Model(QImage src_image, QObject *parent) :
    QObject(parent),
    src_image(src_image), dst_image(QImage())
{

}

void Model::setSRCimage(QImage image)
{
    this->src_image = image;
}

void Model::setDSTimage(QImage image)
{
    this->dst_image = image;
}
