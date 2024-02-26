#ifndef MYQGRAPHICSSCENE_H
#define MYQGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QVector>
#include <QtAlgorithms>

#include "graphnode.h"
#include "arrow.h"


class MyQGraphicsScene : public QGraphicsScene
{
public:
    explicit MyQGraphicsScene(QObject *parent = nullptr): QGraphicsScene{parent} {}
    explicit MyQGraphicsScene(const QRectF& sceneRect, QObject *parent = nullptr): QGraphicsScene{sceneRect, parent} {}

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    QVector<QVector<int>> get_incident();
    QVector<QVector<int>> get_ligament();

    bool arrow_exist(const QGraphicsItem* from, const QGraphicsItem* to);
    void numerate_arrows();

private:
    bool right_mouse_pressed = false;
    QVector<GraphNode*> graph_nodes;
    QVector<Arrow*> arrows;
    Arrow* current_arrow = nullptr;
    int current_node_index = 1;
};

#endif // MYQGRAPHICSSCENE_H
