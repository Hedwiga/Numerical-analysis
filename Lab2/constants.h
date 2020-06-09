/*
Filename : constants.h
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define EPS 0.00002
#define PI 3.1415926
#define SKIP_VALUE while(getchar() != '\n') continue; printf("\nIncorrect value! Try again: _\b");
#define TRUE 1
#define FALSE 0
double equation(double x);
double differential(double x);
double differential2(double x);
void newtons(double a, double b, double eps);
void fixed_point_iteration(double a, double b, double eps);
double max(double a, double b, double eps);
int is_continuous(double a, double b, double step);
void read_values(double * a_start, double * b_start, double * eps);


#endif
