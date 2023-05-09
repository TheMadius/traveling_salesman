#include "addnewmap.h"
#include "ui_addnewmap.h"
#include <QFileDialog>
#include <QMessageBox>

AddNewMap::AddNewMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewMap)
{
    ui->setupUi(this);
}

AddNewMap::~AddNewMap()
{
    delete ui;
}

void AddNewMap::on_pushButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file",QString(),"JPG (*.jpg);; PNG (*.png)");
    if(!file_name.isNull()) {
        this->ui->label_3->setText(file_name);
    }
}

void AddNewMap::on_buttonBox_accepted()
{
    QString name = this->ui->lineEdit->text();
    QString path = this->ui->label_3->text();

    if (!(name.isEmpty() || path.isEmpty())) {
        this->name = name;
        this->path = path;
        this->accept();
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}

