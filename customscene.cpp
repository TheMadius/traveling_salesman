#include "customscene.h"
#include <QDebug>
#include <QMenu>
#include <QtMath>
#include <cmath>
#include <QPainter>
#include "forminteractivemap.h"

CustomGraphicselEvatorItem::CustomGraphicselEvatorItem(QString nameObj,
                                                       QString name,
                                                       QObject *parent):
    QObject(parent),
    QGraphicsPixmapItem()
{
    this->nameItem = name;
    this->nameObject = nameObj;

    this->mode = Move;

    this->setPixmap(QPixmap(":/qss_icons/dark/rc/elevator.png"));
    int w = this->pixmap().rect().width();
    int h = this->pixmap().rect().height();
    this->radius = qSqrt(w * w + h * h);
}

QString CustomGraphicselEvatorItem::getNameItem()
{
    return this->nameItem;
}

QString CustomGraphicselEvatorItem::getNameObject()
{
    return this->nameObject;
}

void CustomGraphicselEvatorItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Move: {
        this->setPos(mapToScene(event->pos()));
        break;
    }
    case Scale: {
        qreal w = qAbs(event->scenePos().x() - this->pos().x());
        qreal h = qAbs(event->scenePos().y() - this->pos().y());
        qreal r = qSqrt(w*w + h*h);
        this->setScale(r / this->radius);
        break;
    }
    case Rotation:{
        break;
    }
     default: {
        break;
    }
    }
}

void CustomGraphicselEvatorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Move:
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        break;
    case Scale:
        break;
    case Rotation:
        break;
    case Null:
        emit this->changePage(this->nameObject);
         break;
    default:
        break;
    }
    Q_UNUSED(event);
}

void CustomGraphicselEvatorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

CustomGraphicsStreamItem::CustomGraphicsStreamItem(std::string url, QString id , QString objId, QObject *parent):
    QObject(parent),
    QGraphicsPixmapItem()
{
    nameObject = objId;
    nameItem = id;
    this->setToolTip(nameItem + "/" + nameObject);
    mode = Move;
}

void CustomGraphicsStreamItem::setNameObject(QString name, std::string url)
{
    this->nameObject = name;
}

void CustomGraphicsStreamItem::updatePixmap(QPixmap pixmap)
{
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::blue);
    QPainter painter(&pixmap);
    painter.setPen(pen);
    painter.drawRect(pixmap.rect());

    this->setPixmap(pixmap);
}

void CustomGraphicsStreamItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Move: {
        this->setPos(mapToScene(event->pos()));
        break;
    }
    case Scale: {
        qreal w = (event->scenePos().x() - this->pos().x());
        qreal h = (event->scenePos().y() - this->pos().y());
        break;
    }
     default:
        break;
    }
}

void CustomGraphicsStreamItem::sendSize(int w, int h)
{
}

void CustomGraphicsStreamItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void CustomGraphicsStreamItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

CustomGraphicsStreamItem::~CustomGraphicsStreamItem()
{
}

CustomGraphicsRectItem::CustomGraphicsRectItem(QRectF rect, QString nameItem, QObject *parent):
    QObject(parent),
    QGraphicsRectItem()
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::DashLine);

    this->setRect(rect);
    this->setPen(pen);
    qreal w = rect.width();
    qreal h = rect.height();
    this->radius = qSqrt(w * w + h * h);
    this->mode = Move;

    form.setTitle(nameItem);
    connect(&form, &SettingsArea::deletePerson, [&](int id){
        this->deleteEvent(id);
    });

    this->nameItem = nameItem;

    Q_UNUSED(parent);
}

void CustomGraphicsRectItem::clearListInrect()
{
    for (auto t = list_element_in.begin(); t != list_element_in.end(); ) {
        disconnect(t.value());
        ++t;
    }
    list_element_in.clear();
}

void CustomGraphicsRectItem::clearListOutrect()
{
    for (auto t = list_element_out.begin(); t != list_element_out.end(); ) {
            disconnect(t.value());
            ++t;
    }
    list_element_out.clear();
}

