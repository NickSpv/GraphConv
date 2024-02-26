#include "graphnode.h"

void GraphNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) {
    painter->setBrush(QBrush(Qt::green));
    painter->drawEllipse(-20, -20, 40, 40);
    painter->drawText(QRectF(-10, -10, 20, 20), Qt::AlignCenter, QString::number(this->num));
}

QRectF GraphNode::boundingRect() const {
    return QRectF(-20, -20, 40, 40);
}

void GraphNode::setNum(const int& num) {
    this->num = num;
}

int GraphNode::getNum() const {
    return this->num;
}
