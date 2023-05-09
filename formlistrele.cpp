#include "formlistrele.h"
#include "ui_formlistrele.h"
#include <QMessageBox>

FormListRele::FormListRele(std::vector<std::string> list_rele, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormListRele)
{
    ui->setupUi(this);

    for(auto it : list_rele) {
        this->ui->listWidget->addItem(it.c_str());
    }
}

void FormListRele::setWinTitle(QString name)
{
    this->setWindowTitle(name);
}

FormListRele::~FormListRele()
{
    delete ui;
}

void FormListRele::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    this->selectedRele = item->text();
    this->accept();
}


void FormListRele::on_buttonBox_accepted()
{
    if (this->ui->listWidget->currentItem() != nullptr) {
        this->selectedRele = this->ui->listWidget->currentItem()->text();
        this->accept();
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не выбрано имя реле!"));
    }
}

