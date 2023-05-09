#include "listelement.h"
#include <QMenu>

ListElementForScene::ListElementForScene(int type, QString name, QGraphicsItem *item, QWidget *parent)
    : QWidget(parent),
      QTableWidgetItem()
{
    this->setText(name);

    this->form = nullptr;
    this->type = type;

    this->item = item;   
}

void ListElementForScene::setName(QString name)
{
    this->name->setText(name);
}

void ListElementForScene::setForm(QDialog *form)
{
    this->form = form;
}

void ListElementForScene::setNameScene(QString name)
{
    this->nameScene = name;
}

QString ListElementForScene::getNameScene()
{
    return this->nameScene;
}

void ListElementForScene::showForm()
{
    if (form != nullptr)
        this->form->exec();
}

ListElement::ListElement(int idFase, QString name, QWidget *parent)
    : QWidget{parent}
{
    text = new InfoWidgit();
    this->setLayout(new QHBoxLayout());
    text->setLayout(new QVBoxLayout());

    this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    this->layout()->setContentsMargins(0,0,0,0);
    text->layout()->setContentsMargins(0,0,0,0);

    this->name = new QLabel("ФИО:" + name);
    this->date = new QLabel();
    this->time = new QLabel();
    this->cam = new QLabel();
    this->rele = new QLabel();

    photo = new QLabel();
    this->strName = name;

    this->layout()->addWidget(photo);
    this->layout()->addWidget(text);

    text->layout()->addWidget(this->cam);
    text->layout()->addWidget(this->name);
    text->layout()->addWidget(this->date);
    text->layout()->addWidget(this->time);
    text->layout()->addWidget(this->rele);

    this->idFase = idFase;
}

const QPixmap* ListElement::getPhoto()
{
    return this->photo->pixmap();
}


void ListElement::setModeView(bool flag)
{
    this->text->setVisible(flag);
    if (!flag) {
        QString info = "Камера : " + this->strCam + "\nФИО : " + this->strName;
        this->photo->setToolTip(info);
    }
}

QString ListElement::getDate()
{
    return this->strDate;
}

QString ListElement::getTime()
{
    return this->strTime;
}

QString ListElement::getCamera()
{
    return this->strCam;
}

void ListElement::setInfo(QString &text)
{
    this->text->setTextInfo(text);
}

void ListElement::setPixmap(QPixmap &pixmap)
{
    this->photo->setPixmap(pixmap);
}

void ListElement::setText(QString &text)
{
    this->photo->setText(text);
}

void ListElement::setDate(QString &label)
{
    this->date->setText("Дата:" + label);
    strDate = label;
}

void ListElement::setRele(QString &text, bool enter)
{
    this->rele->setText("Rele:" + text);

    if (enter) {
        this->rele->setStyleSheet("QLabel{border-radius: 5px; background: green;}");
    } else {
        this->rele->setStyleSheet("QLabel{border-radius: 5px; background: red;}");
    }
}

void ListElement::setTime(QString &label)
{
    this->time->setText("Время:" + label);
     strTime = label;

}

void ListElement::setCamera(QString &label)
{
    this->cam->setText("Камера:" + label);
     strCam = label;
}

int ListElement::getId()
{
    return this->idFase;
}
ListElement::~ListElement()
{
    delete text;
    delete photo;
}
