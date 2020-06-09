/*
Filename : implementation.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
void read_values(double * a_start, double * b_start, double * eps)
{
	while(TRUE)
	{	
		while(!scanf("%lf", a_start))
		{
			SKIP_VALUE;
		}
		printf("Enter b: _\b");
		while(!scanf("%lf", b_start))
		{
			SKIP_VALUE;
		}
		if(is_continuous(*a_start, *b_start, EPS) == EXIT_FAILURE)
		{
			printf("Function is not continuous in the interval[%lf;%lf] \n", *a_start, *b_start);
			SKIP_VALUE;
		}
		else if(equation(*a_start) * equation(*b_start) > 0)
		{
			printf("No solutions: %lf * %lf = %lf > 0 \n", equation(*a_start),equation(*b_start), (equation(*a_start) * equation(*b_start) ));
			SKIP_VALUE;
		}
		else if(differential(*a_start) * differential(*b_start) < 0)
		{
			printf("More than one solution in the interval[%lf;%lf]\nf'(a) * f'(b) = %lf * %lf = %lf < 0 \n", 
			*a_start, *b_start, differential(*a_start), differential(*b_start), differential(*a_start) * differential(*b_start));
			SKIP_VALUE;
		}
		else
			break;
	}
	printf("Enter eps: ");
	while(!scanf("%lf", eps) || (*eps > fabs((*b_start) - (*a_start)) || (*eps <= 0)))
	{
		SKIP_VALUE;
	}
}
void newtons(double a, double b, double eps)
{
	double x_0 = 0, x_i = 0;
	int i = 0;
	if(equation(a) * differential2(a) > 0)
		x_0 = a; 
	else
		x_0 = b;
	printf("The Newton's method:\n");
	printf("i   x_0         x_i\n");
	while(equation(a) * equation(b) < 0)
	{
		x_i = x_0 - (equation(x_0)/differential(x_0));
		printf("%-2i %-+7lf %-+7lf\n", i, x_0, x_i);
		if(fabs(x_i - x_0) < eps)
			break;
		x_0 = x_i;
		++i;
	}
	printf("%d: %lf\n", i,  x_i);
	
}
void fixed_point_iteration(double a, double b, double eps)
{
	double x_0 = (a + b) / 2, x_i = 0, k = fabs(max(a, b, eps));
	int i = 0;
	printf("The Fixed point iteration method:\nk = %lf\n", k);
	printf("i   x_0         x_i\n");
	while(equation(a) * equation(b) < eps)
	{
		k = (differential(x_0)) > 0 ? k : -1 * k;
		x_i = x_0 - (( equation(x_0) )/ k);
		printf("%-2i %-+7lf %-+7lf\n", i, x_0, x_i);
		if(fabs(x_i - x_0) <= eps)
			break;
		x_0 = x_i;
		++i;
	}
	printf("%d: %lf\n", i,  x_i);
}
double max(double a, double b, double eps)
{
	double max = 0, x_0 = 0, x_n = 0;
	if(a > b)
	{
		x_0 = b;
		x_n = a;
	}
	else
	{
		x_0 = a;
		x_n = b;
	}
	double dx_0 = differential(x_0);
	max = dx_0;
	while(x_n > x_0)
	{
		dx_0 = differential(x_0);
		if(dx_0 > differential(max));
			max = dx_0;
		x_0 = x_0 + eps;
	}
	return max;
}
double differential(double x)
{
	double result = (1 / (cos(x-0.5) * cos(x-0.5))) - 5*cos(5*x);
	return result;
}
double differential2(double x)
{
	return (((2 * tan(x - 0.5)) / (cos(x - 0.5) * cos(x - 0.5) )) + (25 * sin(5 * (x))));
}
double equation(double x)
{
	if(x == (PI - 1) / 2) return NAN;
	return (tan((x) - 0.5) - sin(5 * (x)));
}
int is_continuous(double a, double b, double step)
{
	double x_0 = 0, x_n = 0, dx_0 = 0;
	if(a > b)
	{
		x_0 = b;
		x_n = a;
	}
	else
	{
		x_0 = a;
		x_n = b;
	}
	while(x_n > x_0)
	{
		dx_0 = differential(x_0);
		if(isnan(dx_0))
			return EXIT_FAILURE;
		x_0 += step;

		if(dx_0 * differential(x_0) < 0)
		{
			return EXIT_FAILURE;
		}	
	}
	return EXIT_SUCCESS;
}

