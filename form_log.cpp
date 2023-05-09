#include "form_log.h"
#include "ui_form_log.h"
#include <QDebug>

Form_Log::Form_Log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Log)
{
    ui->setupUi(this);
    line = 0;
    connect(this, &Form_Log::sendLog, this, &Form_Log::logMsg);
}

void Form_Log::setText(QString text)
{
  this->ui->textEdit->setText(text);
}

void Form_Log::setTitle(QString name)
{
    this->setWindowTitle(name);
}

void Form_Log::logMsg(QString msg)
{
    if (line == 100) {
        this->ui->textEdit->setText("");
        line = 0;
    }

    this->ui->textEdit->append(QString::number(line + 1) + ") "+ msg);
    line++;
}
void Form_Log::titleSet(QString name)
{
    this->setWindowTitle(name);
}

Form_Log::~Form_Log()
{
    delete ui;
}