void CustomGraphicsRectItem::showSettingItem(QList<QString> ListCam, QHash<QString, CustomGraphicsPixmapItem *> list)
{
    if(formSetting == nullptr)
        formSetting = new SettingsPerimetr(ListCam);

    formSetting->setTitle(this->nameItem);
    formSetting->exec();

    if (formSetting->result() == QDialog::Accepted) {
        auto zona = this;
        zona->clearListInrect();
        zona->clearListOutrect();

        for(auto it : formSetting->inside)
            zona->addElementInInrect(list[it]);

        for(auto it : formSetting->outside)
            zona->addElementInOutrect(list[it]);
    }
}

CustomGraphicsRectItem::CustomGraphicsRectItem(QPointF pos_1, QPointF pos_2, QString nameItem, QObject *parent):
    QObject(parent),
    QGraphicsRectItem()
{
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::DashLine);

    this->setRect(QRectF(pos_1, pos_2));
    this->setPen(pen);
    qreal w = qAbs(pos_1.x() - pos_2.x());
    qreal h = qAbs(pos_1.y() - pos_2.y());
    this->radius = qSqrt(w * w + h * h);
    this->mode = Move;

    this->nameItem = nameItem;

    form.setTitle(nameItem);
    connect(&form, &SettingsArea::deletePerson, [&](int id){
        this->deleteEvent(id);
    });

    Q_UNUSED(parent);
}

void CustomGraphicsRectItem::setMode(changeMode mode)
{
    this->mode = mode;
}

void CustomGraphicsRectItem::addElementInOutrect(CustomGraphicsPixmapItem *object)
{
    auto conn = connect(object, &CustomGraphicsPixmapItem::sendPixmap, [&](QPixmap pixmap, int id, QString name, QString date){
        if (this->itemEvent.contains(id))
            return;
        auto itemPixmap = new QGraphicsPixmapItem();
        QPen pen;
        pen.setWidth(4);
        pen.setColor(Qt::blue);
        QPainter painter(&pixmap);
        painter.setPen(pen);
        painter.drawRect(pixmap.rect());
        itemPixmap->setPixmap(pixmap);
        this->itemEvent.insert(id, itemPixmap);
        this->scene()->addItem(itemPixmap);
        itemPixmap->setScale(0.62);
        updateEventList();

        this->form.addElement(pixmap, id, name, date);
    });

    list_element_out.insert(object ,conn);
}

void CustomGraphicsRectItem::deleteEvent(int id)
{
    this->scene()->removeItem(itemEvent[id]);
    delete itemEvent[id];
    this->itemEvent.remove(id);
    updateEventList();
}

void CustomGraphicsRectItem::addElementInInrect(CustomGraphicsPixmapItem *object)
{
    auto conn = connect(object, &CustomGraphicsPixmapItem::sendPixmap, [&](QPixmap pixmap, int id, QString name, QString date){
        qDebug() << "Person out";
        if (this->itemEvent.contains(id)) {

        form.deleteElement(id);
        deleteEvent(id);
        }
    });

    list_element_in.insert(object, conn);
}
void CustomGraphicsRectItem::updateEventList()
{
    if (this->scene() == nullptr) {
        return;
    }
    auto StartPos = this->pos();
    StartPos.setX(StartPos.x() + this->rect().width());

    StartPos.setX(StartPos.x() - 45);
    StartPos.setY(StartPos.y() - 60);

    for (auto it : this->itemEvent) {
        it->setPos(StartPos);
        StartPos.setX(StartPos.x() - (45 + 8));
    }
}

void CustomGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Move: {
        this->setPos(mapToScene(event->pos()));        
        break;
    }
    case Scale: {
        this->setRect(QRectF(this->rect().topLeft(), event->pos()));
        break;
    }
     default:
        break;
    }
    updateEventList();
}

void CustomGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Null: {
        this->form.show();
        break;
    }
     default:
            this->setCursor(QCursor(Qt::ClosedHandCursor));
        break;
    }
    Q_UNUSED(event);
}

void CustomGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

CustomGraphicsRectItem::~CustomGraphicsRectItem()
{
    for (auto it : this->itemEvent) {
        delete it;
    }
    delete this->formSetting;
}

