#ifndef FORMLISTRELE_H
#define FORMLISTRELE_H

#include <QDialog>
#include <QListWidgetItem>
#include <vector>
#include <string>

namespace Ui {
class FormListRele;
}

class FormListRele : public QDialog
{
    Q_OBJECT

public:
    explicit FormListRele(std::vector<std::string> list_rele, QWidget *parent = nullptr);
    void setWinTitle(QString name);
    QString selectedRele;
    ~FormListRele();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_buttonBox_accepted();

private:
    Ui::FormListRele *ui;
};

#endif // FORMLISTRELE_H
