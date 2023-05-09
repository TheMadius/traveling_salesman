#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QDialog>
#include <QGraphicsItem>
#include <QTableWidget>
#include "infowidgit.h"

class ListElementForScene : public QWidget, public QTableWidgetItem
{
    Q_OBJECT
public:
    explicit ListElementForScene(int type, QString name = "", QGraphicsItem *item = nullptr , QWidget *parent = nullptr);
    void setName(QString name);
    void setForm(QDialog *form);
    void setNameScene(QString name);
    QString getNameScene();
    void showForm();
    int getType(){ return this->type;}
    QString getName(){ return this->name->text();}
    QGraphicsItem *getItem(){ return this->item;}
signals:

private:
    QLabel *name;
    QDialog *form;
    QGraphicsItem *item;
    QString nameScene;
    int type;
};

class ListElement : public QWidget
{
    Q_OBJECT
public:
    explicit ListElement(int idFase, QString name, QWidget *parent = nullptr);
    void setInfo(QString &text);
    void setPixmap(QPixmap &pixmap);
    void setText(QString &text);
    void setRele(QString &text, bool enter = true);
    void setDate(QString &label);
    void setTime(QString &label);
    void setCamera(QString &label);
    void setModeView(bool flag);
    void setVisibleTime(bool flag){ this->time->setVisible(flag); }
    void setVisibleCam(bool flag){ this->cam->setVisible(flag); }

    QString getDate();
    QString getTime();
    QString getCamera();

    const QPixmap *getPhoto();
    ~ListElement();

    int getId();
signals:

private:
    QLabel *name;
    QLabel *date;
    QLabel *time;
    QLabel *photo;
    QLabel *cam;
    QLabel *rele;

    InfoWidgit *text;

    QString strDate;
    QString strName;
    QString strTime;
    QString strCam;

    int idFase;
};

#endif // LISTELEMENT_H