const char * req_sql_get_mac = "SELECT packet_count ,mac, rssi_array FROM probe_request WHERE timestamp = (SELECT max(timestamp) FROM probe_request WHERE mac = 'DC-CC-E6-F1-5B-CB' and (ch = 1 or ch = 3 or ch = 6 or ch = 11 )) and (ch = 1 or ch = 3 or ch = 6 or ch = 11 ) and mac = 'DC-CC-E6-F1-5B-CB' and \"radarDataId\" = ";
const char * req_sql_get_id = "SELECT id FROM radar_data WHERE mac_id = '";
CustomGraphicsPixmapItem::CustomGraphicsPixmapItem(QString stateNormal,
                                                   QString stateAccess,
                                                   QString stateDetection,
                                                   qreal radius,
                                                   int type,
                                                   QString id ,
                                                   QString objId,
                                                   QObject *parent) :
    QObject(parent),
    QGraphicsPixmapItem()
{
    this->stateNormal = stateNormal;
    this->stateAccess = stateAccess;
    this->stateDetection = stateDetection;

    this->type = type;

    setNormal();
    nameObject = objId;
    nameItem = id;
    this->radius = radius;
    this->setToolTip(nameItem + "/" + nameObject);
    mode = Move;
    timer = new QTimer();
    timer_data = new QTimer();

    connect(timer, &QTimer::timeout, [&](){
        setNormal();
        timer->stop();
    });

    connect(timer_data, &QTimer::timeout, [&](){
        //Получение и преобразование в метры
    });

}

int CustomGraphicsPixmapItem::getType()
{
    return this->type;
}

void CustomGraphicsPixmapItem::addLine(QGraphicsLineItem * item, int num) {
    this->lines.push_back(item);
    this->lines_point.push_back(num);
}

void CustomGraphicsPixmapItem::delLine(QGraphicsLineItem * item) {
    for(int i = 0; i < lines.size(); i ++) {
        if (lines[i] == item) {
            lines.erase(lines.begin() +i);
            lines_point.erase(lines_point.begin() + i);
        }
    }
}

void CustomGraphicsPixmapItem::addEvent(QString event)
{

}

CustomGraphicsPixmapItem::~CustomGraphicsPixmapItem()
{
    delete timer;
    for(auto it : lines) {
        delete it;
    }
}

void CustomGraphicsPixmapItem::setNormal()
{
    this->setPixmap(QPixmap(stateNormal));
}

void CustomGraphicsPixmapItem::setAccess()
{
    this->setPixmap(QPixmap(stateAccess));
    timer->stop();
    timer->start(500);
}

void CustomGraphicsPixmapItem::stop_wifi() {
    timer_data->stop();
}

void CustomGraphicsPixmapItem::start_wifi() {
}

void CustomGraphicsPixmapItem::setDetection()
{
    this->setPixmap(QPixmap(stateDetection));
    timer->stop();
    timer->start(500);
}

void CustomGraphicsPixmapItem::setMode(changeMode mode)
{
    this->mode = mode;
}

QString CustomGraphicsPixmapItem::getObjName()
{
    return this->nameObject;
}

void CustomGraphicsPixmapItem::setObjName(QString name)
{
    this->nameObject = name;
    this->setToolTip(nameItem + "/" + nameObject);
}

QString CustomGraphicsPixmapItem::getName()
{
    return this->nameItem;
}

void CustomGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Move: {
        this->setPos(mapToScene(event->pos()));
        for(int i = 0; i < this->lines.size(); i++) {
            if (lines_point[i] == 1) {
                auto line = lines[i]->line();
                line.setP1(mapToScene(event->pos()));
                lines[i]->setLine(line);
            } else {
                auto line = lines[i]->line();
                line.setP2(mapToScene(event->pos()));
                lines[i]->setLine(line);
            }
        }
        break;
    }
    case Scale: {
        qreal w = qAbs(event->scenePos().x() - this->pos().x());
        qreal h = qAbs(event->scenePos().y() - this->pos().y());
        qreal r = qSqrt(w*w + h*h);
        this->setScale(r / this->radius);
        break;
    }
    case Rotation:{
        qreal sign = (this->pos().y() < event->scenePos().y())?1: -1;
        qreal w = (event->scenePos().x() - this->pos().x());
        qreal h = (event->scenePos().y() - this->pos().y());
        qreal r = qSqrt(w*w + h*h);
        qreal scalar = w / r;
        this->setRotation(sign * ((qAcos(scalar)*180)/M_PI));
        break;
    }
     default:
        break;
    }
}

void CustomGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->mode) {
    case Move:
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        break;
    case Scale:
        break;
    case Rotation:
        break;
    case Null:
         break;
    default:
        break;
    }
    Q_UNUSED(event);
}

void CustomGraphicsPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}


CustomView::CustomView(QWidget *parent):
       QGraphicsView(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &CustomView::customContextMenuRequested,
            this, &CustomView::ShowContextMenu);

    installEventFilter(this);
}

bool CustomView::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel) {
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
}

void CustomView::ShowContextMenu(const QPoint &pos)
{

}

CustomScene::CustomScene(bool manu, QString name, QObject *parent) :
    QGraphicsScene()
{
    this->manu = manu;
    this->mode = Move;
    this->parentM = parent;
    this->nameScene = name;

    this->background = new QGraphicsPixmapItem();

    this->r1 = new QGraphicsEllipseItem();
    this->r2 = new QGraphicsEllipseItem();
    this->r3 = new QGraphicsEllipseItem();

    this->p1 = new QGraphicsEllipseItem();
    this->p2 = new QGraphicsEllipseItem();
    this->p3 = new QGraphicsEllipseItem();

    this->addItem(background);

    this->addItem(r1);
    this->addItem(r2);
    this->addItem(r3);

    this->addItem(p1);
    this->addItem(p2);
    this->addItem(p3);
}

QHash<QString, CustomGraphicsPixmapItem *> CustomScene::getList()
{
    return this->items;
}

QHash<QString, CustomGraphicsRectItem *> CustomScene::getListPerimeter()
{
    return this->itemsPerimeter;
}

QHash<QString, CustomGraphicsStreamItem *> CustomScene::getListStream()
{
    return this->itemsStream;
}

void CustomScene::setModeItem(changeMode mode)
{
    this->mode = mode;
    for (auto it : this->items) {
        it->setMode(mode);
    }
}

void CustomScene::stopItem() {
    this->mode = mode;
    for (auto it : this->items) {
        it->stop_wifi();
    }
}

void CustomScene::startItem()
{
    this->mode = mode;
    for (auto it : this->items) {
        it->start_wifi();
    }
}



QString CustomScene::get_pixmap_normal(int type)
{
    switch (type) {
    case 0:
        return ":/qss_icons/dark/rc/cam.png";
    case 1:
        return ":/qss_icons/dark/rc/tur.png";
    case 2:
        return ":/qss_icons/dark/rc/door.png";
    case 3:
        return ":/qss_icons/dark/rc/sensor.png";
    }
}

QString CustomScene::get_pixmap_access(int type)
{
    switch (type) {
    case 0:
        return ":/qss_icons/dark/rc/cam_g.png";
    case 1:
        return ":/qss_icons/dark/rc/tur_g.png";
    case 2:
        return ":/qss_icons/dark/rc/door_g.png";
    case 3:
        return ":/qss_icons/dark/rc/sensor_g.png";
    }
}

QString CustomScene::get_pixmap_detect(int type)
{
    switch (type) {
    case 0:
        return ":/qss_icons/dark/rc/cam_r.png";
    case 1:
        return ":/qss_icons/dark/rc/tur_r.png";
    case 2:
        return ":/qss_icons/dark/rc/door_r.png";
    case 3:
        return ":/qss_icons/dark/rc/sensor_r.png";
    }
}


#include <QHash>
#include <QList>
#include <QGraphicsEllipseItem>
QHash<QString, QHash<QString, std::pair<std::pair<double, double>, double>>> map_mac;
QHash<QString, QGraphicsEllipseItem *> map_point;
QList<QString> wi_fis;

