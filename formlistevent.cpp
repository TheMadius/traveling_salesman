#include "formlistevent.h"
#include "ui_formlistevent.h"
#include <QDebug>

FormLIstEvent::FormLIstEvent(int maxCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLIstEvent)
{
    ui->setupUi(this);
    this->maxCount = maxCount;

    this->ui->tableWidget->hideColumn(0);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 94);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->tableWidget->setAutoScroll(false);

    viewer = new DialogViewer();

    this->count_detect = 0;
    this->count_reco = 0;
}

void FormLIstEvent::closeEvent(QCloseEvent *event)
{
    if(viewer != nullptr)
        viewer->close();
}

void FormLIstEvent::clearEvent()
{
    this->ui->tableWidget->setRowCount(0);
    this->count_detect = 0;
    this->count_reco = 0;
}

void FormLIstEvent::showDetect()
{
    for (int i = 0; i < this->ui->tableWidget->rowCount(); ++i) {
        ui->tableWidget->showRow(i);
    }
}

void FormLIstEvent::hideDetect()
{
    for (int i = 0; i < this->ui->tableWidget->rowCount(); ++i) {
        if (((ListElement*)ui->tableWidget->cellWidget(i, 1))->getId() == -1) {
            ui->tableWidget->hideRow(i);
        }
    }
}

void FormLIstEvent::deleteDetectEvent()
{
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; --i) {
        auto element = (ListElement*)(ui->tableWidget->cellWidget(i, 1));
        if (element == nullptr)
            continue;

        if (element->getId() == -1) {
            ui->tableWidget->removeRow(i);
            return;
        }
    }
}

void FormLIstEvent::deleteRecoEvent()
{
    for (int i = ui->tableWidget->rowCount() - 1; i >= 0; --i) {
        auto element = (ListElement*)(ui->tableWidget->cellWidget(i, 1));
        if (element == nullptr)
            continue;

        if (element->getId() != -1) {
            ui->tableWidget->removeRow(i);
            return;
        }
    }
}

void FormLIstEvent::addElement(ListElement *element, CustomLable *lablePhot, bool connected, bool up)
{
    if (element == nullptr)
        return;

    if (lablePhot == nullptr)
        return;

    if (this->count_reco >= this->maxCount) {
        deleteRecoEvent();
        this->count_reco--;
    }

    if (this->count_detect >= this->maxCount) {
        deleteDetectEvent();
        this->count_detect--;
    }

    if (connected)
        connect(lablePhot, &CustomLable::requestView, this, &FormLIstEvent::showViewer);

    int i = (up)? 0 : ui->tableWidget->rowCount();  

    ui->tableWidget->insertRow(i);
    ui->tableWidget->setRowHeight(i, element->sizeHint().height());
    ui->tableWidget->setCellWidget(i, 1, element);
    ui->tableWidget->setCellWidget(i, 0, lablePhot);

    if ( element->getId() == -1 ) {
        if (!this->ui->checkBox_2->isChecked()) {
            ui->tableWidget->hideRow(i);
        }
        count_detect++;
    } else {
        count_reco++;
    }
}

void FormLIstEvent::showViewer(cv::Mat frame)
{
    viewer->setFrame(frame);
    viewer->show();
}

FormLIstEvent::~FormLIstEvent()
{
    delete viewer;
    delete ui;
}

void FormLIstEvent::on_checkBox_stateChanged(int arg1)
{
    if(arg1) {
        this->setFixedWidth(384);
        this->ui->tableWidget->showColumn(0);
    } else {
        this->setFixedWidth(309);
        this->ui->tableWidget->hideColumn(0);
    }
}


void FormLIstEvent::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1) {
        showDetect();
    } else {
        hideDetect();
    }
}

