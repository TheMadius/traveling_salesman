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
#include <vector>
#include "addnewelementinscene.h"
#include "settingsperimetr.h"
#include <utility>
//
//

std::vector<int> convert_pair(std::vector<std::pair<int, int>> vect_pair) {

    std::vector<int> res;
    if (vect_pair.size() == 0)
        return res;
    res.push_back(vect_pair.back().first);
    res.push_back(vect_pair.back().second);
    vect_pair.pop_back();

    for(int i = 0; i < vect_pair.size(); i++ ) {
        for(int i = 0; i < vect_pair.size(); i++ ) {
            if ( res.back() == vect_pair[i].first ) {
                res.push_back(vect_pair[i].second);
                break;
            }
        }
    }
    return res;
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

QImage cvMatToQImage(const cv::Mat &frame ) {
    return QImage( (const unsigned char*)(frame.data), frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888).rgbSwapped();
}

FormInteractiveMap::FormInteractiveMap(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::FormInteractiveMap)
{
    qRegisterMetaType<std::vector<std::pair<int, int>>>();
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

    connect(this, &FormInteractiveMap::end, this, &FormInteractiveMap::endSlot);

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

void FormInteractiveMap::endSlot(std::vector<std::pair<int, int>> path_pair, double time){
        auto mat = getMat();
        auto name = getNamePoint();
        qDebug() << path_pair.size();
        for(auto p: path_pair) {
            qDebug() << QString::number(p.first) + "->" + QString::number(p.second);
        }
        auto path = convert_pair(path_pair);
        auto stop = std::chrono::high_resolution_clock::now();

        this->ui->lineEdit->setText(pathToStrint(path));
        this->ui->lineEdit_2->setText(QString::number(dist(mat, path)));
        this->ui->lineEdit_3->setText(QString::number(time / 1000.0) + "ms");
        drowLine(name, path);
        qDebug() << pathToStrint(path);
        this->ui->pushButton->setEnabled(true);
        this->ui->pushButton_2->setEnabled(false);
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
            if (it2 == it1)
                line.push_back(-1);
            else
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

std::atomic<bool> run = true;
std::vector<std::pair<int, int>> branches_and_boundaries(std::vector<std::vector<qreal>> &mat) {
    std::vector<std::tuple<std::vector<std::vector<qreal>>, std::vector<std::pair<int, int>> ,qreal>> history = {};
    std::vector<std::pair<int, int>> res;
    qreal pow_min = 0;
    bool start_el = true;
    bool rash = true;
    auto copy_main = mat;

    qreal pow_main = 0;

    n++;
    int sec = 1;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < copy_main.size(); i++) {
        qreal min_row = -1;
        for(int j = 0; j < copy_main.size(); j++) {
            if (copy_main[i][j] >= 0)
                if(min_row == -1)
                    min_row = copy_main[i][j];
                else
                    min_row = (min_row > copy_main[i][j])?copy_main[i][j]:min_row;
        }
        if (min_row != -1) {
            pow_main += min_row;
            for(int k = 0; k < copy_main.size(); k++) {
                copy_main[i][k] -= min_row;
            }
        }
    }

    for (int i = 0; i < copy_main.size(); i++) {
        qreal min_colom = -1;
        for(int j = 0; j < copy_main.size(); j++) {
            if (copy_main[j][i] >= 0)
                if(min_colom == -1)
                    min_colom = copy_main[j][i];
                else
                    min_colom = (min_colom > copy_main[j][i])?copy_main[j][i]:min_colom;
        }
        if (min_colom != -1) {
            pow_main += min_colom;
            for(int k = 0; k < copy_main.size(); k++) {
                copy_main[k][i] -= min_colom;
            }
        }
    }

    while (run) {
        n++;
        qreal pow;
        std::vector<std::vector<qreal>> copy_mat;
        std::vector<std::pair<int, int>> branches = {};

        if (history.size() == 0) {
            if (start_el) {
                copy_mat = copy_main;
                pow = pow_main;
                start_el = false;
            } else {
                qDebug() << res.size();
                break;
            }
        } else {
            int min_intex = -1;
            int s;
            if (rash) {
                s = history.size() - 2;
            } else {
                s = 0;
                rash = true;
            }

            for(; s < history.size(); s++) {
                int H = std::get<2>(history[s]);
                if(min_intex < 0) {
                    min_intex = s;
                } else {
                    if(std::get<2>(history[min_intex]) > std::get<2>(history[s]))
                        min_intex = s;
                }
            }
            copy_mat = std::get<0>(history[min_intex]);
            branches = std::get<1>(history[min_intex]);
            pow = std::get<2>(history[min_intex]);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

            auto time = duration.count();
            if (time / 5 == sec) {
                qDebug() << pow_min;
                qDebug() << time;
                sec++;
            }

            if (branches.size() == copy_mat.size() - 1) {
                for(int i = 0; i < copy_mat.size(); i++)
                    for(int j = 0; j < copy_mat.size(); j++)
                        if (copy_mat[i][j] >= 0) {
                            branches.push_back({i, j});
                            auto tetet = convert_pair(branches);

                            if (tetet.size() - 1 != copy_mat.size()) {
                                rash = false;
                                goto end_for;
                            }

                            if (res.empty()) {
                                res = branches;
                                pow_min = pow;
                            } else {
                                if (pow_min > pow) {
                                    res = branches;
                                    pow_min = pow;
                                }
                            }
                            rash = false;
                            goto end_for;
                        }
            end_for:
                history.erase(std::next(history.begin(), min_intex));
                continue;
            } else {
                history.erase(std::next(history.begin(), min_intex));
            }

        }

        int index_row = -1;
        int index_col = -1;
        qreal max_fine = -1;
        bool not_inf = true;

        for(int i = 0; i < copy_mat.size() && not_inf; i++) {
            for(int j = 0; j < copy_mat.size() && not_inf; j++) {
                if (copy_mat[i][j] == 0) {
                    int cout_row_null = 0;
                    int cout_col_null = 0;
                    qreal min_row = -1;
                    qreal min_col = -1;
                    for(int k = 0; k < copy_mat.size(); k++) {
                        if (copy_mat[i][k] >= 0 && k != j) {
                            min_row = (min_row < 0)?copy_mat[i][k]:(min_row > copy_mat[i][k])?copy_mat[i][k]:min_row;
                        } else {
                            cout_row_null++;
                        }

                        if (copy_mat[k][j] >= 0 && k != i) {
                            min_col = (min_col < 0)?copy_mat[k][j]:(min_col > copy_mat[k][j])?copy_mat[k][j]:min_col;
                        } else {
                            cout_col_null++;
                        }
                    }

                    if (cout_col_null == copy_mat.size() || cout_row_null == copy_mat.size()) {
                        index_row = j;
                        index_col = i;
                        not_inf = false;
                    }

                    if (max_fine < 0) {
                        max_fine = min_row + min_col;
                        index_row = j;
                        index_col = i;
                    } else {
                        auto new_fine = min_row + min_col;
                        if (max_fine < new_fine) {
                            max_fine = new_fine;
                            index_row = j;
                            index_col = i;
                        }
                    }
                }
            }
        }

        //out point with max file
        copy_mat[index_col][index_row] = -1;

        for (int i = 0; i < copy_mat.size(); i++) {
            qreal min_row = -1;
            for(int j = 0; j < copy_mat.size(); j++) {
                if (copy_mat[i][j] >= 0)
                    if(min_row == -1)
                        min_row = copy_mat[i][j];
                    else
                        min_row = (min_row > copy_mat[i][j])?copy_mat[i][j]:min_row;
            }
            if (min_row != -1) {
                for(int k = 0; k < copy_mat.size(); k++) {
                    copy_mat[i][k] -= min_row;
                }
            }
        }

        for (int i = 0; i < copy_mat.size(); i++) {
            qreal min_colom = -1;
            for(int j = 0; j < copy_mat.size(); j++) {
                if (copy_mat[j][i] >= 0)
                    if(min_colom == -1)
                        min_colom = copy_mat[j][i];
                    else
                        min_colom = (min_colom > copy_mat[j][i])?copy_mat[j][i]:min_colom;
            }
            if (min_colom != -1) {
                for(int k = 0; k < copy_mat.size(); k++) {
                    copy_mat[k][i] -= min_colom;
                }
            }
        }

        if (not_inf) {
            history.push_back({copy_mat, branches, pow + max_fine});
        }

        //in point with max file
        branches.push_back({index_col,index_row});
        for (int i = 0; i < copy_mat.size(); i++) {
            copy_mat[i][index_row] = -1;
            copy_mat[index_col][i] = -1;
        }
        copy_mat[index_row][index_col] = -1;
        copy_mat[index_col][index_row] = -1;

        for (int i = 0; i < copy_mat.size(); i++) {
            qreal min_row = -1;
            for(int j = 0; j < copy_mat.size(); j++) {
                if (copy_mat[i][j] >= 0)
                    if(min_row == -1)
                        min_row = copy_mat[i][j];
                    else
                        min_row = (min_row > copy_mat[i][j])?copy_mat[i][j]:min_row;
            }
            if (min_row != -1) {
                pow += min_row;
                for(int k = 0; k < copy_mat.size(); k++) {
                    copy_mat[i][k] -= min_row;
                }
            }
        }

        for (int i = 0; i < copy_mat.size(); i++) {
            qreal min_colom = -1;
            for(int j = 0; j < copy_mat.size(); j++) {
                if (copy_mat[j][i] >= 0)
                    if(min_colom == -1)
                        min_colom = copy_mat[j][i];
                    else
                        min_colom = (min_colom > copy_mat[j][i])?copy_mat[j][i]:min_colom;
            }
            if (min_colom != -1) {
                pow += min_colom;
                for(int k = 0; k < copy_mat.size(); k++) {
                    copy_mat[k][i] -= min_colom;
                }
            }
        }

        history.push_back({copy_mat, branches, pow});
    }
    return res;
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

#include <thread>

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
            this->ui->lineEdit_3->setText(QString::number(duration.count() / 1000.0) + "ms");
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
            this->ui->lineEdit_3->setText(QString::number(duration.count() / 1000.0) + "ms");
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
            this->ui->lineEdit_3->setText(QString::number(duration.count() / 1000.0) + "ms");
            drowLine(name, path);
            qDebug() << pathToStrint(path);

            break;
        }
        case 3: {
            //Ветвей и границ
            run = true;
            std::thread t([&](){
                    auto mat_thread = getMat();
                    auto start_t = std::chrono::high_resolution_clock::now();
                    auto path_pair = branches_and_boundaries(mat_thread);
                    auto stop_t = std::chrono::high_resolution_clock::now();
                    auto duration_t = std::chrono::duration_cast<std::chrono::microseconds>(stop_t - start_t);
                    emit end(path_pair, duration_t.count());
                    return;
            });
            t.detach();
            return;
        }
        default:
            break;
    }

        this->ui->lineEdit_5->setText(QString::number(n));

    this->ui->pushButton->setEnabled(true);
    this->ui->pushButton_2->setEnabled(false);
}

void FormInteractiveMap::on_pushButton_2_clicked()
{
    run = false;
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

