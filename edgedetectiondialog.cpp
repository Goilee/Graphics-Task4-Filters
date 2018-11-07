#include "edgedetectiondialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

QLineEdit * createByteInput(QString initial_val)
{
    QIntValidator *validator = new QIntValidator();
    validator->setRange(0, 255);
    QLineEdit *line_edit = new QLineEdit(initial_val);
    line_edit->setValidator(validator);
    return line_edit;
}

EdgeDetectionDialog::EdgeDetectionDialog() :
    QDialog(),
    red_slider(new QSlider()),
    green_slider(new QSlider()),
    blue_slider(new QSlider())
{
    this->red_slider->setMinimum(0);
    this->red_slider->setMaximum(255);
    this->red_slider->setValue(128);
    connect(this->red_slider, SIGNAL(valueChanged(int)), this, SLOT(applyRedSlider()));
    this->red_edit = createByteInput(QString::number(128));
    connect(this->red_edit, SIGNAL(textEdited(QString)), this, SLOT(applyRedEdit(QString)));
    QLayout *red_slider_layout = new QHBoxLayout();
    red_slider_layout->addWidget(new QLabel(QString("red")));
    red_slider_layout->addWidget(this->red_slider);
    red_slider_layout->addWidget(this->red_edit);
    QWidget *red_slider_widget = new QWidget();
    red_slider_widget->setLayout(red_slider_layout);

    this->green_slider->setMinimum(0);
    this->green_slider->setMaximum(255);
    this->green_slider->setValue(128);
    connect(this->green_slider, SIGNAL(valueChanged(int)), this, SLOT(applyGreenSlider()));
    this->green_edit = createByteInput(QString::number(128));
    connect(this->green_edit, SIGNAL(textEdited(QString)), this, SLOT(applyGreenEdit(QString)));
    QLayout *green_slider_layout = new QHBoxLayout();
    green_slider_layout->addWidget(new QLabel(QString("green")));
    green_slider_layout->addWidget(this->green_slider);
    green_slider_layout->addWidget(this->green_edit);
    QWidget *green_slider_widget = new QWidget();
    green_slider_widget->setLayout(green_slider_layout);

    this->blue_slider->setMinimum(0);
    this->blue_slider->setMaximum(255);
    this->blue_slider->setValue(128);
    connect(this->blue_slider, SIGNAL(valueChanged(int)), this, SLOT(applyBlueSlider()));
    this->blue_edit = createByteInput(QString::number(128));
    connect(this->blue_edit, SIGNAL(textEdited(QString)), this, SLOT(applyBlueEdit(QString)));
    QLayout *blue_slider_layout = new QHBoxLayout();
    blue_slider_layout->addWidget(new QLabel(QString("blue")));
    blue_slider_layout->addWidget(this->blue_slider);
    blue_slider_layout->addWidget(this->blue_edit);
    QWidget *blue_slider_widget = new QWidget();
    blue_slider_widget->setLayout(blue_slider_layout);

    QLayout *base_layout = new QVBoxLayout();
    base_layout->addWidget(red_slider_widget);
    base_layout->addWidget(green_slider_widget);
    base_layout->addWidget(blue_slider_widget);

    this->setLayout(base_layout);

    emit this->applied(this->red_slider->value(), this->green_slider->value(), this->blue_slider->value());
}

void EdgeDetectionDialog::applyRedSlider()
{
    int red = this->red_slider->value();
    this->red_edit->setText(QString::number(red));
    emit this->applied(red, this->green_slider->value(), this->blue_slider->value());
}

void EdgeDetectionDialog::applyGreenSlider()
{
    int green = this->green_slider->value();
    this->green_edit->setText(QString::number(green));
    emit this->applied(this->red_slider->value(), green, this->blue_slider->value());
}

void EdgeDetectionDialog::applyBlueSlider()
{
    int blue = this->blue_slider->value();
    this->blue_edit->setText(QString::number(blue));
    emit this->applied(this->red_slider->value(), this->green_slider->value(), blue);
}

void EdgeDetectionDialog::applyRedEdit(QString text)
{
    this->red_slider->setValue(text.toInt());
}

void EdgeDetectionDialog::applyGreenEdit(QString text)
{
    this->green_slider->setValue(text.toInt());
}

void EdgeDetectionDialog::applyBlueEdit(QString text)
{
    this->blue_slider->setValue(text.toInt());
}
