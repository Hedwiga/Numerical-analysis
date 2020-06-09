/*
 * Filename: linearsystem.h
 */

#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include <math.h>

#include "constants.h"

class LinearSystem
{
    int degree;
    SqrMatrix matrixN;
    SqrMatrix matrixL;
    SqrMatrix matrixU;
    Vector matrixC;
    Vector matrixY;
    Vector matrixX;

    void createTriangular();
    double sumSquares(int i, int p);
    double sumIJ(int i, int j, int p);
    double forward(int i);
    double sumForward(int i, int m);
    double backward(int i);
    double sumBackward(int i, int m);
public:
    LinearSystem(SqrMatrix matrixA, Vector matrixB, int theDegree);
    Vector methodSquareRoot();
};

#endif // LINEARSYSTEM_H
