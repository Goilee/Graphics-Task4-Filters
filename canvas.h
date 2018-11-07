#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include "model.h"

class Canvas : public QWidget
{
    Q_OBJECT
protected /*fields*/:
    Model *model;
    QImage image;
    int image_width;
    int image_height;

public /*methods*/:
    explicit Canvas(Model *model, QWidget *parent = nullptr);
    virtual ~Canvas() override;

protected /*methods*/:
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:
    virtual void updateImage() = 0;
};

#endif // CANVAS_H
