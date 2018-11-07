#include "gammadialog.h"
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QLabel>

QLineEdit * createGammaInput(QString initial_val)
{
    QDoubleValidator *validator = new QDoubleValidator();
    validator->setNotation(QDoubleValidator::ScientificNotation);
    validator->setRange(0, 100);
    QLineEdit *line_edit = new QLineEdit(initial_val);
    line_edit->setValidator(validator);
    return line_edit;
}

GammaDialog::GammaDialog() :
    gamma_slider(new QSlider())
{
    this->gamma_slider->setMinimum(1);
    this->gamma_slider->setMaximum(100);
    this->gamma_slider->setValue(50);
    connect(this->gamma_slider, SIGNAL(valueChanged(int)), this, SLOT(applySlider()));
    this->gamma_edit = createGammaInput(QString::number(50));
    connect(this->gamma_edit, SIGNAL(textEdited(QString)), this, SLOT(applyEdit(QString)));
    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new QLabel(QString("gamma")));
    layout->addWidget(this->gamma_slider);
    layout->addWidget(this->gamma_edit);
    this->setLayout(layout);
}

void GammaDialog::applySlider()
{
    int gamma_i = this->gamma_slider->value();
    double gamma = (double) gamma_i / 10;
    this->gamma_edit->setText(QString::number(gamma));
    emit this->applied(gamma);
}

void GammaDialog::applyEdit()
{
    double gamma = this->gamma_edit->text().toDouble();
    this->gamma_slider->setValue((int) (gamma * 10 + 0.5));
}
