#include "accesspointsettings.h"
#include "ui_accesspointsettings.h"

AccessPointSettings::AccessPointSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccessPointSettings)
{
    ui->setupUi(this);
}

void AccessPointSettings::setWinTitle(QString str) {
    this->setWindowTitle(str);
}

AccessPointSettings::~AccessPointSettings()
{
    delete ui;
}
