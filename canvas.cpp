#include "canvas.h"
#include <QPainter>

Canvas::Canvas(Model *model, QWidget *parent) :
    QWidget(parent),
    model(model), image(QImage())
{

}

Canvas::~Canvas()
{

}

void Canvas::paintEvent(QPaintEvent *)
{
    // TODO
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(0, 0, 255)));
    painter.drawRect(0, 0, this->width(), this->height());
}
