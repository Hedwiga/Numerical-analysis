/*
 * Filename: mainwindow.h
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGenericMatrix>
#include <QMainWindow>
#include <math.h>
#define N 5
#define M 3
#define V 1
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef QGenericMatrix<M, N, double> MatrixA;
typedef QGenericMatrix<N, M, double> TMatrixA;
typedef QGenericMatrix<V, N, double> VectorB;
typedef QGenericMatrix<V, M, double> VectorX;
typedef QGenericMatrix<M, M, double> SqrMatrix;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    VectorX methodLeastSquares();
    VectorX methodSquareRoot();
    double forward(int i);
    double sumForward(int i, int m);
    double backward(int i);
    double sumBackward(int i, int m);
    void createTriangular();
    double sumSquares(int i, int p);
    double sumIJ(int i, int j, int p);

    // Output functions
    void showStartValues();
    void showMatrixNC();
    void showMatrixLU();
    void showMatrixYX();
    ~MainWindow();

private:
    MatrixA matrixA;
    VectorB matrixB;
    SqrMatrix matrixN;
    SqrMatrix matrixL;
    SqrMatrix matrixU;
    VectorX matrixC;
    VectorX matrixY;
    VectorX matrixX;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
