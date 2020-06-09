/*
Filename: main.c
*/

#include <stdio.h>
#include <math.h>
#include "constants.h"

void bisection(double a, double b, double eps);
void secant(double a, double b, double eps);

int main(void)
{
	double a_start = 0, b_start = 0,  eps = 0;
	int i = 0;
	printf("Enter a: _\b");
	while(1)
	{
		
		while(!scanf("%lf", &a_start))
		{
			SKIP_VALUE;
		}
		printf("Enter b: _\b");
		while(!scanf("%lf", &b_start))
		{
			SKIP_VALUE;
		}
		if(EQUATION(a_start) * EQUATION(b_start) > 0)
		{
			printf("No solutions\n");
			SKIP_VALUE;
		}
		else if(DIFFERENTIAL(a_start) * DIFFERENTIAL(b_start) < 0)
		{
			printf("More than one solution in the interval[%lf;%lf]\n", a_start, b_start);
			SKIP_VALUE;
		}
		else
			break;
	}
			
	
	printf("Enter eps: ");
	while(!scanf("%lf", &eps) || (eps > fabs(b_start - a_start)) || (eps <= 0))
	{
		SKIP_VALUE;
	}
	secant(a_start, b_start, eps);
	bisection(a_start, b_start, eps);
	
	return 0;
	
}
void bisection(double a, double b, double eps)
{
	double x = 0, fx = 0, fx_a = EQUATION(a), fx_b = EQUATION(b);
	int i = 0;
	printf("The bisection method:\n");
	printf("i   a         b         x          fx\n");	
	while(fx_a * fx_b < 0)
	{
		x = (a + b)/2;
		fx = EQUATION(x);
		printf("%-2i %-+7lf %-+7lf %-+7lf %-+7lf \n", i, a, b, x, fx);
		if(fabs(b - a) < eps) break;
		else if(fx == 0) break;
		else if(fx_a * fx < 0) 
			b = x;
		else
			a = x;
		++i;
	}
	printf("%d: %lf\n", i, x);
}
void secant(double a, double b, double eps)
{
	double x_0 = 0, x_i = 0, x_n = 0, fx_0 = 0, fx_i = 0, fx_n = 0;
	int i = 0;
	if(EQUATION(a) * DIFFERENTIAL_2(a) < 0)
	{
		x_n = b;
		x_0 = a; 
	}
	else
	{
		x_n = a;
		x_0 = b;
	}
	printf("The secant method:\n");
	printf("i   x_0         x_i\n");
	while(1)
	{
		fx_0 = EQUATION(x_0);
		fx_n = EQUATION(x_n);
		x_i = x_0 - (((x_n - x_0) / (fx_n - fx_0)) * fx_0);
		printf("%-2i %-+7lf %-+7lf\n", i, x_0, x_i);
		if(fabs(x_i - x_0) < eps)
			break;
		x_0 = x_i;		
		++i;
	}
	x_i = (x_0 + x_i) / 2;
	printf("%d: %lf\n", i,  x_i);

}
