/*
 * Filename: integration.cpp
 */

#include "integration.h"

double Integration::integrate(double & error, Methods formula) {
    calculateStartStep(formula);
    calculateFinalStep(formula);
    double integral = integrateBy(formula);
    error = calculateError(formula);
    return integral;
}

Vector Integration::getFunction() {
    return function;
}

void Integration::calculateStartStep(Methods formula) {
    int m;
    if(formula == Simpsons) {
        m = 4;
        step = pow(eps, 1.0/m);
        n = floor(fabs((b - a)/step));
        if(!n) {
            n += 2;
            step = fabs((b - a)/n);
        }
        if(!(n % 2)) {
            n += 1;
            step = fabs((b - a)/n);
        }
    }
    else {
        m = 2;
        step = pow(eps, 1.0/m);
        n = floor(fabs((b - a)/step));
        if(n < 2) {
            n += 2;
            step = fabs((b - a)/n);
        }
    }
}

void Integration::calculateFinalStep(Methods formula) {
    double integralFirstStep = integrateBy(formula);
    step /= 2;
    double integralHalfStep = integrateBy(formula);
    if(fabs(integralFirstStep - integralHalfStep) > eps)
        step /= 2;
}

double Integration::integrateBy(Methods formula) {
    calculateFunction();
    return calculateBy(formula);
}

void Integration::calculateFunction() {
    function.clear();
    Point temp;
    temp.x = a;
    while(temp.x <= b) {
        temp.y = calculateFunctionIn(temp.x);
        temp.midpoint = calculateFunctionIn(temp.x + step/2);
        function.push_back(temp);
        temp.x += step;
    }
    n = function.size();
}

double Integration::calculateFunctionIn(double x) {
    return double(cbrt(tanh(x)));
}

double Integration::calculateBy(Methods formula) {
    double integral;
    switch(formula) {
    case LeftRiemann:
        integral = step * leftSumRiemann(0);
        break;
    case RightRiemann:
        integral = step * rightSumRiemann(1);
        break;
    case MidpointRiemann:
        integral = step * midpointSumRiemann(0);
        break;
    case Simpsons: {
        integral = double(step/3.0) * sumSimpson();
        break;
    }
    case Trapezodial:
        integral = step * ((y(0) + y(n - 1))/2 + leftSumRiemann(1));
        break;
    }
    return integral;
}

double Integration::leftSumRiemann(int i) {
    if(i >= n - 2) return y(i);
    return y(i) + leftSumRiemann(i + 1);
}

double Integration::rightSumRiemann(int i) {
    if(i >= n - 1) return y(i);
    return y(i) + rightSumRiemann(i + 1);
}

double Integration::midpointSumRiemann(int i) {
    if(i >= n - 2) return mid(i);
    return mid(i) + midpointSumRiemann(i + 1);
}

double Integration::sumSimpson() {
    double sumOdd = 0, sumEven = 0;
    for(int i = 1; i < n; ++i)
        if(!(i % 2) && (i < n - 1))
            sumEven += y(i);
        else if(i % 2)
            sumOdd += y(i); 
    return y(0) + y(n - 2) + 4 * sumOdd + 2 * sumEven;
}

double Integration::calculateError(Methods method) {
    double error;
    switch(method) {
    case LeftRiemann:
    case RightRiemann:
    case MidpointRiemann:
        error = -(differentiateOf(Second, b)/24) * (b - a) * pow(step, 2);
        break;
    case Simpsons:
        error = -(differentiateOf(Fourth, b)/2880) * pow(b - a, 5);
        break;
    case Trapezodial:
        error = -(differentiateOf(Second, b)/12) * (b - a)* pow(step, 2);
        break;
    }
    return error;
}

double Integration::differentiateOf(Derivative order, double x) {
    double derivative;
    switch(order) {
    case Second:
        derivative = (-2*(pow(sech(x), 4) + (3*pow(tanh(x), 2)*pow(sech(x), 2))))
                /(9*pow(tanh(x), 5.0/3));
        break;
    case Fourth:
        derivative = (-8*(10*pow(sech(x), 8) + 27*pow(tanh(x), 2) * pow(sech(x), 6) +
               9*pow(tanh(x), 4)*pow(sech(x), 4) + 27*pow(tanh(x), 6)*pow(sech(x), 2)))
               / (81*pow(tanh(x), 11.0/3));
        break;
    }
    return derivative;
}






