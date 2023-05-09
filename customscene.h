#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QMetaObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "addnewelementinscene.h"
#include "form_log.h"
#include "listelement.h"
#include "settingsarea.h"
#include "settingsperimetr.h"

enum changeMode {
    Move,
    Scale,
    Rotation,
    Null
};

class CustomGraphicselEvatorItem : public QObject, public QGraphicsPixmapItem
{
   Q_OBJECT
public:
    explicit CustomGraphicselEvatorItem(QString nameObj, QString name = "", QObject *parent = nullptr);
    void setMode(changeMode mode) {
        this->mode = mode;
    }
    QString getNameItem();
    QString getNameObject();
    void setNameObject(QString new_name){ this->nameObject = new_name; }
signals:
    void changePage(QString name_page);
private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QString nameObject;
    QString nameItem;
    qreal radius;
    changeMode mode;
};

class CustomGraphicsStreamItem : public QObject, public QGraphicsPixmapItem
{
   Q_OBJECT
public:
    explicit CustomGraphicsStreamItem(std::string url,
                                      QString id = "",
                                      QString objId = "",
                                      QObject *parent = nullptr);
   ~CustomGraphicsStreamItem();

    QString getName(){ return this->nameItem;}
    QString getNameObject(){ return this->nameObject;}
    void setNameObject(QString name, std::string url);
    void setMode(changeMode mode)
    {
        this->mode = mode;
    }
    void sendSize(int w, int h);
public slots:
    void updatePixmap(QPixmap pixmap);

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QString nameObject;
    QString nameItem;
    changeMode mode;
};


class CustomGraphicsPixmapItem : public QObject, public QGraphicsPixmapItem
{
   Q_OBJECT
public:
    explicit CustomGraphicsPixmapItem(QString stateNormal,
                                      QString stateAccess,
                                      QString stateDetection,
                                      qreal radius,
                                      int type,
                                      QString id = "",
                                      QString objId = "",                                      
                                      QObject *parent = nullptr);
    void setMode(changeMode mode);
    QString getName();
    QString getObjName();
    void setObjName(QString name);
    int getType();
    void addEvent(QString event);
    void addLine(QGraphicsLineItem *, int);
    void delLine(QGraphicsLineItem *);
    std::vector<QGraphicsLineItem *>& getLine() {
        return lines;
    }
    void setNormal();
    void setAccess();
    void setDetection();

    ~CustomGraphicsPixmapItem();
signals:
    void sendPixmap(QPixmap pixmap, int id, QString name, QString date);
    void sendXYR(QString mac,int x, int y, int r, QString mac_wi_fi);
public slots:
    void start_wifi();
    void stop_wifi();

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QString nameObject;
    QString nameItem;
    changeMode mode;
    qreal radius;

    int type;
    int id;
    std::vector<QGraphicsLineItem *> lines;
    std::vector<int> lines_point;
    QString stateNormal;
    QString stateAccess;
    QString stateDetection;
    QTimer *timer;
    QTimer *timer_data;
};

class CustomGraphicsRectItem : public QObject, public QGraphicsRectItem
{
   Q_OBJECT
public:
    explicit CustomGraphicsRectItem(QPointF pos_1, QPointF pos_2, QString nameItem, QObject *parent = nullptr);
    void showSettingItem(QList<QString> ListCam, QHash<QString, CustomGraphicsPixmapItem *> list);
    CustomGraphicsRectItem(QRectF rect, QString nameItem, QObject *parent = nullptr);
    void addElementInOutrect(CustomGraphicsPixmapItem *object);
    void addElementInInrect(CustomGraphicsPixmapItem *object);
    QString getName(){return this->nameItem;}
    void setMode(changeMode mode);
    void clearListInrect();
    void clearListOutrect();
    void deleteEvent(int id);

    ~CustomGraphicsRectItem();
private:
    void updateEventList();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QHash<int, QGraphicsPixmapItem *> itemEvent;
    QHash<CustomGraphicsPixmapItem *, QMetaObject::Connection> list_element_in;
    QHash<CustomGraphicsPixmapItem *, QMetaObject::Connection> list_element_out;

