#include "qstreamwall.h"
#include <QtMath>

QStreamWall::QStreamWall(QWidget *perent)
    : QLayout(perent)
{

}

QStreamWall::~QStreamWall()
{
    for(int i = 0; i < this->_item.size(); ++i) {
        delete _item.at(i);
    }
}

int QStreamWall::countCell() const
{
    int count = qCeil(qSqrt((qreal)this->count()));
    return count;
}

int QStreamWall::countRow() const
{
    int cell = this->countCell();
    if(cell == 0) {
        return 0;
    }
    if ( count() % cell == 0) {
        return count() / cell;
    } else {
        return (count() / cell) + 1;
    }
}

QSize QStreamWall::sizeHint() const
{
    int width = 100;
    int height = 100;

    if ( count() < 1 ) {
        return QSize(width, height);
    }

    int count_cell = countCell();
    int count_row = countRow();

    width = this->_item[0]->sizeHint().width() * count_cell;
    height = this->_item[0]->sizeHint().height() * count_row;

    return QSize(width, height);
}

void QStreamWall::setGeometry(const QRect &rect)
{
    //QLayout::setGeometry(rect);
    int count_row = countRow();
    int count_cell = countCell();

    for (int i = 0; i < count(); ++i) {

        QRect geom( (i % count_cell)* (rect.width() / count_cell), (i / count_cell) * (rect.height() / count_row),
                   rect.width() / count_cell , (rect.height() / count_row) );
        itemAt(i)->setGeometry(geom);
    }
}


QSize QStreamWall::minimumSize() const
{
    return sizeHint();
}


void QStreamWall::addItem(QLayoutItem *item)
{
    _item.append(item);
}

void QStreamWall::removeItem(QLayoutItem *item)
{
    int index = _item.indexOf(item);
    if (index >= 0) {
        delete _item.at(index);
        _item.removeAt(index);
    }
}

QLayoutItem *QStreamWall::itemAt(int index) const
{
    if (index < 0 || index >= count()) {
        return nullptr;
    }
    return _item.at(index);
}
QLayoutItem *QStreamWall::takeAt(int index)
{
    if (index < 0 || index >= count()) {
        return nullptr;
    }
    return _item.takeAt(index);
}

int QStreamWall::count() const
{
    return _item.size();
}
