#ifndef FORM_LOG_H
#define FORM_LOG_H

#include <QWidget>
#include <mutex>
#include <QSemaphore>

namespace Ui {
class Form_Log;
}

class Form_Log : public QWidget
{
    Q_OBJECT
public:
    void titleSet(QString name);
public:
    explicit Form_Log(QWidget *parent = nullptr);
    void setText(QString text);
    void setTitle(QString name);
    ~Form_Log();
public slots:
    void logMsg(QString msg);
signals:
    void sendLog(QString msg);
private:
    int line;
    Ui::Form_Log *ui;
    std::mutex m;
};

#endif // FORM_LOG_H
