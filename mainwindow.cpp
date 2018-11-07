#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QSizePolicy>
#include <QMessageBox>
#include <QFileDialog>
#include "srccanvas.h"
#include "dstcanvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    QImage image = QImage(":/Lenna.png");
    if (image.isNull())
    {
        QMessageBox msg_box;
        msg_box.setText("Can't open 'Lenna.png'");
        msg_box.exec();
        image = QImage(QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    QString(),
                                                    tr("Images (*.png *.jpg *.gif *.bmp)")));
    }
    this->model = new Model(image, this);  // TODO загрузка файла вместо QImage()

    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new SrcCanvas(this->model));
    layout->addWidget(new DstCanvas(this->model));
    this->ui->centralWidget->setLayout(layout);

    this->controller = new Controller(this->model, this);

    QAction *cp_src_to_dst_action = new QAction(QString("SRC to DST"));
    cp_src_to_dst_action->setToolTip(QString("Копировать изображение из левой зоны в правую"));
    connect(cp_src_to_dst_action, SIGNAL(triggered()), this->controller, SLOT(CpSRCtoDST()));
    QAction *cp_dst_to_src_action = new QAction(QString("DST to SRC"));
    cp_src_to_dst_action->setToolTip(QString("Копировать изображение из левой зоны в правую"));
    connect(cp_dst_to_src_action, SIGNAL(triggered()), this->controller, SLOT(CpDSTtoSRC()));
    this->ui->mainToolBar->addAction(cp_src_to_dst_action);
    this->ui->mainToolBar->addAction(cp_dst_to_src_action);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->controller;
    delete this->model;
}
