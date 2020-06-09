/*
 * Filename: constants.h
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QVector>

struct Point {
    double x;
    double y;
    double midpoint;
};

typedef QVector<Point> Vector;

enum Methods {LeftRiemann, RightRiemann, MidpointRiemann, Simpsons, Trapezodial};
enum Derivative {Second = 2, Fourth = 4};
enum {X, Y, MIDPOINT};

struct IntegrationResult {
    double result;
    double error;
    Vector table;
};

#endif // CONSTANTS_H
