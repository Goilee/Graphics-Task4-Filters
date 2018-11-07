#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include "model.h"

class Canvas : public QWidget
{
    Q_OBJECT
private /*fields*/:
    Model *model;
    QImage image;

public /*methods*/:
    explicit Canvas(Model *model, QWidget *parent = nullptr);
    virtual ~Canvas() override;

private /*methods*/:
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:
    virtual void updateImage() = 0;
};

#endif // CANVAS_H