/*
Filename: constants.h
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H
#define LAB_4
#define N 3
#define VERT_LINE 179

typedef double SqrMatrix [N][N] ;
typedef double Vector [N] ;

void copyMatrix(SqrMatrix destination, const SqrMatrix source);

#ifdef LAB_3

int cramersRule(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX);
int matrixSolution(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX);
double determinantOfMatrix(const SqrMatrix matrix, int n);
void getMinor(SqrMatrix destination, const SqrMatrix source, int p, int q, int n);
void fillColumn(SqrMatrix matrix, const Vector vector, int col);
void copyMatrix(SqrMatrix destination, const SqrMatrix source);
void copyVector(Vector destination, const Vector source, int n);
int invertMatrix(SqrMatrix destination, const SqrMatrix source);
void multiplyMatrixByVector(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX);
void transposeMatrix(SqrMatrix destination, const SqrMatrix source);
void multiplyMatrixByNumber(SqrMatrix matrix, double number);

#endif


#ifdef LAB_4

typedef double AugmentedMatrix [N][N + 1];
int defineMainRow(const AugmentedMatrix matrix, int col);
int gauss(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX);
int forwardGauss(AugmentedMatrix matrix, int col);
double backwardGauss(const AugmentedMatrix matrix, Vector matrixX, int i);
int transformMatrix(AugmentedMatrix matrix, int mainRow);
void createAugmentedMatrix(AugmentedMatrix destination, const SqrMatrix matrixA, const Vector matrixB);
void swapRows(AugmentedMatrix matrix, int row1, int row2);
double sumBackward(const AugmentedMatrix matrix, Vector X, int i, int k);

int luSolution(const SqrMatrix matrixA, const Vector matrixB, Vector matrixX);
void luDecomposition(const SqrMatrix matrixA, SqrMatrix L, SqrMatrix U);
double forwardLU(const SqrMatrix L, const Vector B, Vector Y, int i);
double sumForwardLU(const SqrMatrix L, const Vector B, Vector Y, int i, int m);
double backwardLU(const SqrMatrix U, const Vector Y, Vector X, int i);
double sumBackwardLU(const SqrMatrix U, const Vector Y, Vector X, int i, int m);

#endif

// Output functions
void showAugmentedMatrix(const AugmentedMatrix matrix);
void showMatrix(const SqrMatrix matrix, int n);
void showMinor(const SqrMatrix, int n);
void showVector(const Vector vector, int n, char name);
void showEquations(const SqrMatrix matrixA, const Vector matrixB);

#endif
