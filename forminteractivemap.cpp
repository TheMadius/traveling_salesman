#include "forminteractivemap.h"
#include "ui_forminteractivemap.h"
#include <QGraphicsView>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
#include <QLabel>
#include <QDebug>
#include <QStandardPaths>
#include <QFileDialog>
#include <QBuffer>
#include <QList>
#include <QString>
#include <QMessageBox>
#include "accesspointsettings.h"

#include <opencv2/imgproc.hpp>

#include "addnewelementinscene.h"
#include "settingsperimetr.h"
#include <utility>
//
//

QImage cvMatToQImage(const cv::Mat &frame ) {
    return QImage( (const unsigned char*)(frame.data), frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888).rgbSwapped();
}

FormInteractiveMap::FormInteractiveMap(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::FormInteractiveMap)
{
    ui->setupUi(this);
    this->parentM = parent;

    this->ui->tabWidget->setTabsClosable(true);
    connect(this->ui->tabWidget, &QTabWidget::tabCloseRequested, [&](int index){
        int button = QMessageBox::question(this,
                                           QString::fromLocal8Bit("Сохранение?"),
                                           QString::fromLocal8Bit("Сохранить файл?"),
                                           QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::Yes) {
            savePlan(index);
        }
        deleteItemFromList(index);
        list_tap.remove(this->ui->tabWidget->tabText(index));
        this->ui->tabWidget->removeTab(index);
    });

    this->ui->tableWidget->setFixedWidth(400);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    this->setAcceptDrops(true);

    this->ui->tabWidget->setAcceptDrops(true);

    connect(this, &FormInteractiveMap::eventFaceReco, this, &FormInteractiveMap::activateCamAccess);
    connect(this, &FormInteractiveMap::eventFaceDetect, this, &FormInteractiveMap::activateCamDetect);

    view = new QGraphicsView(this);
    scene = new CustomScene(true, "Граф", this);

    setConnect(scene);

    view->setScene(scene);
    view->setAcceptDrops(true);

    scene->setSceneRect(0,0,1920,1080);

    this->ui->tabWidget->addTab(view, "Граф");
    list_tap.insert("Граф", scene);
    this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count() - 1);
    view->setBackgroundBrush(Qt::white);
    view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}

void FormInteractiveMap::connsetSocket(QString ip_server)
{

}

std::vector<std::string> FormInteractiveMap::getNamePage()
{
    std::vector<std::string> res;
    for ( int i = 0; i < this->ui->tabWidget->count(); i++ ) {
        res.push_back(this->ui->tabWidget->tabText(i).toStdString());
    }
    return res;
}

void FormInteractiveMap::showItemFromList(int index)
{
    if (index >= list_tap.size())
        return;
    auto name_scene = this->list_tap[this->ui->tabWidget->tabText(index)]->getNameScene();
    for (int i = 0; i < this->ui->tableWidget->rowCount(); ++i)
    {
        auto item = ((ListElementForScene *)ui->tableWidget->cellWidget(i, 0));
        if ( item->getNameScene() == name_scene ) {
            ui->tableWidget->showRow(i);
        } else {
            ui->tableWidget->hideRow(i);
        }
    }
}

void FormInteractiveMap::deleteItemFromList(int index)
{
    auto name_scene = this->list_tap[this->ui->tabWidget->tabText(index)]->getNameScene();
    for (int i = this->ui->tableWidget->rowCount() - 1; i >= 0 ; --i)
    {
        auto item = ((ListElementForScene *)ui->tableWidget->cellWidget(i, 0));
        if ( item->getNameScene() == name_scene ) {
            ui->tableWidget->removeRow(i);
        }
    }
}

