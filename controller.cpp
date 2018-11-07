#include "controller.h"
#include "photoshop.h"
#include <QFileDialog>
#include <QMessageBox>

Controller::Controller(Model *model, QObject *parent) :
    QObject(parent),
    model(model), mask(Mask())
{
    this->mask_dialog = new MaskParamDialog(&this->mask);
    connect(this->mask_dialog, SIGNAL(applied()), this, SLOT(applyMatrixTransmition()));
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

void Controller::cpSRCtoDST()
{
    this->model->setDSTimage(this->model->getSRCimage());
}

void Controller::cpDSTtoSRC()
{
    this->model->setSRCimage(this->model->getDSTimage());
}

void Controller::grayscale()
{
    this->model->setDSTimage(photoshop::grayscale(this->model->getSRCimage()));
}

void Controller::edgeDetection()
{
    // TODO
}

void Controller::blur()
{
    // TODO
}

void Controller::sharpen()
{
    // TODO
}

void Controller::identical()
{
    this->model->setDSTimage(photoshop::identical(this->model->getSRCimage()));
}

void Controller::negative()
{
    this->model->setDSTimage(photoshop::negative(this->model->getSRCimage()));
}

void Controller::embossing()
{
    // TODO
}

void Controller::watercolor()
{
    // TODO
}

void Controller::gamma()
{
    // TODO
}

void Controller::matrixTransmition()
{
    this->mask_dialog->show();
}

void Controller::applyMatrixTransmition()
{
    this->model->setDSTimage(photoshop::matrixTransmition(this->model->getSRCimage(), this->mask));
}
