/*
 * Filename: mainwindow.h
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interpolation.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    enum {Nodes = 10, Lagrange = 10, Newtons = 11};
    Ui::MainWindow *ui;
    Interpolation::TableFunction tableFunction;
    Interpolation::Point solution;
    void readFunction();
    void readX();
    Interpolation::Point readFromTable(int row);
    void showLagrange() const;
    void showNewtons() const;
    void showSolution(int row) const;
};
#endif // MAINWINDOW_H