void FormInteractiveMap::changePage(QString name)
{
    for ( int i = 0; i < this->ui->tabWidget->count(); i++ ) {
        if (this->ui->tabWidget->tabText(i) == name) {
            this->ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }
}

FormInteractiveMap::~FormInteractiveMap()
{
    delete ui;
}

void FormInteractiveMap::activateCamDetect(QString cam)
{
    QStringList event = cam.split(' ');
    int index = this->ui->tabWidget->currentIndex();
    if ( index < 0) {
        return;
    }

    auto list = this->list_tap[this->ui->tabWidget->tabText(index)]->getList();
    for (auto it : list) {
        if (it->getObjName() == event[1] ) {
            it->setDetection();
            it->addEvent(cam);
        }
    }
}

void FormInteractiveMap::activateCamAccess(QString cam)
{
    QStringList event = cam.split(' ');
    int index = this->ui->tabWidget->currentIndex();
    if ( index < 0) {
        return;
    }
    auto list = this->list_tap[this->ui->tabWidget->tabText(index)]->getList();
    for (auto it : list) {
        if (it->getObjName() == event[1] ) {
            it->setAccess();
            it->addEvent(cam);
        }
    }
}

void FormInteractiveMap::activateReleAccess(QString rele)
{
    QStringList event = rele.split(' ');

    int index = this->ui->tabWidget->currentIndex();
    if ( index < 0) {
        return;
    }
    auto list = this->list_tap[this->ui->tabWidget->tabText(index)]->getList();
    for (auto it : list) {
        if (it->getObjName() == event[1] ) {
            it->setAccess();
            it->addEvent(rele);
        }
    }
}

qreal euclidean_distance(QPointF pos_1, QPointF pos_2) {
    auto dx = pos_1.x() - pos_2.x();
    auto dy = pos_1.y() - pos_2.y();
    return sqrt((dx*dx) + (dy*dy));
}

std::vector<std::vector<qreal>> FormInteractiveMap::getMat() {
    std::vector<std::vector<qreal>> mat;
    auto item = this->scene->getList();
    for(auto it1: item) {
        std::vector<qreal> line;
        for(auto it2: item) {
            line.push_back(euclidean_distance(it1->pos(),it2->pos()));
        }
        mat.push_back(line);
    }
    return mat;
}

std::vector<QString> FormInteractiveMap::getNamePoint() {
    std::vector<QString> mat;
    auto item = this->scene->getList();
    for(auto it1: item) {
        mat.push_back(it1->getName());
    }
    return mat;
}

qreal dist(std::vector<std::vector<qreal>> &mat, std::vector<int> trace) {
    qreal res = 0;
    for(int i = 0; i < trace.size() - 1; i++){
        res += mat[trace[i]][trace[i + 1]];
    }
    return res;
}

template <typename T>
T get(std::list<T> _list, int _i){
    auto it = _list.begin();
    for(int i=0; i<_i; i++){
        ++it;
    }
    return *it;
}

qreal dist(std::vector<std::vector<qreal>> &mat, std::list<int> trace) {
    qreal res = 0;
    for(int i = 0; i < trace.size() - 1; i++){
        int row = get(trace, i);
        int colom = get(trace, i + 1);
        res += mat[row][colom];
    }
    return res;
}

QString pathToStrint(std::vector<int> path, std::vector<QString> name) {
    QString strPath = "";
    for(int i = 0; i < path.size(); ++i) {
        if (i + 1 == path.size()) {
            strPath += name[path[i]];
        } else {
            strPath += name[path[i]] + "->";
        }

    }
    return strPath;
}

QString pathToStrint(std::vector<int> path) {
    QString strPath = "";
    for(int i = 0; i < path.size(); ++i) {
        if (i + 1 == path.size()) {
            strPath += QString::number(path[i] + 1);
        } else {
            strPath += QString::number(path[i] + 1) + "->";
        }

    }
    return strPath;
}

int n = 0;
std::vector<int> greedy_algorithm(std::vector<std::vector<qreal>> &mat, std::vector<int> backtrace = {0}) {
    n++;
    if (backtrace.size() == mat.size()) {
        backtrace.push_back(backtrace.front());
        qDebug() << pathToStrint(backtrace) + " Дистанция " + QString::number(dist(mat, backtrace));
        return backtrace;
    }

    std::vector<int> next_point;
    for(int i = 0; i < mat.size(); i++) {
        if(std::find(backtrace.begin(), backtrace.end(), i) == backtrace.end()) {
            next_point.push_back(i);
        }
    }
    int last = backtrace.back();
    auto min = std::min_element(next_point.begin(),next_point.end(),[last, mat](auto first, auto second) {
        return mat[last][first] < mat[last][second];
    });
    backtrace.push_back(*min);
    return greedy_algorithm(mat, backtrace);
}

std::vector<int> brute_force(std::vector<std::vector<qreal>> &mat, std::vector<int> backtrace = {0}) {
    n++;
    if (backtrace.size() == mat.size()) {
        backtrace.push_back(backtrace.front());
        return backtrace;
    }

    std::vector<int> bast;
    for(int i = 0; i < mat.size(); i++) {
        if(std::find(backtrace.begin(), backtrace.end(), i) == backtrace.end()) {
            auto copy = backtrace;
            copy.push_back(i);
            auto res = brute_force(mat, copy);
            if(bast.empty()) {
                bast = res;
            } else if(dist(mat, bast) > dist(mat, res)) {
                bast = res;
            }
        }
    }
    return bast;
}

std::list<int> dynamic_programming(std::vector<std::vector<qreal>> &mat, int begin ,int start , std::list<int> backtrace, std::map<std::pair<int, std::list<int>> , std::list<int>> &history, bool on_history = true) {
    n++;

    std::list<int> bast;
    if ((history.find({start, backtrace}) != history.end()) && on_history) {
        bast = history[{start, backtrace}];
    } else {
        for(auto item: backtrace) {
            auto copy = backtrace;
            std::remove(copy.begin(), copy.end(), item);
            copy.pop_back();
            std::list<int> res;
            if (copy.size() != 1) {
                res = dynamic_programming(mat, begin, item, copy, history, on_history);
            } else {
                copy.push_front(item);
                copy.push_back(begin);
                res = copy;
            }

            res.push_front(start);
            if(bast.empty()) {
                bast = res;
            } else if(dist(mat, bast) > dist(mat, res)) {
                bast = res;
            }
        }
        if (on_history)
            history.insert({{start, backtrace}, bast});
    }

    return bast;
}

void FormInteractiveMap::drowLine(std::vector<QString> name, std::vector<int> path) {
    for (auto it: line_path) {
        delete it;
    }
    line_path.clear();
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::green);
    auto item = this->scene->getList();
    for(int i = 0; i < path.size() - 1; i++) {
        this->line_path.push_back(this->scene->addLine(item[name[path[i]]]->pos().x(),
                                                       item[name[path[i]]]->pos().y(),
                                                       item[name[path[i + 1]]]->pos().x(),
                                                       item[name[path[i + 1]]]->pos().y(), pen));
    }
}

