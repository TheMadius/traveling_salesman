#ifndef FORMUPDATA_H
#define FORMUPDATA_H

#include <QWidget>
#include <QDialog>
#include "downloader.h"

namespace Ui {
class FormUpdata;
}

class FormUpdata : public QDialog
{
    Q_OBJECT

public:
    explicit FormUpdata(QWidget *parent = nullptr);
    ~FormUpdata();

private slots:
    void onDownloadButtonClicked();
    void onSelectTargetFolderButtonClicked();
    void onCancelButtonClicked();
    void onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QString url;
    Downloader m_downloader; // Класс для скачивания
    Ui::FormUpdata *ui;
};

#endif // FORMUPDATA_H
