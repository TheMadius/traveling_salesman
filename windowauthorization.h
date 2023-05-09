#ifndef WINDOWAUTHORIZATION_H
#define WINDOWAUTHORIZATION_H

#include <QDialog>

namespace Ui {
class WindowAuthorization;
}

class WindowAuthorization : public QDialog
{
    Q_OBJECT

public:
    explicit WindowAuthorization(QWidget *parent = nullptr);
    ~WindowAuthorization();
    void setModeRegister();
    void setModeAuthorization(QString ip, QString mod);
    bool isLogin;
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    QString ip;
    QString mod;
    Ui::WindowAuthorization *ui;
};

#endif // WINDOWAUTHORIZATION_H
