/*
 * Filename: mainwindow.h
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMatrix4x4>
#include <QMainWindow>
#include <math.h>
#define N 4
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    enum {K = 0, X1, X2, X3, X4, DELTA, AMOUNT};

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void jacobiMethod(const QMatrix4x4 A, const QVector<double> B);
    void seidelMethod(const QMatrix4x4 A, const QVector<double> B);
    double findMaxDelta(const QVector <double> X, const QVector <double> tempX);
    double eps;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
