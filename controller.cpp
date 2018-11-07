#include "controller.h"
#include "photoshop.h"

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
    // TODO
}

void Controller::saveToFile()
{
    // TODO
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
