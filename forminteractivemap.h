#ifndef FORMINTERACTIVEMAP_H
#define FORMINTERACTIVEMAP_H

#include <QWidget>
#include <QMatrix>
#include "addnewmap.h"
#include "customscene.h"
#include "listelement.h"

namespace Ui {
class FormInteractiveMap;
}

class FormInteractiveMap : public QWidget
{
    Q_OBJECT

public:
    explicit FormInteractiveMap(QWidget *parent = nullptr);
    ~FormInteractiveMap();
    std::vector<std::string> getNamePage();
    std::vector<QString> getNamePoint();
    void savePlan(int index);
    void showItemFromList(int index);
    void deleteItemFromList(int index);
    void connsetSocket(QString ip_server);
    std::vector<std::vector<qreal>> getMat();
    QWidget *parentM;

    void drowLine(std::vector<QString>, std::vector<int>);
signals:
    void eventFaceReco(QString msg);
    void eventFaceDetect(QString msg);
    void eventSCUD(QString msg);
    void settingView(ListElementForScene *elem);
public slots:
    void changePage(QString name);
    void activateCamAccess(QString cam);
    void activateCamDetect(QString cam);
    void activateReleAccess(QString rele);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_9_clicked();

private:
    QGraphicsView * view;
    CustomScene* scene;
    bool flag = false;
    void setConnect(CustomScene *scene);
    Ui::FormInteractiveMap *ui;
    QHash<QString, CustomScene*> list_tap;
    std::vector<QGraphicsLineItem*> line_path;
};

#endif // FORMINTERACTIVEMAP_H
