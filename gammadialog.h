#ifndef GAMMADIALOG_H
#define GAMMADIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLineEdit>

class GammaDialog : public QDialog
{
    Q_OBJECT

private:
    double gamma;
    QSlider *gamma_slider;
    QLineEdit *gamma_edit;

public:
    GammaDialog();

signals:
    void applied(double gamma);

public slots:
    void applySlider();
    void applyEdit();
};

#endif // GAMMADIALOG_H
