#include "qwidgetslider.h"

QWidgetSlider::QWidgetSlider(int scale ,QWidget *parent)
    : QWidget{parent}
{
    this->setLayout(new QHBoxLayout());
    this->scale = scale;
    this->value = new QLabel();
    this->slide = new QSlider(Qt::Orientation::Horizontal);

    this->layout()->addWidget(slide);
    this->layout()->addWidget(value);
    connect(slide, &QSlider::valueChanged, this, &QWidgetSlider::valueChanged);
}

void QWidgetSlider::setValue(double value)
{
    this->value->setText(QString::number(value));
    this->slide->setValue(value * scale);
}

void QWidgetSlider::setMaximum(double maxValue)
{
    this->slide->setMaximum(maxValue * scale);
}

void QWidgetSlider::setMinimum(double minValue)
{
    this->slide->setMinimum(minValue * scale);
}

void QWidgetSlider::valueChanged(int new_value)
{
    this->value->setText(QString::number(new_value/((double)scale)));
}

QWidgetSlider::~QWidgetSlider()
{
    delete value;
    delete slide;
}
