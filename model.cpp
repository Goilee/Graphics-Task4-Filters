#include "model.h"

Model::Model(QImage src_image, QObject *parent) :
    QObject(parent),
    src_image(src_image), dst_image(QImage())
{

}

void Model::newModel(QImage image)
{
    this->src_image = image;
    this->dst_image = QImage();
    emit this->SRCimageChanged();
    emit this->DSTimageChanged();
}

QImage Model::getSRCimage()
{
    return this->src_image;
}

QImage Model::getDSTimage()
{
    return this->dst_image;
}

void Model::setSRCimage(QImage image)
{
    this->src_image = image;
    emit this->SRCimageChanged();
}

void Model::setDSTimage(QImage image)
{
    this->dst_image = image;
    emit this->DSTimageChanged();
}
