#ifndef ADDNEWMAP_H
#define ADDNEWMAP_H

#include <QDialog>

namespace Ui {
class AddNewMap;
}

class AddNewMap : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewMap(QWidget *parent = nullptr);
    ~AddNewMap();
    QString name;
    QString path;
private slots:
    void on_pushButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::AddNewMap *ui;
};

#endif // ADDNEWMAP_H
