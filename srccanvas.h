#ifndef SRCCANVAS_H
#define SRCCANVAS_H

#include "canvas.h"

class SrcCanvas : public Canvas
{
    Q_OBJECT
public:
    explicit SrcCanvas(Model *model, QWidget *parent = nullptr);
    ~SrcCanvas() override;

signals:

public slots:
    void updateImage() override;
};

#endif // CANVAS_H
