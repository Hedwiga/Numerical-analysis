/*
Filename: main.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constants.h"
int main()
{
	double a_start = 0, b_start = 0,  eps = 0;
	int i = 0;
	printf("Enter a: _\b");
	read_values(&a_start, &b_start, &eps);
	newtons(a_start, b_start, eps);
	fixed_point_iteration(a_start, b_start, eps); 
	
	return EXIT_SUCCESS;	
}

