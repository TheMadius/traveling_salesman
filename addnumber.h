#ifndef ADDNUMBER_H
#define ADDNUMBER_H

#include <QDialog>

namespace Ui {
class AddNumber;
}

class AddNumber : public QDialog
{
    Q_OBJECT

public:
    explicit AddNumber(QWidget *parent = nullptr);
    ~AddNumber();

    QString number;
    QString last_name;
    QString name;
    QString middle_name;

    bool is_guest;
    QString time;

private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_buttonBox_accepted();

private:
    Ui::AddNumber *ui;
};

#endif // ADDNUMBER_H
