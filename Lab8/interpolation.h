/*
 * Filename: intepolation.h
 */
#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include <math.h>
#include <QVector>
class Interpolation
{
public:
    struct Point {
        double x;
        double y;
    };
    typedef QVector <Point> TableFunction;
    enum {X = 0, Y = 1, Values};
private:
    int nodes;
    TableFunction function;
    Point next;

    double x(int i) const {return function[i].x;}
    double y(int i) const {return function[i].y;}

    double lagrangeBasisPolynomial(int i, int j);
    double lagrangeLinearCombination(int j);
    double newtonsBasisPolynomial(int i, int j);
    double newtonsLinearCombination(int j);
    double dividedDifference(int j, int n);
    void defineAmountOfNodes();
public:
    Interpolation();
    Interpolation(const TableFunction & func, double x);
    double lagrangeMethod();
    double newtonsMethod();
};

#endif // INTERPOLATION_H
