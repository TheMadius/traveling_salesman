#ifndef STARTSETTINGENTER_H
#define STARTSETTINGENTER_H

#include <QDialog>

namespace Ui {
class StartSettingEnter;
}

class StartSettingEnter : public QDialog
{
    Q_OBJECT

public:
    explicit StartSettingEnter(QWidget *parent = nullptr);
    ~StartSettingEnter();
    QString host;
    QString port;
    QString user;
    QString password;
    QString db_name;
private slots:
    void on_buttonBox_accepted();

private:
    Ui::StartSettingEnter *ui;
};

#endif // STARTSETTINGENTER_H
