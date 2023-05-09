#include "formupdata.h"
#include "ui_formupdata.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

FormUpdata::FormUpdata(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormUpdata)
{
    ui->setupUi(this);
    this->ui->cancelPushButton->setVisible(false);
    this->ui->downloadPushButton->setVisible(true);
    connect(ui->downloadPushButton, &QPushButton::clicked, this, &FormUpdata::onDownloadButtonClicked);
    connect(ui->selectTargetFolderPushButton, &QPushButton::clicked, this, &FormUpdata::onSelectTargetFolderButtonClicked);
    connect(ui->cancelPushButton, &QPushButton::clicked, this, &FormUpdata::onCancelButtonClicked);
    connect(&m_downloader, &Downloader::updateDownloadProgress, this, &FormUpdata::onUpdateProgress);
    url = "https://drive.google.com/u/0/uc?id=17EnunrrLbvUcud5uT1Yhiucu4fcUEhZv&export=download&confirm=t";
}


void FormUpdata::onDownloadButtonClicked()
{
    if (!this->ui->targetFolderLineEdit->text().isEmpty()) {
        m_downloader.get(ui->targetFolderLineEdit->text(), url);
        this->ui->cancelPushButton->setVisible(true);
        this->ui->downloadPushButton->setVisible(false);
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Выберите куда сохранить!"));
    }
}

void FormUpdata::onSelectTargetFolderButtonClicked()
{
    QString targetFolder = QFileDialog::getExistingDirectory(this,
                                                             tr("Выбор директории"),
                                                             QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
                                                             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->targetFolderLineEdit->setText(targetFolder);
}

void FormUpdata::onCancelButtonClicked()
{
    m_downloader.cancelDownload();
    ui->downloadProgressBar->setMaximum(100);
    ui->downloadProgressBar->setValue(0);
    this->ui->cancelPushButton->setVisible(false);
    this->ui->downloadPushButton->setVisible(true);
}

void FormUpdata::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->downloadProgressBar->setMaximum(bytesTotal);
    ui->downloadProgressBar->setValue(bytesReceived);

    if (bytesReceived == bytesTotal) {
        QMessageBox::information(this, QObject::tr("Скачалось"), QObject::tr("Файл скачался!"));
        this->ui->cancelPushButton->setVisible(false);
        this->ui->downloadPushButton->setVisible(true);
    }
}

FormUpdata::~FormUpdata()
{
    delete ui;
}
