/*
 * Filename: mianwindow.cpp
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_calculate_clicked() {
    if(!readValues()) return;
    integrateByMethods();
    writeResults();
}

bool MainWindow::readValues() {
    try {
        readIntervalsAndEps();
    } catch (const QString & warning){
        ui->warning->setText(warning);
        return false;
    }
    ui->warning->clear();
    return true;
}

void MainWindow::readIntervalsAndEps() {
    b = ui->b->value();
    a = ui->a->value();
    eps = ui->eps->value();
    if(!eps)
        throw QString("Введіть точність");
    if(b - a <= 0)
        throw QString("Верхня межа має бути більша за нижню");
}

void MainWindow::integrateByMethods() {
    riemannLeft = integrateBy(LeftRiemann);
    riemannRight = integrateBy(RightRiemann);
    riemannMidpoint = integrateBy(MidpointRiemann);
    simpson = integrateBy(Simpsons);
    trapezoidal = integrateBy(Trapezodial);
}

IntegrationResult MainWindow::integrateBy(Methods method) {
    Integration integral(eps, a, b);
    double error;
    double result = integral.integrate(error, method);
    Vector tableFunction = integral.getFunction();
    return {result, error, tableFunction};
}

void MainWindow::writeResults() {
    writeRiemann();
    writeSimpson();
    writeTrapezoidal();
}

void MainWindow::writeRiemann() {
    writeInTable(riemannMidpoint, ui->tableRiemann);
    writeInLine(riemannLeft.error, ui->errorRiemannLeft);
    writeInLine(riemannRight.error, ui->errorRiemannRight);
    writeInLine(riemannMidpoint.error, ui->errorRiemannMidpoint);

    writeInLine(riemannLeft.result, ui->integralLeft);
    writeInLine(riemannRight.result, ui->integralRight);
    writeInLine(riemannMidpoint.result, ui->integralMidpoint);
}

void MainWindow::writeSimpson() {
    writeInTable(simpson, ui->tableSimpson);
    writeInLine(simpson.error, ui->errorSimpson);
    writeInLine(simpson.result, ui->integralSimpson);
}

void MainWindow::writeTrapezoidal() {
    writeInTable(trapezoidal, ui->tableTrapezoidal);
    writeInLine(trapezoidal.error, ui->errorTrapezoidal);
    writeInLine(trapezoidal.result, ui->integralTrapezoidal);
}

void MainWindow::writeInTable(IntegrationResult integral, QTableWidget *table) {
    table->setRowCount(integral.table.size());
    for(int i = 0; i < integral.table.size(); ++i) {
        table->setItem(i, X, createItem(integral.table.at(i).x));
        table->setItem(i, Y, createItem(integral.table.at(i).y));
        table->setItem(i, MIDPOINT, createItem(integral.table.at(i).midpoint));
    }
}

QTableWidgetItem * MainWindow::createItem(double data) {
    QTableWidgetItem * newItem = new QTableWidgetItem;
    newItem->setText(QString::number(data));
    return newItem;
}

void MainWindow::writeInLine(double data, QLineEdit *line) {
    line->setText(QString::number(data));
}
