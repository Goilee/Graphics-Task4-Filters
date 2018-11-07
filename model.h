#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>

class Controller;

class Model : public QObject
{
    Q_OBJECT
private /*fields*/:
    QImage src_image;
    QImage dst_image;
    friend Controller;

public /*methods*/:
    explicit Model(QImage src_image, QObject *parent = nullptr);

private /*methods*/:
    void setSRCimage(QImage image);
    void setDSTimage(QImage image);

signals:
    void SRCimageChanged(QImage src_image);
    void DSRimageChanged(QImage dst_image);

public slots:
};

#endif // MODEL_H
