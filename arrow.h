#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QPolygonF>
#include <QObject>
#include <QPen>
#include <QPainter>

class Arrow : public QGraphicsLineItem
{
public:
    Arrow(QGraphicsItem* parent = nullptr);

    void setStartItem(const QGraphicsItem* startItem);
    void setEndItem(const QGraphicsItem* endItem);
    void setEndTempPos(const QPointF endTempPos);

    const QGraphicsItem* getStartItem() const;
    const QGraphicsItem* getEndItem() const;
    void setNum(const int& num);
    int getNum();

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    const QGraphicsItem* startItem;
    const QGraphicsItem* endItem;
    QPointF endTempPos;
    QPolygonF arrowHead;
    int num = -1;
};

#endif // ARROW_H