void FormInteractiveMap::on_pushButton_clicked()
{
    this->ui->pushButton->setEnabled(false);
    this->ui->pushButton_2->setEnabled(true);

    auto mat = getMat();
    auto name = getNamePoint();

    if(mat.size() == 0) {
        this->ui->pushButton->setEnabled(true);
        this->ui->pushButton_2->setEnabled(false);
        qDebug() << "Нет точек";
        return;
    }

    qDebug() << "Точек " +  QString::number(mat.size());
    n = 0;
    switch (this->ui->comboBox->currentIndex()) {
        case 0: {
            qDebug() << "Полный перебор";
            auto start = std::chrono::high_resolution_clock::now();
            auto path = brute_force(mat);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            drowLine(name, path);
            this->ui->lineEdit->setText(pathToStrint(path, name));
            this->ui->lineEdit_2->setText(QString::number(dist(mat, path)));
            this->ui->lineEdit_3->setText(QString::number(duration.count()) + "us");
            break;
        }
        case 1: {
            qDebug() << "Жадный алгоритм";
            auto start = std::chrono::high_resolution_clock::now();
            auto path = greedy_algorithm(mat);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            drowLine(name, path);
            this->ui->lineEdit->setText(pathToStrint(path, name));
            this->ui->lineEdit_2->setText(QString::number(dist(mat, path)));
            this->ui->lineEdit_3->setText(QString::number(duration.count()) + "us");
            break;
        }
        case 2:{
            qDebug() << "Метод динамического программирования";
            int pStart = 0;
            std::list<int> point;
            std::map<std::pair<int, std::list<int>> , std::list<int>> history;
            for(int i = 1; i < mat.size(); ++i) point.push_back(i);

            auto start = std::chrono::high_resolution_clock::now();
            auto res = dynamic_programming(mat, pStart, pStart, point, history);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

            std::vector<int> path(res.begin(), res.end());
            this->ui->lineEdit->setText(pathToStrint(path, name));
            this->ui->lineEdit_2->setText(QString::number(dist(mat, path)));
            this->ui->lineEdit_3->setText(QString::number(duration.count()) + "us");
            drowLine(name, path);
            qDebug() << pathToStrint(path);

            break;
        }
        case 3: {
            //Ветвей и границ
            auto start = std::chrono::high_resolution_clock::now();

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            this->ui->lineEdit_3->setText(QString::number(duration.count()));
            break;
        }
        default:
            return;
    }
    this->ui->lineEdit_5->setText(QString::number(n));

    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(false);
}

