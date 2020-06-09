/*
 * Filename: equations.h
 */
#ifndef EQUATIONS_H
#define EQUATIONS_H
#include <math.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "QString"
class Equations
{
    double curX;
    double curY;
    double startX;
    double startY;
    double eps;

    QTableWidget * results;
    enum { ColX, ColY};
    enum Status { Iteration, Result };
    void fillIteration(int i, Status = Iteration);
//  Fixed-point iterations method
    double calculateX(double xn) const;
    double calculateY(double yn) const;
    double calculateError(double xn, double yn) const;
//  Newton's method
    double calculateJacobi(double xn, double yn) const;
    double calculateErrorX(double xN, double yN) const;
    double calculateErrorY(double xN, double yN) const;
    double calculateX(double jacobi, double errorX) const;
    double calculateY(double jacobi, double errorY) const;

public:
    Equations();
    Equations(double startX, double startY, double eps,
              QTableWidget *results);
    void changeResultTable(QTableWidget *results);
    void methodIterations();
    void methodNewtons();
};

#endif // EQUATIONS_H
