#ifndef GRAPHCONV_H
#define GRAPHCONV_H

#include <QMainWindow>
#include <QRectF>
#include <QStandardItemModel>
#include "myqgraphicsscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GraphConv;
}
QT_END_NAMESPACE

class GraphConv : public QMainWindow
{
    Q_OBJECT

public:
    GraphConv(QWidget *parent = nullptr);
    ~GraphConv();

private slots:
    void on_tabWidget_currentChanged(int index);

private:
    Ui::GraphConv *ui;
    MyQGraphicsScene* scene;
};
#endif // GRAPHCONV_H
