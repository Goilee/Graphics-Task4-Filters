#include "controller.h"
#include "photoshop.h"
#include <QFileDialog>
#include <QMessageBox>

Controller::Controller(Model *model, QObject *parent) :
    QObject(parent),
    model(model)
{

}

Controller::~Controller()
{

}

void Controller::newFile()
{
    QImage image = QImage(QFileDialog::getOpenFileName(nullptr,
                                                tr("Open file"),
                                                QString(),
                                                tr("Images (*.png *.jpg *.gif *.bmp)")));
    if (!image.isNull())
    {
        this->model->newModel(image);
    }
}

void Controller::saveToFile()
{
    // TODO
    QImage image = this->model->getDSTimage();
    if (image.isNull())
    {
        QMessageBox msg_box;
        msg_box.setText("Nothing to save");
        msg_box.exec();
        return;
    }
    QString file_name = QFileDialog::getSaveFileName(nullptr,
                                                     tr("Save file"),
                                                     QString(),
                                                     tr("Images (*.png)"));
    if (!file_name.isNull())
    {
        this->model->getDSTimage().save(file_name, "PNG", 100);
    }
}

void Controller::CpSRCtoDST()
{
    this->model->setDSTimage(this->model->getSRCimage());
}

void Controller::CpDSTtoSRC()
{
    this->model->setSRCimage(this->model->getDSTimage());
}

void Controller::Grayscale()
{
    // TODO
}

void Controller::EdgeDetection()
{
    // TODO
}

void Controller::Blur()
{
    // TODO
}

void Controller::Sharpen()
{
    // TODO
}

void Controller::Identical()
{
    // TODO
}

void Controller::Negative()
{
    // TODO
}

void Controller::Embossing()
{
    // TODO
}

void Controller::Watercolor()
{
    // TODO
}

void Controller::Gamma()
{
    // TODO
}

void Controller::MatrixTransmition()
{
    // TODO
}
