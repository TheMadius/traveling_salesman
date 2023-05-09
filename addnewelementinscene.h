#ifndef ADDNEWELEMET_H
#define ADDNEWELEMET_H

#include <QDialog>
#include <vector>
#include <string>

namespace Ui {
class AddNewElementInScene;
}

class AddNewElementInScene : public QDialog
{
     Q_OBJECT

public:
    explicit AddNewElementInScene(std::vector<std::string> elemen_list, bool listVisibl = true, QWidget *parent = nullptr);
    void setVisibleName(bool flag);
    void setCurrentIndex(QString name_element);
    ~AddNewElementInScene();
    QString name;
    QString obj;
private slots:
    void on_buttonBox_accepted();

private:
     Ui::AddNewElementInScene *ui;
     bool listVisibl;
     bool enterObj;
};

#endif // ADDNEWMAP_H
