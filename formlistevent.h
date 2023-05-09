#ifndef FORMLISTEVENT_H
#define FORMLISTEVENT_H

#include <QWidget>
#include "listelement.h"
#include "customelement.h"
#include "dialogviewer.h"

namespace Ui {
class FormLIstEvent;
}

class FormLIstEvent : public QWidget
{
    Q_OBJECT

public:
    explicit FormLIstEvent(int maxCount, QWidget *parent = nullptr);
    void addElement(ListElement *element, CustomLable *lablePhot, bool connected = true, bool up = true);
    void clearEvent();
    void showDetect();
    void hideDetect();
    void deleteDetectEvent();
    void deleteRecoEvent();
    virtual void closeEvent(QCloseEvent *event);
    ~FormLIstEvent();

private slots:
    void showViewer(cv::Mat frame);
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::FormLIstEvent *ui;
    DialogViewer *viewer;
    int count_detect;
    int count_reco;
    int maxCount;
};

#endif // FORMLISTEVENT_H
