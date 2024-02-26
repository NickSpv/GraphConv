#include "arrow.h"

Arrow::Arrow(QGraphicsItem* parent): QGraphicsLineItem{parent} {
    this->endTempPos;
    this->startItem = nullptr;
    this->endItem = nullptr;
}

void Arrow::setStartItem(const QGraphicsItem* startItem) {
    this->startItem = startItem;
}

void Arrow::setEndItem(const QGraphicsItem* endItem) {
    this->endItem = endItem;
}

const QGraphicsItem* Arrow::getStartItem() const {
    return this->startItem;
}

const QGraphicsItem* Arrow::getEndItem() const {
    return this->endItem;
}

void Arrow::setEndTempPos(const QPointF endTempPos) {
    this->endTempPos = endTempPos;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setBrush(Qt::black);
    qreal size = 10;
    QPointF arrow_pos = (this->endItem != nullptr) ? this->endItem->pos() : this->endTempPos;
    double angle = std::atan2(this->startItem->pos().ry() - arrow_pos.ry(),
                              arrow_pos.rx() - this->startItem->pos().rx());
    QPointF start_pos = this->startItem->pos() +
                        QPointF(sin(angle + M_PI / 2) * 20,
                                cos(angle + M_PI / 2) * 20) +
                        QPointF(sin(angle + M_PI) * 5,
                                cos(angle + M_PI) * 5);
    QPointF end_pos = arrow_pos -
                      QPointF(sin(angle + M_PI / 2) * 20,
                              cos(angle + M_PI / 2) * 20);
    if (this->endItem == nullptr) end_pos = arrow_pos;
    QLineF line(start_pos, end_pos);
    painter->drawLine(line);

    painter->drawLine(end_pos, end_pos - QPointF(sin(angle + M_PI - M_PI / 3) * size,
                                                     cos(angle + M_PI - M_PI / 3) * size));
    painter->drawLine(end_pos, end_pos - QPointF(sin(angle + M_PI / 3) * size,
                                                     cos(angle + M_PI / 3) * size));
    if (this->endItem != nullptr) {
        painter->setPen(Qt::red);
        painter->drawText(QRectF(start_pos, end_pos - (end_pos - start_pos) / 3),
                          Qt::AlignCenter, QString::number(this->num));
    }
}

QRectF Arrow::boundingRect() const {
    qreal extra = (this->pen().width() + 20) / 2;
    return QRectF(line().p1(),
               QSizeF(
                   line().p2().x() - line().p1().x(),
                   line().p2().y() - line().p1().y()
               )
           ).normalized().adjusted(-extra,-extra,extra,extra);
}

void Arrow::setNum(const int &num) {
    this->num = num;
}

int Arrow::getNum() {
    return this->num;
}
