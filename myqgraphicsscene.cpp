#include "myqgraphicsscene.h"

#include <QDebug>

void MyQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem* item = this->itemAt(event->scenePos(), QTransform());
    if (event->button() == Qt::MiddleButton) {
        GraphNode* new_node = new GraphNode();
        new_node->setFlags(QGraphicsItem::ItemIsMovable);
        new_node->setPos(event->scenePos());
        new_node->setNum(this->current_node_index);
        this->current_node_index++;
        this->graph_nodes.append(new_node);
        this->addItem(new_node);
    } else if (event->button() == Qt::RightButton and item != nullptr) {
        qInfo() << "start_line";
        this->right_mouse_pressed = true;
        current_arrow = new Arrow();
        current_arrow->setStartItem(item);
        current_arrow->setEndTempPos(event->scenePos());
        this->addItem(current_arrow);
    }
    if (item != nullptr)
        item->setZValue(1);
    this->update();
    QGraphicsScene::mousePressEvent(event);
}

void MyQGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (event->button() == Qt::RightButton and item) {
        this->right_mouse_pressed = false;
        if (not this->arrow_exist(current_arrow->getStartItem(), item)) {
            current_arrow->setEndItem(item);
            this->arrows.append(current_arrow);
            qInfo() << "end_line";
            this->numerate_arrows();
        } else delete current_arrow;
        item->setZValue(1);
    } else if (event->button() == Qt::RightButton) {
        delete current_arrow;
    }
    this->update();
    QGraphicsScene::mouseReleaseEvent(event);
}

void MyQGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (this->right_mouse_pressed) {
        current_arrow->setEndTempPos(event->scenePos());
    }
    this->update();
    QGraphicsScene::mouseMoveEvent(event);
}

bool MyQGraphicsScene::arrow_exist(const QGraphicsItem *from, const QGraphicsItem *to) {
    for (auto i : arrows) {
        if (i->getStartItem() == from and i->getEndItem() == to) return true;
    }
    return false;
}

QVector<QVector<int>> MyQGraphicsScene::get_incident() {
    QVector<QVector<int>> incident(this->graph_nodes.size(),
                                   QVector<int>(this->arrows.size(), 0));
    this->numerate_arrows();
    for (int i = 0; i < this->arrows.size(); i++) {
        incident[static_cast<const GraphNode*>(this->arrows[i]->getStartItem())->getNum() - 1][i] = 1;
        incident[static_cast<const GraphNode*>(this->arrows[i]->getEndItem())->getNum() - 1][i] = -1;
    }
    return incident;
}

bool arr_com(const Arrow* a, const Arrow* b) {
    if (static_cast<const GraphNode*>(a->getStartItem())->getNum() > static_cast<const GraphNode*>(b->getStartItem())->getNum() or
        (static_cast<const GraphNode*>(a->getStartItem())->getNum() == static_cast<const GraphNode*>(b->getStartItem())->getNum() and
        static_cast<const GraphNode*>(a->getEndItem())->getNum() > static_cast<const GraphNode*>(b->getEndItem())->getNum())) {
        return false;
    } else {
        return true;
    }
}

void MyQGraphicsScene::numerate_arrows() {
    std::sort(this->arrows.begin(), this->arrows.end(), arr_com);
    for (int i = 0; i < this->arrows.size(); i++) {
        this->arrows[i]->setNum(i + 1);
    }
}

QVector<QVector<int>> MyQGraphicsScene::get_ligament() {
    QVector<QVector<int>> ligament(this->graph_nodes.size(),
                                   QVector<int>(this->graph_nodes.size(), 0));
    this->numerate_arrows();
    for (int i = 0; i < this->arrows.size(); i++) {
        ligament[static_cast<const GraphNode*>(this->arrows[i]->getStartItem())->getNum() - 1]
                [static_cast<const GraphNode*>(this->arrows[i]->getEndItem())->getNum() - 1] = 1;
    }
    return ligament;
}

void MyQGraphicsScene::clear() {
    for (auto& i : this->graph_nodes) delete i;
    this->graph_nodes.clear();
    for (auto& i : this->arrows) delete i;
    this->arrows.clear();
    this->current_node_index = 1;
    this->current_arrow = nullptr;
    this->update();
}

int MyQGraphicsScene::get_count_input_arrow(const GraphNode* node) {
    int count_input_arrow = 0;
    for (auto arrow : this->arrows) {
        if (arrow->getEndItem() == node) count_input_arrow++;
    }
    return count_input_arrow;
}

int MyQGraphicsScene::get_count_output_arrow(const GraphNode* node) {
    int count_output_arrow = 0;
    for (auto arrow : this->arrows) {
        if (arrow->getStartItem() == node) count_output_arrow++;
    }
    return count_output_arrow;
}

QMap<int, int> MyQGraphicsScene::hierarchical_level_selection() {
    QVector<QVector<int>> ligament = this->get_ligament();
    QMap<int, int> number_nodes;
    QSet<int> selected_nodes;
    QVector<QVector<int>> levels;
    bool select;
    QVector<int> level;
    int current_new_num = 0;
    while (selected_nodes.size() != ligament.size()) {
        for (int i = 0; i < ligament.size(); i++) {
            if (selected_nodes.contains(i)) continue;
            select = true;
            for (int j = 0; j < ligament.size(); j++) {
                if (ligament[j][i] == 1 and not selected_nodes.contains(j)) {
                    select = false;
                    break;
                }
            }
            if (select) {
                level.append(i);
                number_nodes[i] = current_new_num;
                current_new_num++;
            }
        }
        for (auto i : level) selected_nodes.insert(i);
        levels.append(level);
    }
    for (auto& i : this->graph_nodes) {
        i->setDefaultNum(i->getNum());
        i->setNum(number_nodes[i->getNum()-1]+1);
    }
    return number_nodes;
}

QVector<QVector<int>> MyQGraphicsScene::get_left_incident() {
    QVector<QVector<int>> left_incident(this->graph_nodes.size(),
                                   QVector<int>(0));
    this->numerate_arrows();
    for (int i = 0; i < this->arrows.size(); i++) {
        left_incident[static_cast<const GraphNode*>(this->arrows[i]->getStartItem())->getNum() - 1]
            .append(static_cast<const GraphNode*>(this->arrows[i]->getEndItem())->getNum() - 1);
    }
    return left_incident;
}

QVector<QVector<int>> MyQGraphicsScene::get_right_incident() {
    QVector<QVector<int>> right_incident(this->graph_nodes.size(),
                                   QVector<int>(0));
    this->numerate_arrows();
    for (int i = 0; i < this->arrows.size(); i++) {
        right_incident[static_cast<const GraphNode*>(this->arrows[i]->getEndItem())->getNum() - 1]
            .append(static_cast<const GraphNode*>(this->arrows[i]->getStartItem())->getNum() - 1);
    }
    return right_incident;
}

void MyQGraphicsScene::set_default() {
    for (auto& i : this->graph_nodes) {
        i->setNum(i->getDefaultNum());
    }
}