void FormInteractiveMap::on_pushButton_2_clicked()
{
    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(false);
}

void FormInteractiveMap::on_pushButton_4_clicked()
{

    for(int i = 0; i < ui->tabWidget->count(); ++i)
        this->list_tap[this->ui->tabWidget->tabText(i)]->setModeItem(Move);
}


void FormInteractiveMap::on_pushButton_5_clicked()
{

    for(int i = 0; i < ui->tabWidget->count(); ++i)
        this->list_tap[this->ui->tabWidget->tabText(i)]->setModeItem(Scale);
}


void FormInteractiveMap::on_pushButton_6_clicked()
{

    for(int i = 0; i < ui->tabWidget->count(); ++i)
        this->list_tap[this->ui->tabWidget->tabText(i)]->setModeItem(Rotation);
}


void FormInteractiveMap::on_pushButton_7_clicked()
{

    for(int i = 0; i < ui->tabWidget->count(); ++i)
        this->list_tap[this->ui->tabWidget->tabText(i)]->setModeItem(Null);
}

QByteArray getDataInFile(QString file_name)
{
    QByteArray data;
    QFile file(file_name);

    file.open(QIODevice::ReadOnly);
    data = file.readAll();
    file.close();
    return data;
}

void FormInteractiveMap::on_pushButton_3_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Открыть карту", QString(),"EMAP (*.emap)");
    if (!file_name.isNull()) {
        QPixmap background;
        QByteArray data = getDataInFile(file_name);
        QByteArray bPixmap;
        QDataStream stream(&data, QIODevice::ReadOnly);
        QStringList list = file_name.split('/');

        for(int i = 0; i < ui->tabWidget->count(); ++i) {
            if (this->ui->tabWidget->tabText(i) == list[list.size() - 1]){
                QMessageBox::information(this, QObject::tr("Открытие"), QObject::tr("Файл уже открыт"));
                return;
            }
        }

        auto view = new QGraphicsView(this);
        auto scene = new CustomScene(true, list[list.size() - 1], this);

        stream >> bPixmap;

        background.loadFromData(bPixmap);

        view->setScene(scene);
        view->setAcceptDrops(true);
        scene->setBackground(background);
        setConnect(scene);

        int count;
        stream >> count;
        for (int i = 0; i < count; i++) {
            qreal x, y, scele, rot;
            QByteArray name, nameObj;
            int type;

            stream >> x >> y >> type >> scele >> rot >> name >> nameObj;
            auto item = scene->addItemInScene(type, name, nameObj, QPointF(x,y));
            item->setScale(scele);
            item->setRotation(rot);
        }

        stream >> count;
        for (int i = 0; i < count; ++i) {
            QRectF rect;
            QPointF pos;
            QString name;
            stream >> pos >> rect >> name;
            scene->addRectInScene(name, pos, rect);
        }

        stream >> count;
        for (int i = 0; i < count; ++i) {
            QPointF pos;
            QString nameObj, nameItem;
            qreal scale, rotation;

            stream >> pos >> scale >> rotation >> nameItem >> nameObj;
        }

        stream >> count;
        for (int i = 0; i < count; ++i) {
            QPointF pos;
            QString nameObj, nameItem;
            int w, h;

            stream >> pos >> w >> h >> nameItem >> nameObj;
        }


        this->ui->tabWidget->addTab(view, list[list.size() - 1]);
        list_tap.insert(list[list.size() - 1], scene);

        this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count() - 1);
    }
}

