#ifndef DSTCANVAS_H
#define DSTCANVAS_H

#include "canvas.h"

class DstCanvas : public Canvas
{
    Q_OBJECT
public:
    explicit DstCanvas(Model *model, QWidget *parent = nullptr);
    ~DstCanvas() override;

signals:

public slots:
    void updateImage() override;
};

#endif // DSTCANVAS_H
