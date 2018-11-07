#include "dstcanvas.h"

DstCanvas::DstCanvas(Model *model, QWidget *parent) : Canvas(model, parent)
{
    connect(this->model, SIGNAL(DSTimageChanged()), this, SLOT(updateImage()));
    this->updateImage();
}

DstCanvas::~DstCanvas()
{

}

void DstCanvas::updateImage()
{
    this->image = this->model->getDSTimage();
    this->image_width = this->image.width();
    this->image_height = this->image.height();
    this->update();
}
