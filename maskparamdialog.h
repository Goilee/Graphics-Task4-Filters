#ifndef MASKPARAMDIALOG_H
#define MASKPARAMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "mask.h"

class MaskParamDialog : public QDialog
{
    Q_OBJECT

private /*fields*/:
    Mask *mask;
    QLineEdit *matrix_edits[3][3];
    QLineEdit *norm_edit;
    QLineEdit *shift_edits[3];

public /*methods*/:
    MaskParamDialog(Mask *mask);

signals:
    void applied();

private /*methods*/:
    double autoNormCalc();

private slots:
    void autoNorm();
    void accept();
    void reject();
    void apply();
};

#endif // MASKPARAMDIALOG_H
