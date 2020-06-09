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
    readFunction();
    approximation.setTableFunction(tableFunction);
    linearPolynom = approximation.methodLeastSquares(Linear, linearDeviation);
    squarePolynom = approximation.methodLeastSquares(Square, squareDeviation);
    cubePolynom = approximation.methodLeastSquares(Cube, cubeDeviation);
    symetricMatrix = approximation.getSymetricMatrix();
    vector = approximation.getVector();
    writeResults();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::readFunction() {
    tableFunction.resize(N);
    for(int i = 0; i < N; ++i)
        tableFunction.insert(i, readFromTable(i));
}

Point MainWindow::readFromTable(int col) {
    Point point;
    point.x = ui->inputTable->item(X, col)->text().toDouble();
    point.y = ui->inputTable->item(Y, col)->text().toDouble();
    return point;
}

void MainWindow::writeResults() {
    fillLinear();
    fillSquare();
    fillCube();
}

void MainWindow::fillLinear() {
    fillLinearPolynomAndError();
    fillMatrix(ui->matrix1, linearPolynom);
    fillVector(ui->vector1, linearPolynom);
}

void MainWindow::fillLinearPolynomAndError() {
    ui->a0Linear->setText(QString::number(linearPolynom[Null]));
    ui->a1Linear->setText(QString::number(linearPolynom[Linear]));
    ui->error1->setText(QString::number(linearDeviation));
}

void MainWindow::fillSquare() {
    fillSquarePolynomAndError();
    fillMatrix(ui->matrix2, squarePolynom);
    fillVector(ui->vector2, squarePolynom);
}

void MainWindow::fillSquarePolynomAndError() {
    ui->a0Square->setText(QString::number(squarePolynom[Null]));
    ui->a1Square->setText(QString::number(squarePolynom[Linear]));
    ui->a2Square->setText(QString::number(squarePolynom[Square]));
    ui->error2->setText(QString::number(squareDeviation));
}

void MainWindow::fillCube() {
    fillCubePolynomAndError();
    fillMatrix(ui->matrix3, cubePolynom);
    fillVector(ui->vector3, cubePolynom);
}

void MainWindow::fillCubePolynomAndError() {
    ui->a0Cube->setText(QString::number(cubePolynom[Null]));
    ui->a1Cube->setText(QString::number(cubePolynom[Linear]));
    ui->a2Cube->setText(QString::number(cubePolynom[Square]));
    ui->a3Cube->setText(QString::number(cubePolynom[Cube]));
    ui->error3->setText(QString::number(cubeDeviation));
}

void MainWindow::fillMatrix(QTableWidget *table, Vector polynom) {
    for(int row = 0; row < polynom.size(); ++row)
        for(int col = 0; col < polynom.size(); ++col)
            setItemTo(table, row, col, polynom[row]);
}

void MainWindow::fillVector(QTableWidget *table, Vector polynom) {
    for(int col = 0; col < polynom.size(); ++col)
        setItemTo(table, X, col, polynom[col]);
}

void MainWindow::setItemTo(QTableWidget *table, int row, int col, double data) {
    QTableWidgetItem * item = new QTableWidgetItem;
    item->setText(QString::number(data));
    table->setItem(row, col, item);
}