    SettingsPerimetr *formSetting = nullptr;
    SettingsArea form;
    QString nameItem;
    changeMode mode;
    qreal radius;

};


class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomView(QWidget *parent = nullptr);
    virtual bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void ShowContextMenu(const QPoint &);
};

class CustomSceneView : public QGraphicsScene
{
   Q_OBJECT
public:
    explicit CustomSceneView(bool menu = true, QObject *parent = nullptr);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void handleWheelOnGraphicsScene(QGraphicsSceneWheelEvent* scrollevent);
    ~CustomSceneView();

signals:
    void sendRect(QRectF zone);
    void saveCut(QRectF zone);
    void cut(QRectF zone);
    void normal();
    void save();
    void back();
    void zoom(int delta, QPointF point);

public slots:

private:
    bool menu;
    QPointF posCenter;
    QGraphicsRectItem *zone;
    bool draw;
};

class CustomScene : public QGraphicsScene
{
   Q_OBJECT
public:
    explicit CustomScene(bool manu = false, QString name = "" ,QObject *parent = nullptr);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    void setModeItem(changeMode mode);
    void startItem();
    void stopItem();

    QHash<QString, CustomGraphicsPixmapItem *> getList();
    void deleteItemInList(QString kay);
    QHash<QString, CustomGraphicsRectItem *> getListPerimeter();
    void deleteItemInListPerimeter(QString kay);
    QHash<QString, CustomGraphicsStreamItem *> getListStream();
    void deleteItemInListStream(QString kay);
    QHash<QString, CustomGraphicselEvatorItem *> getListElevator();
    void deleteItemInListElevator(QString kay);

    void setNameScene(QString name) { this->nameScene = name;}
    QString getNameScene() { return this->nameScene; }

    void setBackground(QPixmap map);
    QPixmap getBackground();
    void addRectInScene(QString name, QPointF scenePos, QRectF rect);
    CustomGraphicsPixmapItem *addItemInScene(int type, QString name, QString obj, QPointF scenePos);
    void addItemInScene(QGraphicsSceneMouseEvent *event,
                        int type,
                        std::vector<std::string> list);
    void addStreamInScene(QGraphicsSceneMouseEvent *event, std::vector<std::string> list);
    CustomGraphicselEvatorItem *addEvatorInScene(QString nameObj, QString nameItem);
    CustomGraphicsStreamItem *addStreamInScene(QString nameObj, QString nameItem);

signals:
    void addNewItem(CustomGraphicsPixmapItem *);
    void addNewZone(CustomGraphicsRectItem *);
    void addNewStream(CustomGraphicsStreamItem *);
    void addNewElevator(CustomGraphicselEvatorItem *);
    void signalTargetCoordinate(QPointF point);

public slots:

private:
    std::pair<double, double> calcCoordsFrom3Routers(std::pair<double, double> td1, std::pair<double, double> td2, std::pair<double, double> td3, double r1, double r2, double r3);
    QString get_pixmap_detect(int type);
    QString get_pixmap_access(int type);
    QString get_pixmap_normal(int type);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QHash<QString, CustomGraphicsPixmapItem *> items;
    QHash<QString, CustomGraphicsRectItem *> itemsPerimeter;
    QHash<QString, CustomGraphicsStreamItem *> itemsStream;
    QHash<QString, CustomGraphicselEvatorItem *> itemsElevator;

    QGraphicsEllipseItem* r1;
    QGraphicsEllipseItem* r2;
    QGraphicsEllipseItem* r3;

    QGraphicsEllipseItem* p1;
    QGraphicsEllipseItem* p2;
    QGraphicsEllipseItem* p3;

    QGraphicsPixmapItem *background;
    QString nameScene;
    QObject *parentM;
    changeMode mode;
    bool manu;
};


#endif // CUSTOMSCENE_Hs
