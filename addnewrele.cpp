#include "addnewrele.h"0
#include "ui_addnewrele.h"
#include <QMessageBox>

AddNewRele::AddNewRele(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewRele)
{
    ui->setupUi(this);
}

AddNewRele::~AddNewRele()
{
    delete ui;
}

void AddNewRele::setTitle(QString name)
{
    this->setWindowTitle(name);
}

void AddNewRele::on_checkBox_2_stateChanged(int arg1)
{
    ui->checkBox->setChecked(!arg1);
}

void AddNewRele::on_checkBox_stateChanged(int arg1)
{
     ui->checkBox_2->setChecked(!arg1);
}

void AddNewRele::on_buttonBox_accepted()
{
    QString name = ui->lineEdit_5->text();
    QString query = ui->lineEdit_4->text();
    QString areaId = ui->lineEdit_6->text();
    bool enter = this->ui->checkBox->isChecked();

    if (!(name.isEmpty() && query.isEmpty())) {
         this->name = name;
         this->query = query;
         this->areaId = areaId;
         this->enter = enter;

         this->accept();
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}

