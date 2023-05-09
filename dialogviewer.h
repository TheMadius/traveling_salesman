#ifndef DIALOGVIEWER_H
#define DIALOGVIEWER_H

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMetaObject>
#include <QDebug>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/mat.hpp>

#include "customscene.h"

namespace Ui {
class DialogViewer;
}

class DialogViewer : public QWidget
{
    Q_OBJECT

public:
    explicit DialogViewer(QWidget *parent = nullptr);
    void setFrame(cv::Mat frame);
    cv::Mat getFrame(){return frame;}
    QImage cvMatToQImage(const cv::Mat &frame);
    ~DialogViewer();

public slots:
    void saveFrame();
    void setNormal();
    void cutFrame(QRectF zone);
    void cutAndSaveFrame(QRectF zone);
    void zoomPhoto(int delta, QPointF point);
    void backPhoto();

private:
    Ui::DialogViewer *ui;
    QGraphicsPixmapItem *photo;
    CustomSceneView *scene;
    CustomView *view;
    QList<QPixmap> history;
    cv::Mat frame;
};

#endif // DIALOGVIEWER_H
