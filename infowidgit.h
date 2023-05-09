#ifndef INFOWIDGIT_H
#define INFOWIDGIT_H

#include <QWidget>
#include <QObject>
#include <QMenu>

#include "form_log.h"

class InfoWidgit : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidgit(QWidget *parent = nullptr);
    void setTextInfo(QString info);
    ~InfoWidgit();
private:
    QString info;
    Form_Log form;
signals:
};

#endif // INFOWIDGIT_H