void FormInteractiveMap::setConnect(CustomScene *scene)
{
    connect(scene, &CustomScene::addNewItem, [=](CustomGraphicsPixmapItem *item){
        this->ui->tableWidget->insertRow(this->ui->tableWidget->rowCount());
        auto itemWidget = new ListElementForScene(0, item->getName() + " (Точка)", item);
        itemWidget->setNameScene(scene->getNameScene());

        itemWidget->setContextMenuPolicy(Qt::CustomContextMenu);
                connect(itemWidget, &ListElementForScene::customContextMenuRequested, [=](){
                    QMenu contextMenu(tr("Меню"), this);
                    QAction action1("Удалить", this);

                    connect( &action1, &QAction::triggered, [=](){
                        scene->deleteItemInList(item->getName());
                        delete itemWidget->getItem();
                        this->ui->tableWidget->removeRow(this->ui->tableWidget->currentRow());
                    });

                    contextMenu.addAction(&action1);

                    contextMenu.exec(mapToGlobal(this->mapFromGlobal(this->cursor().pos())));
                });

                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemWidget);
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 0, itemWidget);

    });
}

void FormInteractiveMap::savePlan(int index)
{
    QString targetFolder = QFileDialog::getSaveFileName(this, tr("Сохранить карту"), this->ui->tabWidget->tabText(index) ,"EMAP (*.emap)");

    if (!targetFolder.isNull()) {
        if (targetFolder.indexOf(".emap") == -1) {
            targetFolder += ".emap";
        }
        auto scene = this->list_tap[this->ui->tabWidget->tabText(index)];
        QByteArray saveData;
        QDataStream streamVMan(&saveData, QIODevice::WriteOnly);
        QByteArray bPixmap;
        QBuffer buffer(&bPixmap);

        buffer.open(QIODevice::WriteOnly);
        scene->getBackground().save(&buffer, "PNG");

        streamVMan << bPixmap;
        streamVMan << scene->getList().size();

        for (auto item : scene->getList()) {
            streamVMan << item->pos().x();
            streamVMan << item->pos().y();
            streamVMan << item->getType();
            streamVMan << item->scale();
            streamVMan << item->rotation();
            streamVMan << item->getName().toUtf8();
            streamVMan << item->getObjName().toUtf8();
        }

        QFile file(targetFolder);
        file.open(QIODevice::WriteOnly);
        file.write(saveData);
        file.close();
    }
}

void FormInteractiveMap::on_pushButton_8_clicked()
{
    int index = this->ui->tabWidget->currentIndex();
    if ( index < 0) {
        return;
    }
    savePlan(index);
}

void FormInteractiveMap::on_tabWidget_currentChanged(int index)
{
    if(index < 0)
        return;
    showItemFromList(index);
}
#include "startsettingenter.h"

void FormInteractiveMap::on_pushButton_9_clicked()
{

}

