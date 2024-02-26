#include "graphconv.h"
#include "./ui_graphconv.h"

#include <QDebug>

GraphConv::GraphConv(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphConv) {
    ui->setupUi(this);
    this->scene = new MyQGraphicsScene();
    ui->graphicsView->setScene(this->scene);
}

GraphConv::~GraphConv() {
    delete ui;
}

void GraphConv::on_tabWidget_currentChanged(int index) {
    if (index == 1) {
        qInfo() << "out";
        QVector<QVector<int>> incident = this->scene->get_incident();
        QStandardItemModel *incident_model = new QStandardItemModel(this);
        for (int i = 0; i < incident.size(); i++) {
            for (int j = 0; j < incident[i].size(); j++) {
                QStandardItem* item = new QStandardItem(QString::number(incident[i][j]));
                incident_model->setItem(i, j, item);
            }
        }
        ui->incident->setModel(incident_model);
        ui->incident->resizeColumnsToContents();
        QVector<QVector<int>> ligament = this->scene->get_ligament();
        QStandardItemModel *ligament_model = new QStandardItemModel(this);
        for (int i = 0; i < ligament.size(); i++) {
            for (int j = 0; j < ligament[i].size(); j++) {
                QStandardItem* item = new QStandardItem(QString::number(ligament[i][j]));
                ligament_model->setItem(i, j, item);
            }
        }
        ui->ligament->setModel(ligament_model);
        ui->ligament->resizeColumnsToContents();
    }
}
