#ifndef ALARMBUTTON_H
#define ALARMBUTTON_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QTimer>
#include "alarmmonitor.h"

class AlarmButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AlarmButton(QWidget *parent = nullptr);
    void switchState();
public slots:
    void startAnimation();
    void stopAnimation();
    void showMonitor();
    void getAlarm(QString msg);
    void deleteAlarm(int index);
signals:
    void sendAlarm(QString msg);
private:
    QTimer time;
    bool state;
    int countAlarm;
    QMetaObject::Connection connected;
    QStringList alarms;
};

#endif // ALARMBUTTON_H
