#ifndef SETTINGSAREA_H
#define SETTINGSAREA_H

#include <QDialog>

namespace Ui {
class SettingsArea;
}

class SettingsArea : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsArea(QWidget *parent = nullptr);
    ~SettingsArea();
    void addElement(QPixmap pixmap, int id, QString name, QString date);
    void deleteElement(int id);
    void setTitle(QString name);
signals:
    void deletePerson(int id);
private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingsArea *ui;
};

#endif // SETTINGSAREA_H
