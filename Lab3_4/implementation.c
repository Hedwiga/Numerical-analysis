/*
Filename: implementation.c
*/

#include <stdlib.h>
#include <math.h>
#include "constants.h"
#define LAB_4

void copyMatrix(SqrMatrix destination, const SqrMatrix source)
{
	for(int row = 0; row < N; ++row)
		for(int col = 0; col < N; ++col)
			destination[row][col] = source[row][col];
}

#ifdef LAB_3

int matrixSolution(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX)
{
	SqrMatrix matrixInv = {0.0};
	printf("\nInvertion of matrix:\n");
	if(invertMatrix(matrixInv, matrixA) == EXIT_FAILURE)
		return EXIT_FAILURE;
	printf("\nInvertedMatrix : \n");
	showMatrix(matrixInv, N);
	printf("\nX = Inv A * B\n");
	showMatrix(matrixInv, N);
	printf("Multiply by\n");
	showVector(matrixB, N, 'b');
	multiplyMatrixByVector(matrixInv, matrixB, matrixX);
	
	return EXIT_SUCCESS;
}
int invertMatrix(SqrMatrix destination, const SqrMatrix source)
{
	double detA = determinantOfMatrix(source, N);
	SqrMatrix det = {0.0};
	printf("\ndetA = %-+.2lf\n", detA);
	if(detA == 0.0)
		return EXIT_FAILURE;
	int sign = 0;
	SqrMatrix cofactor = {0.0};
	SqrMatrix temp = {0.0};
	for(int row = 0; row < N; ++row)
	{
		for(int col = 0; col < N; ++col)
		{
			sign = pow(-1, row + col + 2);
			getMinor(temp, source, row, col, N);
			printf("Minor M%d,%d:\n", row, col);
			showMinor(temp, N);
			det[row][col] =  determinantOfMatrix(temp, N - 1);
			cofactor[row][col] =  sign * det[row][col];	
			printf("\nCofactor A%d,%d = %d * %-+.2lf = %-+.2lf\n", row, col, sign, det[row][col], cofactor[row][col]);
		}
	}
	printf("\nInv A = %-+.2lf * Transposed A\n", 1 / detA);
	printf("Transposed matrix A: \n");
	transposeMatrix(destination, cofactor);
	showMatrix(destination, N);
	multiplyMatrixByNumber(destination, 1 / detA);
	return EXIT_SUCCESS;
}

int cramersRule(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX)
{
	double detA = determinantOfMatrix(matrixA, N);
	printf("\ndetA = %-+.2lf\n", detA);
	if(detA == 0.0)
		return EXIT_FAILURE;
	Vector det = {0.0};
	SqrMatrix matrixTemp = {0.0};
	
	for(int i = 0; i < N; ++i)
	{
		copyMatrix(matrixTemp, matrixA);
		fillColumn(matrixTemp, matrixB, i);
		det[i] = determinantOfMatrix(matrixTemp, N);
		printf("\nMatrix%d = \n", i);
		showMatrix(matrixTemp, N);
		printf("det%d = %-+.2lf\n", i, det[i]);
		matrixX[i] = det[i]/detA;
		printf("x%d = det%d / detA  = %-+.2lf /  %-+.2lf;\n", i, i, det[i], detA);
		printf("x%d = %-+.2lf;\n", i, matrixX[i]);
	}
	return EXIT_SUCCESS;
}

