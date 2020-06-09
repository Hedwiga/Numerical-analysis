/*
 * Filename: mainwindow.h
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "approximation.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Approximation approximation;
    SqrMatrix symetricMatrix;
    Vector vector;
    TableFunction tableFunction;
    Vector linearPolynom;
    Vector squarePolynom;
    Vector cubePolynom;
    double linearDeviation;
    double squareDeviation;
    double cubeDeviation;

    void readFunction();
    Point readFromTable(int col);
    void setItemTo(QTableWidget * table, int row, int col, double data);
    void writeResults();

    void fillLinear();
    void fillLinearPolynomAndError();

    void fillSquare();
    void fillSquarePolynomAndError();

    void fillCube();
    void fillCubePolynomAndError();

    void fillMatrix(QTableWidget * table, Vector polynom);
    void fillVector(QTableWidget * table, Vector polynom);
};

#endif // MAINWINDOW_H
