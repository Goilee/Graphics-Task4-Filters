#ifndef EDGEDETECTIONDIALOG_H
#define EDGEDETECTIONDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLineEdit>

class EdgeDetectionDialog : public QDialog
{
    Q_OBJECT

private /*fields*/:
    QSlider *red_slider;
    QSlider *green_slider;
    QSlider *blue_slider;
    QLineEdit *red_edit;
    QLineEdit *green_edit;
    QLineEdit *blue_edit;

public /*methods*/:
    EdgeDetectionDialog();

signals:
    void applied(int red_threshold, int greeen_threshold, int blue_threshold);

public slots:
    void applyRedSlider();
    void applyGreenSlider();
    void applyBlueSlider();
    void applyRedEdit(QString text);
    void applyGreenEdit(QString text);
    void applyBlueEdit(QString text);
};

#endif // EDGEDETECTIONDIALOG_H
