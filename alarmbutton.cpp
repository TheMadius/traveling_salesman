#include "alarmbutton.h"
#include <QDebug>

AlarmButton::AlarmButton(QWidget *parent)
    : QPushButton{parent}
{
    this->setIcon(QIcon(":/qss_icons/dark/rc/alarm_empty.png"));
    connect(&time, &QTimer::timeout, this, &AlarmButton::switchState);
    connect(this, &AlarmButton::clicked, this, &AlarmButton::showMonitor);
    connect(this, &AlarmButton::sendAlarm, this, &AlarmButton::getAlarm);

    state = false;
    countAlarm = 0;
}

void AlarmButton::showMonitor()
{
    AlarmMonitor *monitir = new AlarmMonitor(this->alarms, this);
    connect(monitir, &AlarmMonitor::deleteAlarm, this, &AlarmButton::deleteAlarm);
    monitir->exec();
}

void AlarmButton::getAlarm(QString msg)
{
    this->alarms.push_back(msg);
    countAlarm++;
    if (countAlarm == 1) {
        startAnimation();
    }
}

void AlarmButton::deleteAlarm(int index)
{
    this->alarms.removeAt(index);
    countAlarm--;
    if (countAlarm == 0) {
        stopAnimation();
        this->setIcon(QIcon(":/qss_icons/dark/rc/alarm_empty.png"));
    }
}

void AlarmButton::startAnimation()
{
    time.start(1000);
}


void AlarmButton::stopAnimation()
{
    time.stop();
}

void AlarmButton::switchState()
{
    if (state)
        this->setIcon(QIcon(":/qss_icons/dark/rc/alarm_empty.png"));
    else
        this->setIcon(QIcon(":/qss_icons/dark/rc/alarm.png"));

    state = !state;
}
