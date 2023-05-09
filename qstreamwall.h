#ifndef QSTREAMWALL_H
#define QSTREAMWALL_H

#include <QLayout>
#include <QLayoutItem>
#include <QDebug>

class QStreamWall : public QLayout
{
    Q_OBJECT
public:
    QStreamWall(QWidget *perent = nullptr);
    ~QStreamWall();

    virtual QSize sizeHint() const;
    virtual void setGeometry(const QRect &rect);
    virtual void addItem(QLayoutItem *item);
    virtual QLayoutItem *itemAt(int index) const;
    virtual QLayoutItem *takeAt(int index);
    virtual int count() const;
    virtual QSize minimumSize() const;
    virtual void removeItem(QLayoutItem *item);

private:
    QList<QLayoutItem *> _item;
    int countCell() const;
    int countRow() const;
};

#endif // QSTREAMWALL_H
