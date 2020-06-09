/*
 * Filename: intepolation.cpp
 */
#include "interpolation.h"
Interpolation::Interpolation() {
    nodes = 0;
    function.resize(0);
}

Interpolation::Interpolation(const Interpolation::TableFunction &func, double x) {
    function = func;
    next.x = x;
    defineAmountOfNodes();
    function.resize(nodes);
}
void Interpolation::defineAmountOfNodes() {
    for(int i = 0; i < function.size(); ++i) {
        if(x(i) > next.x) {
            nodes = ++i;
            return;
        }
    }
    nodes = 0;
    exit(EXIT_FAILURE);
}
double Interpolation::lagrangeMethod() {
    return next.y = lagrangeLinearCombination(0);
}
double Interpolation::lagrangeLinearCombination(int j) {
    if(j == nodes - 1)
        return y(j) * lagrangeBasisPolynomial(0, j);
    return  y(j) * lagrangeBasisPolynomial(0, j) + lagrangeLinearCombination(j + 1);
}
double Interpolation::lagrangeBasisPolynomial(int i, int j) {
    if(i == j)
        if(i == nodes - 1) return 1;
        else return lagrangeBasisPolynomial(i + 1, j);
    if(i == nodes - 1)
        return (next.x - x(i)) / (x(j) - x(i));
    return ((next.x - x(i))/(x(j) - x(i))) * lagrangeBasisPolynomial(i + 1, j);
}


double Interpolation::newtonsMethod() {
    return newtonsLinearCombination(0);
}
double Interpolation::newtonsLinearCombination(int j) {
    if(j == nodes - 1)
        return  dividedDifference(0, j) * newtonsBasisPolynomial(0, j);
    return dividedDifference(0, j) * newtonsBasisPolynomial(0, j)
            + newtonsLinearCombination(j + 1);
}
double Interpolation::newtonsBasisPolynomial(int i, int j) {
    if(j == 0)
        return 1;
    if(i == j - 1)
        return (next.x - x(i));
    return (next.x - x(i)) * newtonsBasisPolynomial(i + 1, j);
}
double Interpolation::dividedDifference(int j, int n) {
    if(n == 0)
        return y(j);
    if(j == n - 1)
        return (y(n) - y(j))/(x(n) - x(j));
    return (dividedDifference(j + 1, n) - dividedDifference(j, n - 1))/(x(n) - x(0));
}
