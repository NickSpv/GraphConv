#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class GraphNode : public QGraphicsItem
{
public:
    explicit  GraphNode(QGraphicsItem* parent = nullptr) : QGraphicsItem{parent} {}

    void setNum(const int& num);
    int getNum() const;
    void setDefaultNum(const int& num);
    int getDefaultNum() const;
    void setColor(QColor color);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    int num = 0;
    int default_num = 0;
    QColor color = Qt::green;
};

#endif // GRAPHNODE_H
