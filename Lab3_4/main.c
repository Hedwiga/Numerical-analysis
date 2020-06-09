/*
Filename: main.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#define LAB_4
int main()
{
	SqrMatrix matrixA = 
	{
	1.24, 0.87, 3.17,
	2.11, 0.45, 1.44,
	0.48, 1.25, 0.63
	};
	Vector matrixB =
	{
	0.46,
	1.50,
	0.35
	};
	Vector matrixX = {0.0};
	
	showEquations(matrixA, matrixB);
	
#ifdef LAB_3

	printf("\nCramer's method:\n");
	if(cramersRule(matrixA, matrixB, matrixX) == EXIT_FAILURE)
	{
		printf("No solutions");
		return EXIT_FAILURE;
	}
	printf("\nSolution:\n");
	showVector(matrixX, N, 'x');
	printf("\nMatrix solution:\n");
	if(matrixSolution(matrixA, matrixB, matrixX) == EXIT_FAILURE)
	{
		printf("No solutions");
		return EXIT_FAILURE;
	}
	printf("\nSolution:\n");
	showVector(matrixX, N, 'x');
	
#endif

#ifdef LAB_4

	printf("\nGauss solution:\n");
	if(gauss(matrixA, matrixB, matrixX) == EXIT_FAILURE)
	{
		printf("No solutions");
		return EXIT_FAILURE;
	}
	printf("\nSolution:\n");
	showVector(matrixX, N, 'x');
	printf("\nLU solution:\n");
	if(luSolution(matrixA, matrixB, matrixX) == EXIT_FAILURE)
	{
		printf("No solutions");
		return EXIT_FAILURE;
	}
	printf("\nSolution:\n");
	showVector(matrixX, N, 'x');
	
#endif	
	
	return EXIT_SUCCESS;
}

