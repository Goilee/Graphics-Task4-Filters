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
        if (image.isNull())
        {
            msg_box.setText("No image to process. Exiting...");
            msg_box.exec();
            this->~MainWindow();
        }
    }
    this->model = new Model(image, this);  // TODO загрузка файла вместо QImage()

    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new SrcCanvas(this->model));
    layout->addWidget(new DstCanvas(this->model));
    this->ui->centralWidget->setLayout(layout);
    this->controller = new Controller(this->model, this);

    QAction *new_file_action = new QAction(QString("Новый файл"));
    new_file_action->setToolTip(QString("Изменить рабочее изображение"));
    connect(new_file_action, SIGNAL(triggered()), this->controller, SLOT(newFile()));
    this->ui->mainToolBar->addAction(new_file_action);
    QAction *save_to_file_action = new QAction(QString("Сохранить в файл"));
    save_to_file_action->setToolTip(QString("Сохранить изображение из левой зоны в файл"));
    connect(save_to_file_action, SIGNAL(triggered()), this->controller, SLOT(saveToFile()));
    this->ui->mainToolBar->addAction(save_to_file_action);
    QAction *cp_src_to_dst_action = new QAction(QString("SRC --> DST"));
    cp_src_to_dst_action->setToolTip(QString("Копировать изображение из левой зоны в правую"));
    connect(cp_src_to_dst_action, SIGNAL(triggered()), this->controller, SLOT(cpSRCtoDST()));
    this->ui->mainToolBar->addAction(cp_src_to_dst_action);
    QAction *cp_dst_to_src_action = new QAction(QString("SRC <-- DST"));
    cp_src_to_dst_action->setToolTip(QString("Копировать изображение из левой зоны в правую"));
    connect(cp_dst_to_src_action, SIGNAL(triggered()), this->controller, SLOT(cpDSTtoSRC()));
    this->ui->mainToolBar->addAction(cp_dst_to_src_action);

    QAction *indent_action = new QAction(QString("Идентичное преобразование"));
    indent_action->setToolTip(QString("Идентичное преобразование"));
    connect(indent_action, SIGNAL(triggered()), this->controller, SLOT(identical()));
    this->ui->filter_bar->addAction(indent_action);
    QAction *grayscale_action = new QAction(QString("Оттенки серого"));
    grayscale_action->setToolTip(QString("Перевести изображение в оттенки серого"));
    connect(grayscale_action, SIGNAL(triggered()), this->controller, SLOT(grayscale()));
    this->ui->filter_bar->addAction(grayscale_action);
    QAction *negative_action = new QAction(QString("Негатив"));
    negative_action->setToolTip(QString("Перевести изображение в негатив"));
    connect(negative_action, SIGNAL(triggered()), this->controller, SLOT(negative()));
    this->ui->filter_bar->addAction(negative_action);
}

MainWindow::~MainWindow()
{
    delete this->ui;
    if (this->controller != nullptr)
    {
        delete this->controller;
    }
    if (this->model != nullptr)
    {
        delete this->model;
    }
}
