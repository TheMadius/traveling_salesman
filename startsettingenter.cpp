#include "startsettingenter.h"
#include "ui_startsettingenter.h"

StartSettingEnter::StartSettingEnter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartSettingEnter)
{
    ui->setupUi(this);
}

StartSettingEnter::~StartSettingEnter()
{
    delete ui;
}

void StartSettingEnter::on_buttonBox_accepted()
{
    host = this->ui->lineEdit->text();
    port = this->ui->lineEdit_2->text();
    user = this->ui->lineEdit_3->text();
    password = this->ui->lineEdit_5->text();
    db_name = this->ui->lineEdit_4->text();
    this->accept();
}