CustomGraphicsPixmapItem* CustomScene::addItemInScene(int type, QString name, QString obj, QPointF scenePos)
{
    QString path_pixmap_normal = get_pixmap_normal(type);
    QString path_pixmap_access = get_pixmap_access(type);
    QString path_pixmap_detect = get_pixmap_detect(type);

    auto pixmap_item = QPixmap(path_pixmap_normal);
    qreal r = qSqrt(pixmap_item.width()*pixmap_item.width() + pixmap_item.height() * pixmap_item.height());

    CustomGraphicsPixmapItem *item = new CustomGraphicsPixmapItem(path_pixmap_normal,
                                                                  path_pixmap_access,
                                                                  path_pixmap_detect,
                                                                  r, type, name,
                                                                  obj);
    item->setPos(scenePos);
    item->setMode(this->mode);
    this->addItem(item);

    items.insert(name, item);
    connect(item, &CustomGraphicsPixmapItem::sendXYR, [&](QString mac,int x, int y, int r, QString mac_wi_fi){

    });

    emit this->addNewItem(item);
    return item;
}

void CustomScene::addItemInScene(QGraphicsSceneMouseEvent *event,
                                 int type,
                                 std::vector<std::string> list)
{
    static int i = 0;

    QString path_pixmap_normal = get_pixmap_normal(type);
    QString path_pixmap_access = get_pixmap_access(type);
    QString path_pixmap_detect = get_pixmap_detect(type);
    auto pixmap_item = QPixmap(path_pixmap_normal);
    qreal r = qSqrt(pixmap_item.width() * pixmap_item.width() + pixmap_item.height() * pixmap_item.height());

    CustomGraphicsPixmapItem *item = new CustomGraphicsPixmapItem(path_pixmap_normal,
                                                                  path_pixmap_access,
                                                                  path_pixmap_detect,
                                                                  r, type, QString::number(++i),
                                                                  QString::number(i));
    item->setPos(event->scenePos());
    item->setMode(this->mode);
    this->addItem(item);

    for(auto it_1: items) {
        auto line = this->addLine(it_1->pos().x(),it_1->pos().y(),item->pos().x(),item->pos().y());
        it_1->addLine(line, 1);
        item->addLine(line, 2);
    }

    items.insert(QString::number(i), item);
    emit this->addNewItem(item);
}

CustomGraphicsStreamItem *CustomScene::addStreamInScene(QString nameObj, QString nameItem)
{
    std::string url = "";
    CustomGraphicsStreamItem *item = new CustomGraphicsStreamItem(url, nameItem, nameObj);
    item->setMode(this->mode);
    this->addItem(item);
    itemsStream.insert(nameItem, item);
    emit this->addNewStream(item);
    return item;
}

void CustomScene::addStreamInScene(QGraphicsSceneMouseEvent *event,
                                  std::vector<std::string> list)
{
    AddNewElementInScene *form = new AddNewElementInScene(list);
    form->exec();

    if (form->result() == QDialog::Accepted) {
        std::string url = "";
        CustomGraphicsStreamItem *item = new CustomGraphicsStreamItem(url, form->name,
                                                                      form->obj);
        item->setPos(event->scenePos());
        item->setMode(this->mode);
        this->addItem(item);
        itemsStream.insert(form->name, item);
        emit this->addNewStream(item);
    }
}

void CustomScene::addRectInScene(QString name, QPointF scenePos, QRectF rect)
{
    CustomGraphicsRectItem *item = new CustomGraphicsRectItem(rect, name);
    item->setPos(scenePos);
    item->setMode(this->mode);
    this->addItem(item);
    this->itemsPerimeter.insert(name, item);
    emit this->addNewZone(item);
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
    if (manu) {
        if (event->button() == Qt::RightButton) {
            std::vector<std::string> list = {};
            addItemInScene(event, 3, list);
        }
    }
}

CustomGraphicselEvatorItem *CustomScene::addEvatorInScene(QString nameObj, QString nameItem)
{
    CustomGraphicselEvatorItem *item = new CustomGraphicselEvatorItem(nameObj, nameItem);

    connect(item, &CustomGraphicselEvatorItem::changePage, ((FormInteractiveMap *)(this->parentM)), &FormInteractiveMap::changePage);
    item->setMode(this->mode);
    this->addItem(item);
    this->itemsElevator.insert(nameItem, item);
    return item;
}

