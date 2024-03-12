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
        QVector<QVector<int>> right_incident = this->scene->get_right_incident();
        ui->right_incident->clear();
        for (int i = 0; i < right_incident.size(); i++) {
            ui->right_incident->insertPlainText("G-(" +
                                                QString::number(i + 1) +
                                                ") = {");
            for (int j = 0; j < right_incident[i].size(); j++) {
                ui->right_incident->insertPlainText(QString::number(right_incident[i][j] + 1) +
                                                    ((j + 1 < right_incident[i].size()) ? ", " : "}\n") );
            }
            if (right_incident[i].size() == 0)
                ui->right_incident->insertPlainText("}\n");
        }
        QVector<QVector<int>> left_incident = this->scene->get_left_incident();
        ui->left_incident->clear();
        for (int i = 0; i < left_incident.size(); i++) {
            ui->left_incident->insertPlainText("G+(" +
                                                QString::number(i + 1) +
                                                ") = {");
            for (int j = 0; j < left_incident[i].size(); j++) {
                ui->left_incident->insertPlainText(QString::number(left_incident[i][j] + 1) +
                                                    ((j + 1 < left_incident[i].size()) ? ", " : "}\n") );
            }
            if (left_incident[i].size() == 0)
                ui->left_incident->insertPlainText("}\n");
        }
    }
}

void GraphConv::on_pushButton_clicked()
{
    this->scene->clear();
}


void GraphConv::on_pushButton_2_clicked()
{
    this->scene->hierarchical_level_selection();
    this->scene->update();
}


void GraphConv::on_pushButton_3_clicked()
{
    this->scene->set_default();
    this->scene->update();
}