void getMinor(SqrMatrix destination, const SqrMatrix source, int p, int q, int n)
{ 
    int i = 0, j = 0; 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            if (row != p && col != q) 
            { 
                destination[i][j++] = source[row][col]; 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
double determinantOfMatrix(const SqrMatrix matrix, int n)
{ 
   	double det = 0; 
    if (n == 1) 
        return matrix[0][0]; 
    SqrMatrix temp; 
    int sign = 1;  
    for (int f = 0; f < n; f++) 
    {  
        getMinor(temp, matrix, 0, f, n);
        det += sign * matrix[0][f] * determinantOfMatrix(temp, n - 1); 
        sign = -sign; 
    } 
  
    return det; 
} 
void fillColumn(SqrMatrix matrix, const Vector vector, int col)
{
	for(int row = 0; row < N; ++row)
		matrix[row][col] = vector[row];
	
}

void transposeMatrix(SqrMatrix destination, const SqrMatrix source)
{
	for(int row = 0; row < N; ++row)
	{
		for(int col = 0; col < N; ++col)
			destination[row][col] = source[col][row];
	}
}
void multiplyMatrixByNumber(SqrMatrix matrix, double number)
{
	for(int row = 0; row < N; ++row)
		for(int col = 0 ; col < N; ++col)
			matrix[row][col] *= number;
}
void multiplyMatrixByVector(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX)
{
	for(int row = 0; row < N; ++row)
	{
		matrixX[row] = 0;
		for(int col = 0; col < N; ++col)
			matrixX[row] += matrixA[row][col] * matrixB[col];  	
			
	}
}
#endif

#ifdef LAB_4
int gauss(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX)
{
	AugmentedMatrix matrix = {0.0};
	double mainEl = 0.0;
	createAugmentedMatrix(matrix, matrixA, matrixB);
	printf("Forward step:\n");
	if(forwardGauss(matrix, 0) == EXIT_FAILURE)
		return EXIT_FAILURE;
	backwardGauss(matrix, matrixX, 0);
	return EXIT_SUCCESS;
}
int forwardGauss(AugmentedMatrix matrix, int mainCol)
{
	showAugmentedMatrix(matrix);
	if(mainCol == N - 1)
		return EXIT_SUCCESS;
	int mainRow = defineMainRow(matrix, mainCol);
	if(mainCol != mainRow)
		swapRows(matrix, mainRow, mainCol);
	mainRow = mainCol;
	if(transformMatrix(matrix, mainRow) == EXIT_FAILURE)
		return EXIT_FAILURE;
	forwardGauss(matrix, mainCol + 1);
}
double backwardGauss(const AugmentedMatrix matrix, Vector matrixX, int i)
{
	if(i == N - 1)
		return matrixX[i] = matrix[i][N] / matrix[i][i];
	return matrixX[i] = (1 / matrix[i][i]) * (matrix[i][N] - sumBackward(matrix, matrixX, i, i + 1));	
}
double sumBackward(const AugmentedMatrix matrix, Vector matrixX, int i, int k)
{	
	if(k == N - 1)
		return matrix[i][k] * backwardGauss(matrix, matrixX, k);
	return matrix[i][k] * backwardGauss(matrix, matrixX, k) + sumBackward(matrix, matrixX, i, k + 1);
}
int defineMainRow(const AugmentedMatrix matrix, int col)
{
	double maxElement = fabs(matrix[0][col]);
	double curElement = maxElement;
	int maxRow = col;
	for(int row = 0; row < N; ++row)
	{
		curElement = fabs(matrix[row][col]);
		if(curElement > maxElement)
		{
			maxElement = curElement;
			maxRow = row;
		}
	}
	return maxRow;
}
void createAugmentedMatrix(AugmentedMatrix destination, const SqrMatrix matrixA, const Vector matrixB)
{
	for(int row = 0; row < N; ++row)
		for(int col = 0; col < N + 1; ++col)
			if(col == N)
				destination[row][col] = matrixB[row];
			else	
				destination[row][col] = matrixA[row][col];

}
void swapRows(AugmentedMatrix matrix, int row1, int row2)
{
	double temp[N + 1] = {0.0};
	for(int col = 0; col < N + 1; ++col)
	{
		temp[col] = matrix[row1][col];
		matrix[row1][col] = matrix[row2][col];
		matrix[row2][col] = temp[col];
	}

}
int transformMatrix(AugmentedMatrix matrix, int mainRow)
{
	int mainCol = mainRow;
	if(matrix[mainRow][mainCol] == 0)
		return EXIT_FAILURE;
	for(int row = mainRow + 1; row < N; ++row)
	{
		double mainNumber = matrix[row][mainCol] / matrix[mainRow][mainCol];
		for(int col = mainCol; col < N + 1; ++col)
			matrix[row][col] = matrix[mainRow][col] * mainNumber - matrix[row][col];
	}
	return EXIT_SUCCESS;
}
int luSolution(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX)
{
	SqrMatrix L = {0.0};
	SqrMatrix U = {0.0};
	luDecomposition(matrixA, L, U);
	printf("L matrix: \n");
	showMatrix(L, N);
	printf("U matrix: \n");
	showMatrix(U, N);
	Vector Y = {0.0};
	forwardLU(L, matrixB, Y, N - 1);
	backwardLU(U, Y, matrixX, 0);
	return EXIT_SUCCESS;
}
void luDecomposition(const SqrMatrix matrixA, SqrMatrix L, SqrMatrix U)
{
	copyMatrix(U, matrixA);
	for(int i = 0; i < N; ++i)
		for(int j = i; j < N; ++j)
			L[j][i] = U[j][i]/U[i][i];
	for(int k = 1; k < N; ++k)
	{
		for(int i = k - 1; i < N; ++i)
			for(int j = i; j < N; ++j)
				L[j][i] = U[j][i]/U[i][i];
		
		for(int i = k; i < N; ++i)
			for(int j = k - 1; j < N; ++j)
				U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];		
	}
}
double forwardLU(const SqrMatrix L, const Vector B, Vector Y, int i)
{
	if(i == 0)
		return Y[i] = B[i];
	return Y[i] = B[i] - sumForwardLU(L, B, Y, i, 0);
}
double sumForwardLU(const SqrMatrix L, const Vector B, Vector Y, int i, int m)
{
	if(m == i - 1)
		return L[i][m] * forwardLU(L, B, Y, m);
	return L[i][m] * forwardLU(L, B, Y, m) + sumForwardLU(L, B, Y, i, m + 1);
}
double backwardLU(const SqrMatrix U, const Vector Y, Vector X, int i)
{
	if(i == N - 1)
		return X[i] = Y[i]/U[i][i];
	return X[i] = (1/U[i][i]) * (Y[i] - sumBackwardLU(U, Y, X, i, i + 1));
}
double sumBackwardLU(const SqrMatrix U, const Vector Y, Vector X, int i, int m)
{
	if(m == N - 1)
		return U[i][m] * backwardLU(U, Y, X, m);
	return U[i][m] * backwardLU(U, Y, X, m) + sumBackwardLU(U, Y, X, i, m + 1);
}

#endif

// Output functions
void showAugmentedMatrix(const AugmentedMatrix matrix)
{
	printf("\n");
	for(int row = 0; row < N; ++row)
	{
		printf("%c ", VERT_LINE);
		for(int col = 0; col < N + 1; ++col)
		{
			if(col == N)
				printf("%c ", VERT_LINE);
			printf("%-+.2lf ", matrix[row][col]);
		}
			
		printf("%c", VERT_LINE);
		printf("\n");
	}	
}
void showVector(const Vector vector, int n, char name)
{
	for(int i = 0; i < n; ++i)
		printf("%c%d = %lf\n", name, i, vector[i]);

}
void showMatrix(const SqrMatrix matrix, int n)
{
	for(int row = 0; row < n; ++row)
	{
		printf("%c ", VERT_LINE);
		for(int col = 0; col < n; ++col)
			printf("%-+.2lf ", matrix[row][col]);
		printf("%c", VERT_LINE);
		printf("\n");
	}
}
void showMinor(const SqrMatrix matrix, int n)
{
	for(int row = 0; row < n; ++row)
	{
		if(n - row > 1)
			printf("%c ", VERT_LINE);
		for(int col = 0; col < n; ++col)
			if(matrix[row][col])
				printf("%-+.2lf ", matrix[row][col]);
		if(n - row > 1)
		printf("%c", VERT_LINE);
		printf("\n");
	}
}
void showEquations(const SqrMatrix matrixA, const Vector matrixB)
{
	for(int row = 0; row < N; ++row)
		printf("%-+.2lfx0 %-+.2lfx1 %-+.2lfx2 = %-+.2lf\n", matrixA[row][0], matrixA[row][1], matrixA[row][2], matrixB[row]);
}