QHash<QString, CustomGraphicselEvatorItem *> CustomScene::getListElevator()
{
    return itemsElevator;
}

void CustomScene::setBackground(QPixmap map)
{
    this->background->setPixmap(map);
}

QPixmap CustomScene::getBackground()
{
    return this->background->pixmap();
}

void CustomScene::deleteItemInList(QString kay)
{
    auto item = this->items[kay];
    this->items.remove(kay);
    if (item != nullptr) {
        auto lines = item->getLine();
        for(auto &it: items) {
            for(auto line: lines) {
                it->delLine(line);
            }
        }
    }
}

void CustomScene::deleteItemInListPerimeter(QString kay)
{
    this->itemsPerimeter.remove(kay);
}

void CustomScene::deleteItemInListStream(QString kay)
{
    this->itemsStream.remove(kay);
}

void CustomScene::deleteItemInListElevator(QString kay)
{
    this->itemsElevator.remove(kay);
}

void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "drop scene";
}

CustomSceneView::CustomSceneView(bool menu, QObject *parent):
        QGraphicsScene()
{
    zone = new QGraphicsRectItem();
    this->addItem(zone);
    draw = false;
    zone->setZValue(1);
    this->menu = menu;

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::white);
    pen.setStyle(Qt::DashLine);
    zone->setPen(pen);
    installEventFilter(this);
}

void CustomSceneView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (draw) {
           qreal posX_1 = posCenter.x();
           qreal posY_1 = posCenter.y();
           qreal posX_2 = event->scenePos().x();
           qreal posY_2 = event->scenePos().y();
           QPointF posTopLeft, posBottonRight;

           posTopLeft.setX(qMin(posX_1, posX_2));
           posTopLeft.setY(qMin(posY_1, posY_2));

           posBottonRight.setX(qMax(posX_1, posX_2));
           posBottonRight.setY(qMax(posY_1, posY_2));

           zone->setRect(QRectF(posTopLeft, posBottonRight));
    }
}

void CustomSceneView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (menu) {
        if (event->button() == Qt::RightButton) {
            QMenu contextMenu("Меню");
            QAction action1("Экспортировать...", this);
            QAction action2("К исходному размеру", this);
            QAction action3("К предыдущему размеру", this);

            connect( &action1, &QAction::triggered, [&](){
                emit save();
            });

            connect( &action2, &QAction::triggered, [&](){
                emit normal();
            });

            connect( &action3, &QAction::triggered, [&](){
                emit back();
            });

            contextMenu.addAction(&action1);
            contextMenu.addAction(&action3);
            contextMenu.addAction(&action2);

            contextMenu.exec(event->screenPos());
            return;
        }
    }
    posCenter = event->scenePos();
    zone->setRect(QRectF(posCenter, posCenter));
    this->draw = true;
}

void CustomSceneView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->draw = false;
    if (menu) {
        QMenu contextMenu("Меню");
        QAction action1("Экспортировать выделенную зону...", this);
        QAction action2("Увеличить", this);

        connect( &action1, &QAction::triggered, [&](){
            emit saveCut(this->zone->rect());
            this->zone->setRect(QRectF());
        });
        connect( &action2, &QAction::triggered, [&](){
            emit cut(this->zone->rect());
            this->zone->setRect(QRectF());
        });

        contextMenu.addAction(&action2);
        contextMenu.addAction(&action1);

        contextMenu.exec(event->screenPos());
        this->zone->setRect(QRectF());
    }
    emit this->sendRect(this->zone->rect());
    this->zone->setRect(QRectF());
}

CustomSceneView::~CustomSceneView()
{

}

bool CustomSceneView::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneWheel)
    {
        QGraphicsSceneWheelEvent *scrollevent = static_cast<QGraphicsSceneWheelEvent *>(event);
        handleWheelOnGraphicsScene(scrollevent);
        return true;
    }
  return false;
}


void CustomSceneView::handleWheelOnGraphicsScene(QGraphicsSceneWheelEvent* scrollevent)
{
   emit zoom(scrollevent->delta(), scrollevent->scenePos());
}
