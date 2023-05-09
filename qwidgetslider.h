#ifndef QWIDGETSLIDER_H
#define QWIDGETSLIDER_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QDebug>

class QWidgetSlider : public QWidget
{
    Q_OBJECT
public:
    explicit QWidgetSlider(int scale = 1, QWidget *parent = nullptr);
    void setValue(double value);
    void setMaximum(double maxValue);
    void setMinimum(double minValue);
    QLabel *getLable(){ return this->value ;}
    QSlider *getSlider(){ return this->slide ;}

    ~QWidgetSlider();
public slots:
    void valueChanged(int new_value);
signals:

private:
    int scale;
    QLabel *value;
    QSlider *slide;
};

#endif // QWIDGETSLIDER_H
