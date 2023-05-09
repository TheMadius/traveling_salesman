#include "settingsperimetr.h"
#include "ui_settingsperimetr.h"

SettingsPerimetr::SettingsPerimetr(QList<QString> listObject, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsPerimetr)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 10);

    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setVisible(false);
    ui->tableWidget_2->setColumnWidth(0, 10);

    for (auto id : listObject) {
        this->ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        this->ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 0, new QCheckBox());
        this->ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(id));

        this->ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
        this->ui->tableWidget_2->setCellWidget(ui->tableWidget_2->rowCount() - 1, 0, new QCheckBox());
        this->ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount() - 1, 1, new QTableWidgetItem(id));
    }
}

void SettingsPerimetr::setTitle(QString name)
{
    this->setWindowTitle(name);
}

SettingsPerimetr::~SettingsPerimetr()
{
    delete ui;
}

void SettingsPerimetr::on_buttonBox_accepted()
{
    this->outside.clear();
    this->inside.clear();

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (((QCheckBox *)(ui->tableWidget->cellWidget(i, 0)))->isChecked()) {
            this->inside.append(ui->tableWidget->item(i, 1)->text());
        }
    }

    for (int i = 0; i < ui->tableWidget_2->rowCount(); i++) {
        if (((QCheckBox *)(ui->tableWidget_2->cellWidget(i, 0)))->isChecked()) {
            this->outside.append(ui->tableWidget_2->item(i, 1)->text());
        }
    }

    this->accept();
}

