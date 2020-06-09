/*
 * Filename: constants.h
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QGenericMatrix>
#include <QVector>

struct Point {
    double x;
    double y;
};
enum {HALF_N = 3, N = 6, MAX_SYMETRIC = N / 2 + 1};
enum {X = 0, Y = 1};
enum {Null = 0, Linear = 1, Square = 2, Cube = 3};
typedef QVector <Point> TableFunction;
typedef QGenericMatrix <MAX_SYMETRIC, MAX_SYMETRIC, double> SqrMatrix;
typedef QVector <double> Vector;

#endif // CONSTANTS_H
