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
    QImage getSRCimage();
    QImage getDSTimage();

private /*methods*/:
    void setSRCimage(QImage image);
    void setDSTimage(QImage image);
    void newModel(QImage image);

signals:
    void SRCimageChanged();
    void DSTimageChanged();

public slots:
};

#endif // MODEL_H
