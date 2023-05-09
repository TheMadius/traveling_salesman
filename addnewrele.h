#ifndef ADDNEWRELE_H
#define ADDNEWRELE_H

#include <QDialog>

namespace Ui {
class AddNewRele;
}

class AddNewRele : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewRele(QWidget *parent = nullptr);
    void setTitle(QString name);
    ~AddNewRele();
    QString name;
    QString query;
    QString feedback;
    QString areaId;
    QString message;
    bool enter;

private slots:
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddNewRele *ui;
};

#endif // ADDNEWRELE_H
