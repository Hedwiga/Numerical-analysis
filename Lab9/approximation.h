/*
 * Filename: approximation.h
 */

#ifndef APPROXIMATION_H
#define APPROXIMATION_H

#include <QTableWidget>
#include <QTableWidgetItem>

#include <math.h>

#include "constants.h"
#include "linearsystem.h"

class Approximation {

private:
    TableFunction function;
    SqrMatrix symetricMatrix;
    Vector sumsOfDegreesX;
    Vector sumsOfDegreesY;
    Vector polynom;

    void resizeVectors();

    void fillSumsOfDegrees();
    void fillSumsOfDegreesX();
    void fillSumsOfDegreesY();
    void fillSymetricMatrix();

    double sumOfDegreesX(int col, int degree);
    double sumOfDegreesY(int col, int degree);

    double calculateDeviation();
    double sumOfDeltaSquares(int i);
    double calculateFunction(double x, double i);

    double x(int i) const {return function[i].x;}
    double y(int i) const {return function[i].y;}
public:
    Approximation() {};
    void setTableFunction(const TableFunction & func);
    Vector methodLeastSquares(int degree, double & deviation);
    SqrMatrix getSymetricMatrix() {return symetricMatrix;}
    Vector getVector() {return sumsOfDegreesY;}
};

#endif // APPROXIMATION_H
