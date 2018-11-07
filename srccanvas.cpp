#include "srccanvas.h"

SrcCanvas::SrcCanvas(Model *model, QWidget *parent) : Canvas(model, parent)
{
    this->updateImage();
}

SrcCanvas::~SrcCanvas()
{

}

void SrcCanvas::updateImage()
{
    this->image = this->model->getSRCimage();
    this->image_width = this->image.width();
    this->image_height = this->image.height();
    this->update();
}
