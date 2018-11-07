#include "canvas.h"
#include <QPainter>

Canvas::Canvas(Model *model, QWidget *parent) :
    QWidget(parent),
    model(model), image(QImage())
{
    this->image_width = 0;
    this->image_height = 0;
}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    // TODO
    QPainter painter(this);

    int width = this->width();
    int height = this->height();

    int x, y, target_x, target_y, target_width, target_height;
    if (width > this->image_width)
    {
        x = (width - this->image_width) / 2;
        target_x = 0;
        target_width = this->image_width;
    }
    else  // if (width <= this>image_width)
    {
        x = 0;
        target_x = (this->image_width - width) / 2;
        target_width = width;
    }
    if (height > this->image_height)
    {
        y = (height - this->image_height) / 2;
        target_y = 0;
        target_height = this->image_height;
    }
    else  // if (height <= this-> image_height)
    {
        y = 0;
        target_y = (this->image_height - height) / 2;
        target_height = height;
    }

    painter.setBrush(QBrush(QColor(0, 0, 255)));
    painter.drawRect(0, 0, width, height);
    painter.drawImage(QPoint(x, y), this->image, QRect(target_x, target_y, target_width, target_height));
}
