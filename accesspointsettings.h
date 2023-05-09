#ifndef ACCESSPOINTSETTINGS_H
#define ACCESSPOINTSETTINGS_H

#include <QDialog>

namespace Ui {
class AccessPointSettings;
}

class AccessPointSettings : public QDialog
{
    Q_OBJECT

public:
    void setWinTitle(QString str);
    explicit AccessPointSettings(QWidget *parent = nullptr);
    ~AccessPointSettings();

private:
    Ui::AccessPointSettings *ui;
};

#endif // ACCESSPOINTSETTINGS_H
