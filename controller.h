#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "mask.h"
#include "maskparamdialog.h"

class Controller : public QObject
{
    Q_OBJECT
private /*fields*/:
    Model *model;
    Mask mask;
    MaskParamDialog *mask_dialog;


public /*methods*/:
    explicit Controller(Model *model, QObject *parent = nullptr);
    ~Controller();

signals:

public slots:
    void newFile();
    void saveToFile();
    void cpSRCtoDST();
    void cpDSTtoSRC();
    void grayscale();
    void edgeDetection();
    void blur();
    void sharpen();
    void identical();
    void negative();
    void embossing();
    void watercolor();
    void gamma();
    void matrixTransmition();

private slots:
    void applyMatrixTransmition();
    void applyEdgeDetection();
};

#endif // CONTROLLER_H
