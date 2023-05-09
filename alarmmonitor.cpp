#include "alarmmonitor.h"
#include "ui_alarmmonitor.h"
#include <QDebug>
#include <QApplication>
#include <QClipboard>

AlarmElement::AlarmElement(QString title, QWidget *parent)
    : QWidget(parent)
{
    this->setLayout(new QHBoxLayout());
    this->setMinimumHeight(40);

    lable = new QLabel();
    copy = new QPushButton();
    del = new QPushButton();

    copy->setFixedSize(20,20);
    del->setFixedSize(20,20);

    this->layout()->addWidget(lable);
    this->layout()->addWidget(copy);
    this->layout()->addWidget(del);

    lable->setText(title);
    lable->setWordWrap(true);

    index = nullptr;

    del->setIcon(QIcon(":/qss_icons/dark/rc/tresh.png"));
    copy->setIcon(QIcon(":/qss_icons/dark/rc/copy_.png"));

    connect(copy, &QPushButton::clicked, [this](){
        QApplication::clipboard()->setText(this->lable->text());
    });

    connect(del, &QPushButton::clicked, [this](){
        emit delElement(this->index);
    });
}

void AlarmElement::setTableItem(QTableWidgetItem* index)
{
    this->index = index;
}

AlarmMonitor::AlarmMonitor(QStringList list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmMonitor)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    for(auto it : list)
        addElement(it);
}

void AlarmMonitor::addElement(QString title)
{
    this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
    AlarmElement *item = new AlarmElement(title);
    this->ui->tableWidget->setCellWidget(this->ui->tableWidget->rowCount() - 1, 0, item);
    ui->tableWidget->setRowHeight(this->ui->tableWidget->rowCount() - 1, item->sizeHint().height());
    this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(""));
    item->setTableItem(this->ui->tableWidget->item(this->ui->tableWidget->rowCount() - 1, 0));
    connect(item, &AlarmElement::delElement, this, &AlarmMonitor::delElement);
}

void AlarmMonitor::delElement(QTableWidgetItem* title)
{
    if (title != nullptr) {
        emit deleteAlarm(title->row());
        this->ui->tableWidget->removeRow(title->row());
    }
}

AlarmMonitor::~AlarmMonitor()
{
    delete ui;
}
