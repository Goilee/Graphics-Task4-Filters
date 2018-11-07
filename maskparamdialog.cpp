#include "maskparamdialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

QLineEdit * createDoubleInput(QString initial_val)
{
    QDoubleValidator *validator = new QDoubleValidator();
    validator->setNotation(QDoubleValidator::ScientificNotation);
    QLineEdit *line_edit = new QLineEdit(initial_val);
    line_edit->setValidator(validator);
    return line_edit;
}

QLineEdit * createIntInput(QString initial_val)
{
    QIntValidator *validator = new QIntValidator();
    QLineEdit *line_edit = new QLineEdit(initial_val);
    line_edit->setValidator(validator);
    return line_edit;
}

QWidget * createColorComponentInput(QString name, QLineEdit *line_edit)
{
    QLayout *layout = new QHBoxLayout();
    layout->addWidget(new QLabel(name));
    layout->addWidget(line_edit);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    return widget;
}

QPushButton * createButtonAndConnect(QString name, QObject *reciever, const char* member)
{
    QPushButton *button = new QPushButton(name);
    QObject::connect(button, SIGNAL(clicked()), reciever, member);
    return button;
}

void MaskParamDialog::autoNorm()
{
    double s = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s += this->matrix_edits[i][j]->text().toDouble();
        }
    }
    this->norm_edit->setText(QString::number(s));
}

MaskParamDialog::MaskParamDialog(Mask *mask) :
    QDialog(),
    mask(mask)
{
    this->setWindowTitle(QString("Матричное преобразование"));

    // матрица
    QGridLayout *matrix_grid_layout = new QGridLayout();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->matrix_edits[i][j] = createDoubleInput(QString::number(this->mask->matrix[i][j]));
            matrix_grid_layout->addWidget(this->matrix_edits[i][j], i, j);
        }
    }
    QWidget *matrix_grid_widget = new QWidget();
    matrix_grid_widget->setLayout(matrix_grid_layout);
    matrix_grid_widget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    // правая половина окна (матрица с lable)
    QLayout *matrix_layout = new QVBoxLayout();
    QLabel *matrix_label = new QLabel(QString("Матрица"));
    matrix_label->setAlignment(Qt::AlignCenter);
    matrix_layout->addWidget(matrix_label);
    matrix_layout->addWidget(matrix_grid_widget);
    QWidget *matrix_widget = new QWidget();
    matrix_widget->setLayout(matrix_layout);
    //matrix_widget->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

    // строка редактирования норм.коэффициента
    QLayout *norm_edit_layout = new QHBoxLayout();
    this->norm_edit = createDoubleInput(QString::number(this->mask->norm()));
    norm_edit->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    norm_edit_layout->addWidget(norm_edit);
    norm_edit_layout->addWidget(createButtonAndConnect(QString("Авто"), this, SLOT(autoNorm())));
    QWidget *norm_edit_widget = new QWidget();
    norm_edit_widget->setLayout(norm_edit_layout);

    // нормировочный коэффициент
    QLayout *norm_layout = new QVBoxLayout();
    QLabel *norm_label = new QLabel(QString("Нормировочный коэффициент"));
    norm_label->setAlignment(Qt::AlignCenter);
    norm_layout->addWidget(norm_label);
    norm_layout->addWidget(norm_edit_widget);
    QWidget *norm_widget = new QWidget();
    norm_widget->setLayout(norm_layout);

    // строка редактирования цвета смещения
    QLayout *shift_color_layout = new QHBoxLayout();
    for (int i = 0; i < 3; i++)
    {
        this->shift_edits[i] = createIntInput(QString::number(0));
    }
    shift_color_layout->addWidget(createColorComponentInput(QString("r"), this->shift_edits[0]));
    shift_color_layout->addWidget(createColorComponentInput(QString("g"), this->shift_edits[1]));
    shift_color_layout->addWidget(createColorComponentInput(QString("b"), this->shift_edits[2]));
    QWidget *shift_color_widget = new QWidget();
    shift_color_widget->setLayout(shift_color_layout);
    shift_color_widget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    // цвет смещения с lable
    QLayout *shift_layout = new QVBoxLayout();
    QLabel *shift_label = new QLabel(QString("Сдвиг"));
    shift_label->setAlignment(Qt::AlignCenter);
    shift_layout->addWidget(shift_label);
    shift_layout->addWidget(shift_color_widget);
    QWidget *shift_widget = new QWidget();
    shift_widget->setLayout(shift_layout);

    // правая половина окна (параметры)
    QLayout *params_layout = new QVBoxLayout();
    params_layout->addWidget(norm_widget);
    params_layout->addWidget(shift_widget);
    QWidget *params_widget = new QWidget();
    params_widget->setLayout(params_layout);
    //params_widget->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

    // область редактирования
    QLayout *edits_layout = new QHBoxLayout();
    edits_layout->addWidget(matrix_widget);
    edits_layout->addWidget(params_widget);
    QWidget *edits_widget = new QWidget();
    edits_widget->setLayout(edits_layout);

    // кнопки
    QLayout *buttons_layout = new QHBoxLayout();
    buttons_layout->addWidget(createButtonAndConnect(QString("OK"), this, SLOT(accept())));
    buttons_layout->addWidget(createButtonAndConnect(QString("Отмена"), this, SLOT(reject())));
    buttons_layout->addWidget(createButtonAndConnect(QString("Применить"), this, SLOT(apply())));
    QWidget *buttons_widget = new QWidget();
    buttons_widget->setLayout(buttons_layout);

    // все окно
    QLayout *base_layout = new QVBoxLayout();
    base_layout->addWidget(edits_widget);
    base_layout->addWidget(buttons_widget);
    this->setLayout(base_layout);
}

void MaskParamDialog::accept()
{
    this->apply();
    QDialog::accept();
}

void MaskParamDialog::reject()
{
    QDialog::reject();
}

void MaskParamDialog::apply()
{
    double norm = this->norm_edit->text().toDouble();
    if (norm == 0)
    {
        QMessageBox msg_box;
        msg_box.setText("Нормировочный коэффициент не должен быть равен 0!");
        msg_box.exec();
        return;
    }

    this->mask->setNorm(norm);
    this->mask->setRedShift(this->shift_edits[0]->text().toInt());
    this->mask->setGreenShift(this->shift_edits[1]->text().toInt());
    this->mask->setBlueShift(this->shift_edits[2]->text().toInt());
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->mask->matrix[i][j] = this->matrix_edits[i][j]->text().toDouble();
        }
    }

    emit this->applied();
}
