#include "dialogviewer.h"
#include "ui_dialogviewer.h"
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QScrollBar>
#include <QFileDialog>
#include <QWhatsThis>

DialogViewer::DialogViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogViewer)
{
    ui->setupUi(this);
    ui->verticalLayout_2->layout()->setContentsMargins(0,0,0,0);

    this->ui->widget->setLayout(new QVBoxLayout());
    ui->widget->layout()->setContentsMargins(0,0,0,0);

    this->scene = new CustomSceneView();

    connect(scene, &CustomSceneView::cut, this, &DialogViewer::cutFrame);
    connect(scene, &CustomSceneView::normal, this, &DialogViewer::setNormal);
    connect(scene, &CustomSceneView::save, this, &DialogViewer::saveFrame);
    connect(scene, &CustomSceneView::saveCut, this, &DialogViewer::cutAndSaveFrame);
    connect(scene, &CustomSceneView::zoom, this, &DialogViewer::zoomPhoto);
    connect(scene, &CustomSceneView::back, this, &DialogViewer::backPhoto);

    view = new CustomView();

    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setScene(scene);

    this->layout()->addWidget(view);
    photo = new QGraphicsPixmapItem();

    scene->addItem(photo);
}

void DialogViewer::zoomPhoto(int delta, QPointF point)
{    
    QPointF posZoom;
    qreal step = (delta / (double)180) / 10;
    qreal scale = this->photo->scale() + step;

    if (scale <= 1) {
        scale = 1;
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }

    posZoom.setX(point.x() * scale);
    posZoom.setY(point.y() * scale);

    this->photo->setScale(scale);
    this->scene->setSceneRect(0, 0, photo->pixmap().width() * scale, photo->pixmap().height() * scale );
    view->centerOn(point);
}

void DialogViewer::saveFrame()
{
    QString targetFolder = QFileDialog::getSaveFileName(this, tr("Сохранить фото"), ".jpg" ,"JPG (*.jpg)");

    if (!targetFolder.isNull()) {
        if (targetFolder.indexOf(".jpg") == -1) {
            targetFolder += ".jpg";
        }
        photo->pixmap().save(targetFolder, "jpg");
    }
}

void DialogViewer::setNormal()
{
    QPixmap pixmap = QPixmap::fromImage(cvMatToQImage(frame));
    photo->setPixmap(pixmap);

    this->history.clear();
    this->photo->setScale(1);
    this->scene->setSceneRect(0, 0, photo->pixmap().width(), photo->pixmap().height());
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void DialogViewer::backPhoto()
{
    if (history.size() != 0) {
        QPixmap pixmap = history.back();
        history.pop_back();

        this->photo->setPixmap(pixmap);
        this->photo->setScale(1);
        this->scene->setSceneRect(0, 0, photo->pixmap().width(), photo->pixmap().height());
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
}

void DialogViewer::cutFrame(QRectF zone)
{
    history.append(this->photo->pixmap());

    qreal scale = this->photo->scale();
    auto newPhoto = photo->pixmap().copy(QRect(zone.x() / scale, zone.y() / scale, zone.width() / scale, zone.height() / scale));
    newPhoto = newPhoto.scaled(photo->pixmap().width(), photo->pixmap().height());
    this->photo->setPixmap(newPhoto);
    this->photo->setScale(1);
    this->scene->setSceneRect(0, 0, photo->pixmap().width(), photo->pixmap().height());
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void DialogViewer::cutAndSaveFrame(QRectF zone)
{
    qreal scale = this->photo->scale();
    auto newPhoto = photo->pixmap().copy(zone.toRect());
    newPhoto = photo->pixmap().copy(QRect(zone.x() / scale, zone.y() / scale, zone.width() / scale, zone.height() / scale));
    QString targetFolder = QFileDialog::getSaveFileName(this, tr("Сохранить фото"), ".jpg" ,"JPG (*.jpg)");

    if (!targetFolder.isNull()) {
        if (targetFolder.indexOf(".jpg") == -1) {
            targetFolder += ".jpg";
        }
        newPhoto.save(targetFolder, "jpg");
    }
}

DialogViewer::~DialogViewer()
{
    delete ui;
}

QImage DialogViewer::cvMatToQImage(const cv::Mat &frame ) {
    return QImage( (const unsigned char*)(frame.data), frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_RGB888).rgbSwapped();
}

void DialogViewer::setFrame(cv::Mat frame)
{
    this->frame = frame;
    photo->setPixmap(QPixmap::fromImage(cvMatToQImage(frame)));
    this->setGeometry(0,0,frame.cols, frame.rows);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    this->history.clear();
}

