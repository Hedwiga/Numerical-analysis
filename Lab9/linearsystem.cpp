/*
 * Filename: linearsystem.cpp
 */

#include "linearsystem.h"

LinearSystem::LinearSystem(SqrMatrix matrixA, Vector matrixB, int theDegree) {
    degree = theDegree;
    matrixC.resize(theDegree);
    matrixY.resize(theDegree);
    matrixX.resize(theDegree);
    matrixN = matrixA;
    matrixC = matrixB;
}

Vector LinearSystem::methodSquareRoot() {
    createTriangular();
    matrixU = matrixL.transposed();
    forward(degree - 1);
    backward(0);
    return matrixX;
}

void LinearSystem::createTriangular() {
    for(int i = 0; i < degree ; ++i)
        for(int j = i; j < degree; ++j)
            if(i == 0)
                if(i == j) matrixL(i, j) = sqrt(matrixN(i, j));
                else matrixL(j, 0) = matrixN(j, 0) / matrixL(0, 0);
            else if(i == j)  matrixL(i, j) = sqrt(matrixN(i, j) - sumSquares(i, 0));
            else matrixL(j, i) = (matrixN(j, i) - sumIJ(i, j, 0)) / matrixL(i, i);
}

double LinearSystem::sumSquares(int i, int p) {
    if(p == i - 1) return matrixL(i, p) * matrixL(i, p);
    return (matrixL(i, p) * matrixL(i, p)) + sumSquares(i, p + 1);
}

double LinearSystem::sumIJ(int i, int j, int p) {
    if(p == i - 1) return matrixL(i, p) * matrixL(j, p);
    return matrixL(i, p) * matrixL(j, p) + sumIJ(i, j, p + 1);
}

double LinearSystem::forward(int i) {
    if(i == 0) return matrixY[i] = matrixC[i] / matrixL(i, i);
    return matrixY[i] = (1 / matrixL(i, i)) * (matrixC[i] - sumForward(i, 0));
}

double LinearSystem::sumForward(int i, int m) {
    if(m == i - 1) return matrixL(i, m) * forward(m);
    return matrixL(i, m) * forward(m) + sumForward(i, m + 1);
}

double LinearSystem::backward(int i) {
    if(i == degree - 1) return matrixX[i] = matrixY[i] / matrixU(i, i);
    return matrixX[i] = (1 / matrixU(i, i)) * (matrixY[i] - sumBackward(i, i + 1));
}

double LinearSystem::sumBackward(int i, int m) {
    if(m == degree - 1) return matrixU(i, m) * backward(m);
    return matrixU(i, m) * backward(m) + sumBackward(i, m + 1);
}
