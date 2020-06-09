/*
 * Filename: mianwindow.h
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <math.h>

#include "integration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_calculate_clicked();

private:
    double a;
    double b;
    double eps;
    IntegrationResult riemannLeft, riemannRight, riemannMidpoint, simpson, trapezoidal;

    bool readValues();
    void readIntervalsAndEps();
    void integrateByMethods();
    IntegrationResult integrateBy(Methods method);

    void writeResults();
    void writeRiemann();
    void writeSimpson();
    void writeTrapezoidal();

    void writeInTable(IntegrationResult, QTableWidget * table);
    void writeInLine(double data, QLineEdit * line);
    QTableWidgetItem * createItem(double data);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
