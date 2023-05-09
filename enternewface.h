#ifndef ENTERNEWFACE_H
#define ENTERNEWFACE_H

#include <QDialog>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/mat.hpp>
#include <vector>
#include <algorithm>


namespace Ui {
class EnterNewFace;
}

class EnterNewFace : public QDialog
{
    Q_OBJECT

public:
    explicit EnterNewFace(QWidget *parent = nullptr);
    QString id;
    QString name;
    QString surname;
    QString lastname;
    QString url;
    ~EnterNewFace();

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_checkBox_stateChanged(int arg1);

private:
    QGraphicsPixmapItem *foto;
    Ui::EnterNewFace *ui;
    QString path;

};

#endif // ENTERNEWFACE_H
