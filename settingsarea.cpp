#include "settingsarea.h"
#include "ui_settingsarea.h"
#include "listelement.h"

#include <QDebug>

SettingsArea::SettingsArea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsArea)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void SettingsArea::deleteElement(int id)
{
    for (int i = 0; i < this->ui->tableWidget->rowCount(); ++i) {
        if (((ListElement *)(ui->tableWidget->cellWidget(i, 0)))->getId() == id) {
            ui->tableWidget->removeRow(i);
            return;
        }
    }
}

void SettingsArea::addElement(QPixmap pixmap, int id, QString name, QString date)
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ListElement *itemWinget = new ListElement(id, name, this);
    itemWinget->setPixmap(pixmap);
    itemWinget->setDate(date);
    itemWinget->setVisibleCam(false);
    itemWinget->setVisibleTime(false);

    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 0, itemWinget);
    ui->tableWidget->setRowHeight(ui->tableWidget->rowCount() - 1, itemWinget->getPhoto()->height());
}

void SettingsArea::setTitle(QString name)
{
    this->setWindowTitle(name);
}

SettingsArea::~SettingsArea()
{
    delete ui;
}

void SettingsArea::on_pushButton_clicked()
{
    if (ui->tableWidget->currentRow() >= 0) {
        int id = ((ListElement *)(ui->tableWidget->cellWidget(ui->tableWidget->currentRow(), 0)))->getId();
        emit this->deletePerson(id);
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    }
}

