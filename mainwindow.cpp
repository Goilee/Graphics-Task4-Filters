#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QSizePolicy>
#include <QMessageBox>
#include <QFileDialog>
#include "srccanvas.h"
#include "dstcanvas.h"

QAction * createAction(QString name, QString tool_tip, QObject *reciever, const char *member)
{
    QAction *action = new QAction(name);
    action->setToolTip(tool_tip);
    QObject::connect(action, SIGNAL(triggered()), reciever, member);
    return action;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->setWindowTitle(QString("Task 4"));

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

    this->ui->mainToolBar->addAction(createAction(QString("Новый файл"),
                                                  QString("Изменить рабочее изображение"),
                                                  this->controller, SLOT(newFile())));
    this->ui->mainToolBar->addAction(createAction(QString("Сохранить в файл"),
                                                  QString("Сохранить изображение из правой зоны в файл"),
                                                  this->controller, SLOT(saveToFile())));
    this->ui->mainToolBar->addAction(createAction(QString("SRC --> DST"),
                                                  QString("Копировать изображение из левой зоны в правую"),
                                                  this->controller, SLOT(cpSRCtoDST())));
    this->ui->mainToolBar->addAction(createAction(QString("SRC <-- DST"),
                                                  QString("Копировать изображение из правой зоны в левую"),
                                                  this->controller, SLOT(cpDSTtoSRC())));

    this->ui->filter_bar->addAction(createAction(QString("Оттенки серого"),
                                                 QString("Перевести изображение в оттенки серого"),
                                                 this->controller, SLOT(grayscale())));
    this->ui->filter_bar->addAction(createAction(QString("Выделение контуров"),
                                                 QString("Выделение контуров по каждой из цветовых компонент"),
                                                 this->controller, SLOT(edgeDetection())));
    this->ui->filter_bar->addAction(createAction(QString("Сглаживание"),
                                                 QString("Размытие изображения"),
                                                 this->controller, SLOT(blur())));
    this->ui->filter_bar->addAction(createAction(QString("Резкость"),
                                                 QString("Повышение резкости изображения"),
                                                 this->controller, SLOT(sharpen())));
    this->ui->filter_bar->addAction(createAction(QString("Идентичное преобразование"),
                                                 QString("Идентичное преобразование"),
                                                 this->controller, SLOT(identical())));
    this->ui->filter_bar->addAction(createAction(QString("Негатив"),
                                                 QString("Перевести изображение в негатив"),
                                                 this->controller, SLOT(negative())));
    this->ui->filter_bar->addAction(createAction(QString("Тиснение"),
                                                 QString("Тиснение"),
                                                 this->controller, SLOT(embossing())));
    this->ui->filter_bar->addAction(createAction(QString("Аквалеризация"),
                                                 QString("Аквалеризация"),
                                                 this->controller, SLOT(watercolor())));
    this->ui->filter_bar->addAction(createAction(QString("Гамма"),
                                                 QString("Гамма коррекция"),
                                                 this->controller, SLOT(gamma())));
    this->ui->filter_bar->addAction(createAction(QString("Матричное преобразование"),
                                                 QString("Произвольное матричное 3х3 преобразование"),
                                                 this->controller, SLOT(matrixTransmition())));
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
