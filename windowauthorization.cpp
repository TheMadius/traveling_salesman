#include "windowauthorization.h"
#include "ui_windowauthorization.h"
#include "mainwindow.h"

WindowAuthorization::WindowAuthorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowAuthorization)
{
    ui->setupUi(this);
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    isLogin = false;
    setModeAuthorization("", "");
}

WindowAuthorization::~WindowAuthorization()
{
    delete ui;
}

void WindowAuthorization::setModeRegister()
{
    this->setWindowTitle("Регистрация пользователя");
    this->ui->pushButton->setVisible(false);
    this->ui->pushButton_2->setVisible(true);
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
}

void WindowAuthorization::setModeAuthorization(QString ip, QString mod)
{
    this->ip = ip;
    this->mod = mod;
    this->setWindowTitle("Авторизация(" + ip + ")");
    this->ui->pushButton->setVisible(true);
    this->ui->pushButton_2->setVisible(false);
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

void WindowAuthorization::on_pushButton_2_clicked()
{
    QString login = this->ui->lineEdit->text();
    QString password = this->ui->lineEdit_2->text();

    if (!((login.isEmpty()) || password.isEmpty())) {
        auto server = (MainWindow *)this->parent();
        if (server->registerUser(ip, login, password)) {
            QMessageBox::information(this, QObject::tr("Успех"), QObject::tr("Пользователь зарегистрирован!"));
            this->accept();
        } else {
            QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Ошибка регистрации!"));
        }
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}


void WindowAuthorization::on_pushButton_clicked()
{
    QString login = this->ui->lineEdit->text();
    QString password = this->ui->lineEdit_2->text();

    if (!((login.isEmpty()) || password.isEmpty())) {
        auto server = (MainWindow *)this->parent();
        if (server->authorisationUser(ip, login, password, this->mod)) {
            QMessageBox::information(this, QObject::tr("Успех"), QObject::tr("Успешный вход!"));
            isLogin = true;
            this->accept();
        } else {
            QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Ошибка авторизации!"));
        }
    } else {
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Не заполнены все поля!"));
    }
}
