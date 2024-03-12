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
    explicit MyQGraphicsScene(QObject *parent = nullptr): QGraphicsScene{parent} {
        level_color.insert(0, QColor(Qt::red));
        level_color.insert(1, QColor(Qt::green));
        level_color.insert(2, QColor(Qt::magenta));
        level_color.insert(3, QColor(Qt::yellow));
        level_color.insert(4, QColor(Qt::white));
        level_color.insert(5, QColor(Qt::blue));
        level_color.insert(6, QColor(Qt::cyan));
        level_color.insert(7, QColor(Qt::gray));
        level_color.insert(8, QColor(Qt::darkRed));
        level_color.insert(9, QColor(Qt::darkGreen));
        level_color.insert(10, QColor(Qt::darkMagenta));
        level_color.insert(11, QColor(Qt::darkYellow));
        level_color.insert(12, QColor(Qt::lightGray));
        level_color.insert(13, QColor(Qt::darkBlue));
        level_color.insert(14, QColor(Qt::darkCyan));
        level_color.insert(15, QColor(Qt::darkGray));
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    QVector<QVector<int>> get_incident();
    QVector<QVector<int>> get_ligament();
    QVector<QVector<int>> get_left_incident();
    QVector<QVector<int>> get_right_incident();


    int get_count_input_arrow(const GraphNode*);
    int get_count_output_arrow(const GraphNode*);
    bool arrow_exist(const QGraphicsItem* from, const QGraphicsItem* to);
    void numerate_arrows();
    void clear();
    QMap<int, int> hierarchical_level_selection();
    void set_default();

private:
    bool right_mouse_pressed = false;
    QVector<GraphNode*> graph_nodes;
    QVector<Arrow*> arrows;
    Arrow* current_arrow = nullptr;
    int current_node_index = 1;
    QMap<int, QColor> level_color;
};

#endif // MYQGRAPHICSSCENE_H
