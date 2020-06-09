/*
 * Filename: mainwindow.cpp
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tableFunction.resize(Nodes);
    readFunction();
    readX();
    Interpolation func(tableFunction, solution.x);
    solution.y = func.lagrangeMethod();
    showLagrange();
    solution.y = func.newtonsMethod();
    showNewtons();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::readFunction() {
    for(int i = 0; i < Nodes; ++i)
        tableFunction.insert(i, readFromTable(i));
}

void MainWindow::readX() {
    solution = readFromTable(Nodes);
}

Interpolation::Point MainWindow::readFromTable(int row) {
    Interpolation::Point point;
    point.x = ui->table->item(row, Interpolation::X)->text().toDouble();
    point.y = ui->table->item(row, Interpolation::Y)->text().toDouble();
    return point;
}

void MainWindow::showLagrange() const {
    showSolution(Lagrange);
}

void MainWindow::showNewtons() const {
    showSolution(Newtons);
}

void MainWindow::showSolution(int row) const {
    ui->table->item(row, Interpolation::Y)->setText(QString::number(solution.y));
}

