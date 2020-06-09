/*
 * Filename: approximation.cpp
 */

#include "approximation.h"

void Approximation::setTableFunction(const TableFunction & func) {
    resizeVectors();
    function = func;
    fillSumsOfDegrees();
    fillSymetricMatrix();
}

void Approximation::resizeVectors() {
    function.resize(N);
    sumsOfDegreesX.resize(N);
    sumsOfDegreesY.resize(HALF_N);
}

void Approximation::fillSumsOfDegrees() {
    fillSumsOfDegreesX();
    fillSumsOfDegreesY();
}

void Approximation::fillSumsOfDegreesX() {
    for(int i = 0; i < N + 1; ++i)
        sumsOfDegreesX.insert(i, sumOfDegreesX(i, 0));
}

double Approximation::sumOfDegreesX(int degree, int col) {
    if(col == N - 1) return pow(x(col), degree);
    return pow(x(col), degree) + sumOfDegreesX(degree, col + 1);
}

void Approximation::fillSumsOfDegreesY() {
    for(int i = 0; i < HALF_N + 1; ++i)
        sumsOfDegreesY.insert(i, sumOfDegreesY(i, 0));
}

double Approximation::sumOfDegreesY(int degree, int col) {
    if(col == N - 1) return y(col) * pow(x(col), degree);
    return y(col) * pow(x(col), degree) + sumOfDegreesY(degree, col + 1);
}
void Approximation::fillSymetricMatrix() {
    for(int row = 0; row < MAX_SYMETRIC; ++row)
        for(int col = 0; col < MAX_SYMETRIC; ++col)
            symetricMatrix(row, col) = sumsOfDegreesX[row + col];
}

Vector Approximation::methodLeastSquares(int degree, double &deviation) {
    if(degree > MAX_SYMETRIC) exit(EXIT_FAILURE);
    LinearSystem system(symetricMatrix, sumsOfDegreesY, degree + 1);
    polynom.resize(degree);
    polynom = system.methodSquareRoot();
    deviation = calculateDeviation();
    return polynom;
}

double Approximation::calculateDeviation() {
    return sqrt((1.0 /(N + 1)) * sumOfDeltaSquares(0));
}

double Approximation::sumOfDeltaSquares(int i) {
    if(i == N - 1) return pow(calculateFunction(x(i), polynom.size() - 1) - y(i), Square);
    return pow(calculateFunction(x(i), polynom.size() - 1) - y(i), Square)
            + sumOfDeltaSquares(i + 1);
}

double Approximation::calculateFunction(double x, double i) {
    if(i == 0) return polynom[i];
    return polynom[i] * pow(x, i) + calculateFunction(x, i - 1);
}
