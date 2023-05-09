#ifndef DIALOGVSTREAMVIEW_H
#define DIALOGVSTREAMVIEW_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

namespace Ui {
class DialogVStreamView;
}


class DialogVStreamView : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVStreamView(QWidget *parent = nullptr);
    virtual void keyPressEvent(QKeyEvent *event);
    void setNameCam(QString name);
    ~DialogVStreamView();
    void setFrame();
private:
    QString name_cam;
    Ui::DialogVStreamView *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *photo;
    int num_frame;
};

#endif // DIALOGVSTREAMVIEW_H
