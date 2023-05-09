#include "addnumber.h"
#include "ui_addnumber.h"
#include <QMessageBox>

AddNumber::AddNumber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNumber)
{
    ui->setupUi(this);
    this->ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

AddNumber::~AddNumber()
{
    delete ui;
}

void AddNumber::on_checkBox_stateChanged(int arg1)
{
    this->ui->dateTimeEdit->setEnabled(arg1);
}


void AddNumber::on_buttonBox_accepted()
{
    QString number = this->ui->lineEdit->text();
    QString last_name = this->ui->lineEdit_2->text();
    QString name = this->ui->lineEdit_3->text();
    QString middle_name = this->ui->lineEdit_4->text();

    if (!(number.isEmpty() || last_name.isEmpty() || name.isEmpty() || middle_name.isEmpty())) {
        this->number = number;
        this->last_name = last_name;
        this->name = name;
        this->middle_name = middle_name;
        this->is_guest = this->ui->checkBox->isChecked();
        this->time = ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd_HH:mm:ss");

        this->accept();
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}

