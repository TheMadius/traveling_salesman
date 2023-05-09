#ifndef ALARMMONITOR_H
#define ALARMMONITOR_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QTextBrowser>

class AlarmElement : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmElement(QString title, QWidget *parent = nullptr);
    void setTableItem(QTableWidgetItem* index);
signals:
    void delElement(QTableWidgetItem* index);

private:
    QTableWidgetItem* index;
    QLabel *lable;
    QPushButton *del;
    QPushButton *copy;
};


namespace Ui {
class AlarmMonitor;
}

class AlarmMonitor : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmMonitor(QStringList list, QWidget *parent = nullptr);
    ~AlarmMonitor();

public slots:
    void addElement(QString title);
    void delElement(QTableWidgetItem* title);

signals:
    void deleteAlarm(int index);

private:
    Ui::AlarmMonitor *ui;
};

#endif // ALARMMONITOR_H
