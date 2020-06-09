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

    QMatrix4x4 matrixA
    (
         1.13,  0.27, -0.22, -0.18,
        -0.21, -0.65,  0.18, -0.18,
         0.12,  0.13, -0.73,  0.18,
         0.33, -0.05,  0.06, -1.28
    );
    qDebug() << matrixA(0, 0);
    QVector<double> matrixB(N);
    matrixB.insert(0, -1.21);
    matrixB.insert(1, -0.33);
    matrixB.insert(2, 0.48);
    matrixB.insert(3, -0.17);
    eps = 0.001;
    jacobiMethod(matrixA, matrixB);
    seidelMethod(matrixA, matrixB);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::jacobiMethod(const QMatrix4x4 A, const QVector<double> B)
{
    QVector<double> X = B;
    QVector<double> tempX;
    double maxDelta = 0;
    int k = 0;
    do
    {
        ui->jacobiTable->insertRow(k);
        QTableWidgetItem * index = new QTableWidgetItem;
        index->setText(QString::number(k));
        ui->jacobiTable->setItem(k, K, index);

        tempX = X;
        for(int i = 0; i < N; ++i)
        {
            double temp = 0;
            for(int j = 0; j < i; ++j)
                temp += (A(i, j) * tempX[j]);
            for(int j = i + 1; j < N; ++j)
                temp += (A(i, j) * tempX[j]);
            X[i] = (B[i] - temp) / A(i, i);

            QTableWidgetItem * xN = new QTableWidgetItem;
            xN->setText(QString::number(X[i]));
            ui->jacobiTable->setItem(k, i + 1, xN);
        }
        maxDelta = findMaxDelta(X, tempX);

        QTableWidgetItem * delta = new QTableWidgetItem;
        delta->setText(QString::number(maxDelta));
        ui->jacobiTable->setItem(k, DELTA, delta);

        ++k;
    }while(maxDelta > eps);


}

void MainWindow::seidelMethod(const QMatrix4x4 A, const QVector<double> B)
{
    QVector<double> X = B;
    QVector<double> tempX;
    double maxDelta = 0;
    int k = 0;
    do
    {
        ui->seidelTable->insertRow(k);
        QTableWidgetItem * index = new QTableWidgetItem;
        index->setText(QString::number(k));
        ui->seidelTable->setItem(k, K, index);

        tempX = X;
        for(int i = 0; i < N; ++i)
        {
            double temp = 0;
            for(int j = 0; j < i; ++j)
                temp += A(i, j) * X[j];
            for(int j = i + 1; j < N; ++j)
                temp += A(i, j) * tempX[j];

            X[i] = (B[i] - temp) / A(i, i);
            QTableWidgetItem * xN = new QTableWidgetItem;
            xN->setText(QString::number(X[i]));
            ui->seidelTable->setItem(k, i + 1, xN);
        }
        maxDelta = findMaxDelta(X, tempX);

        QTableWidgetItem * delta = new QTableWidgetItem;
        delta->setText(QString::number(maxDelta));
        ui->seidelTable->setItem(k, DELTA, delta);

        ++k;
    }while(maxDelta > eps);


}
double MainWindow::findMaxDelta(const QVector<double> X, const QVector<double> tempX)
{
    double maxDelta = fabs(X[0] - tempX[0]);
    double tempDelta;
    for(int i = 0; i < N; ++i)
    {
        tempDelta = fabs(X[i] - tempX[i]);
        if(tempDelta > maxDelta)
            maxDelta = tempDelta;
    }
    return maxDelta;
}
