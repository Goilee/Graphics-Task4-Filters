#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QSizePolicy>
#include "srccanvas.h"
#include "dstcanvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->model = new Model(QImage());  // TODO загрузка файла вместо QImage()

    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new SrcCanvas(this->model));
    layout->addWidget(new DstCanvas(this->model));
    this->ui->centralWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->controller;
    delete this->model;
}
