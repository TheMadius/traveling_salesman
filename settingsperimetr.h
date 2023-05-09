#ifndef SETTINGSPERIMETR_H
#define SETTINGSPERIMETR_H

#include <QDialog>
#include <QCheckBox>

namespace Ui {
class SettingsPerimetr;
}

class SettingsPerimetr : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsPerimetr(QList<QString> listObject, QWidget *parent = nullptr);
    void setTitle(QString name);
    ~SettingsPerimetr();
    QList<QString> outside;
    QList<QString> inside;
private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsPerimetr *ui;
};

#endif // SETTINGSPERIMETR_H
