/*
 * Filename: equations.cpp
 */
#include "equations.h"
Equations::Equations() {
    curX = startX = -0.9;
    curY = startY = 0.5;
    eps = 0.003;
    results = nullptr;
}

Equations::Equations(double x, double y,
                     double error, QTableWidget *table) {
    curX = startX = x;
    curY = startY = y;
    results = table;
    eps = error;
}
void Equations::changeResultTable(QTableWidget *table) {
    results = table;
}

void Equations::methodIterations() {
    double prevX = startX, prevY = startY , error;
    curX = prevX;
    curY = prevY;
    int i = 0;
    while(true) {
        fillIteration(i);
        curX = calculateX(prevY);
        curY = calculateY(prevX);
        error = calculateError(prevX, prevY);
        ++i;
        if(error < eps) {
            break;
        }
        prevX = curX;
        prevY = curY;
    }
    fillIteration(i, Result);
    return;
}

void Equations::methodNewtons() {
    double prevX = startX, prevY = startY, errorX, errorY, jacobi, error;
    curX = prevX;
    curY = prevY;
    int i = 0;
    while(true) {
        fillIteration(i);
        jacobi = calculateJacobi(curX, curY);
        errorX = calculateErrorX(curX, curY);
        errorY = calculateErrorY(curX, curY);
        curX = calculateX(jacobi, errorX);
        curY = calculateY(jacobi, errorY);
        error = calculateError(prevX, prevY);
        ++i;
        if(error < eps){
            break;
        }
        prevX = curX;
        prevY = curY;
    }
    fillIteration(i, Result);
    return;
}
double Equations::calculateX(double yN) const {
    return -(0.4 + sin(yN));
}

double Equations::calculateY(double xN) const {
    return 0.5 * cos(xN + 1);
}
double Equations::calculateError(double prevX, double prevY) const {
    return fabs(curX - prevX) + fabs(curY - prevY);
}

double Equations::calculateJacobi(double xN, double yN) const {
    return (cos(yN) * sin(xN + 1)) - 2;
}

double Equations::calculateErrorX(double xN, double yN) const {
    return ((2 * yN - cos(xN + 1)) * cos(yN)) - (2 * (xN + sin(yN) + 0.4));
}

double Equations::calculateErrorY(double xN, double yN) const {
    return ((xN + sin(yN) + 0.4) * sin(xN + 1)) - 2 * yN + cos(xN + 1);
}

double Equations::calculateX(double jacobi, double errorX) const {
    return curX - (errorX / jacobi);
}

double Equations::calculateY(double jacobi, double errorY) const {
    return curY - (errorY / jacobi);
}

void Equations::fillIteration(int i, Status status) {
    QTableWidgetItem * itemX = new QTableWidgetItem;
    itemX->setText(QString::number(curX));
    QTableWidgetItem * itemY = new QTableWidgetItem;
    itemY->setText(QString::number(curY));
    if(status == Result) {
        QColor success(175, 255, 125);
        itemX->setBackgroundColor(success);
        itemY->setBackgroundColor(success);
    }

    results->insertRow(i);
    results->setItem(i, ColX, itemX);
    results->setItem(i, ColY, itemY);
}




