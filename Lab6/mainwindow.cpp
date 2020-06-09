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
    double matrix[] = {
        1, -3,  2,
       -1,  0,  5,
       -2, -1, -2,
        3, -1, -5,
       -2, -1,  3
   };
    double vector[] = {
        -3,
        10,
         7,
        -1,
         4
   };
    MatrixA matrixTempA(matrix);
    VectorB matrixTempB(vector);
    matrixA = matrixTempA;
    matrixB = matrixTempB;
    showStartValues();
    matrixX = methodLeastSquares();
    showMatrixNC();
    showMatrixLU();
    showMatrixYX();

}

VectorX MainWindow::methodLeastSquares() {
    TMatrixA transposed = matrixA.transposed();
    matrixN = transposed * matrixA;
    matrixC = transposed * matrixB;
    return methodSquareRoot();
}

VectorX MainWindow::methodSquareRoot() {
    createTriangular();
    matrixU = matrixL.transposed();
    forward(M - 1);
    backward(0);
    return matrixX;
}


void MainWindow::createTriangular() {
    for(int i = 0; i < M ; ++i) {
        for(int j = i; j < M; ++j) {

            if(i == 0) {
                if(i == j) {
                    matrixL(i, j) = sqrt(matrixN(i, j));
                }
                else {
                    matrixL(j, 0) = matrixN(j, 0) / matrixL(0, 0);
                }
            }
            else if(i == j) {
                matrixL(i, j) = sqrt(matrixN(i, j) - sumSquares(i, 0));

            }
            else {
                matrixL(j, i) = (matrixN(j, i) - sumIJ(i, j, 0)) / matrixL(i, i);
            }
        }
    }
}

double MainWindow::sumSquares(int i, int p) {
    if(p == i - 1) {
        return matrixL(i, p) * matrixL(i, p);
    }

    return (matrixL(i, p) * matrixL(i, p)) + sumSquares(i, p + 1);
}

double MainWindow::sumIJ(int i, int j, int p) {
    if(p == i - 1) {
        return matrixL(i, p) * matrixL(j, p);
    }
    return matrixL(i, p) * matrixL(j, p) + sumIJ(i, j, p + 1);
}
double MainWindow::forward(int i) {
    if(i == 0) {
        return matrixY(i, 0) = matrixC(i, 0) / matrixL(i, i);
    }
    return matrixY(i, 0) = (1 / matrixL(i, i)) * (matrixC(i, 0) - sumForward(i, 0));
}
double MainWindow::sumForward(int i, int m) {
    if(m == i - 1) {
        return matrixL(i, m) * forward(m);
    }
    return matrixL(i, m) * forward(m) + sumForward(i, m + 1);
}
double MainWindow::backward(int i) {
    if(i == M - 1) {
        return matrixX(i, 0) = matrixY(i, 0) / matrixU(i, i);
    }
    return matrixX(i, 0) = (1 / matrixU(i, i)) * (matrixY(i, 0) - sumBackward(i, i + 1));
}
double MainWindow::sumBackward(int i, int m) {
    if(m == M - 1) {
        return matrixU(i, m) * backward(m);
    }
    return matrixU(i, m) * backward(m) + sumBackward(i, m + 1);
}
// Output functions
void MainWindow::showStartValues() {
    ui->matrixA->setRowCount(N);
    ui->matrixA->setColumnCount(M);
    ui->matrixB->setRowCount(N);
    ui->matrixB->setColumnCount(1);

    for(int i = 0; i < N; ++i) {
        QTableWidgetItem * itemB = new QTableWidgetItem;
        itemB->setText(QString::number(matrixB(i, 0)));
        ui->matrixB->setItem(i, 0, itemB);

        for(int j = 0; j < M; ++j) {
            QTableWidgetItem * itemA = new QTableWidgetItem;
            itemA->setText(QString::number(matrixA(i, j)));
            ui->matrixA->setItem(i, j, itemA);
        }
    }
}

void MainWindow::showMatrixNC() {
    ui->matrixN->setRowCount(M);
    ui->matrixN->setColumnCount(M);
    ui->matrixC->setRowCount(M);
    ui->matrixC->setColumnCount(1);
    for(int i = 0; i < M; ++i) {
        QTableWidgetItem * itemC = new QTableWidgetItem;
        itemC->setText(QString::number(matrixC(i, 0)));
        ui->matrixC->setItem(0, i, itemC);

        for(int j = 0; j < M; ++j) {
            QTableWidgetItem * itemN = new QTableWidgetItem;
            itemN->setText(QString::number(matrixN(i, j)));
            ui->matrixN->setItem(i, j, itemN);
        }
    }
}

void MainWindow::showMatrixLU() {
    ui->matrixL->setRowCount(M);
    ui->matrixL->setColumnCount(M);
    ui->matrixU->setRowCount(M);
    ui->matrixU->setColumnCount(M);
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < M; ++j) {
            QTableWidgetItem * itemL = new QTableWidgetItem;
            QTableWidgetItem * itemU = new QTableWidgetItem;
            itemL->setText(QString::number(matrixL(i, j)));
            itemU->setText(QString::number(matrixU(i, j)));
            ui->matrixL->setItem(i, j, itemL);
            ui->matrixU->setItem(i, j, itemU);
        }
    }
}

void MainWindow::showMatrixYX() {
    ui->matrixX->setRowCount(M);
    ui->matrixX->setColumnCount(1);
    ui->matrixY->setRowCount(M);
    ui->matrixY->setColumnCount(1);
    for(int i = 0; i < M; ++i) {
        QTableWidgetItem * itemX = new QTableWidgetItem;
        QTableWidgetItem * itemY = new QTableWidgetItem;
        itemX->setText(QString::number(matrixX(i, 0)));
        itemY->setText(QString::number(matrixY(i, 0)));
        ui->matrixX->setItem(i, 0, itemX);
        ui->matrixY->setItem(i, 0, itemY);

    }
}
MainWindow::~MainWindow() {
    delete ui;
}

