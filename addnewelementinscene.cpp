#include "addnewelementinscene.h"
#include "ui_addnewelementinscene.h"
#include <QMessageBox>

AddNewElementInScene::AddNewElementInScene(std::vector<std::string> elemen_list, bool listVisibl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewElementInScene)
{
    ui->setupUi(this);

    this->listVisibl = listVisibl;
}

void AddNewElementInScene::setVisibleName(bool flag)
{
    this->enterObj = flag;

    this->ui->label->setVisible(flag);
    this->ui->lineEdit->setVisible(flag);
}

void AddNewElementInScene::setCurrentIndex(QString name_element)
{
}

AddNewElementInScene::~AddNewElementInScene()
{
    delete ui;
}

void AddNewElementInScene::on_buttonBox_accepted()
{
    QString name = this->ui->lineEdit->text();

    if (!name.isEmpty()) {
        this->name = name;
        this->accept();
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}

