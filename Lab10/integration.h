/*
 * Filename: integration.h
 */

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QVector>
#include <math.h>

#include "constants.h"

class Integration {
    Vector function;
    double step;
    double halfStep;
    double eps;
    double a;
    double b;
    int n;

    const double &x(int i) const {return function.at(i).x;}
    const double &y(int i) const{return function.at(i).y;}
    const double &mid(int i) const{return function.at(i).midpoint;}


    double integrateBy(Methods formula);
    void calculateStartStep(Methods formula);
    void calculateFinalStep(Methods formula);
    void calculateFunction();
    double calculateFunctionIn(double x);
    double calculateBy(Methods formula);

    double leftSumRiemann(int i);
    double rightSumRiemann(int i);
    double midpointSumRiemann(int i);

    double sumSimpson();

    double calculateError(Methods method);
    double differentiateOf(Derivative order, double x);
    double sech(double x) {return 1.0/cosh(x);}

public:
    Integration(double theEps, double A, double B) : eps(theEps), a(A), b(B) {};
    double integrate(double & error, Methods formula);
    Vector getFunction();
};

#endif // INTEGRATION_H
