#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
private /*fields*/:
    Model *model;

public /*methods*/:
    explicit Controller(Model *model, QObject *parent = nullptr);
    ~Controller();

signals:

public slots:
    void newFile();
    void saveToFile();
    void CpSRCtoDST();
    void CpDSTtoSRC();
    void Grayscale();
    void EdgeDetection();
    void Blur();
    void Sharpen();
    void Identical();
    void Negative();
    void Embossing();
    void Watercolor();
    void Gamma();
    void MatrixTransmition();
};

#endif // CONTROLLER_H
