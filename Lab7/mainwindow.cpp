/*
 * Filename: mainwindow.cpp
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Equations equations(-0.9, 0.5, 0.003, ui->iteration);
    equations.methodIterations();
    equations.changeResultTable(ui->newton);
    equations.methodNewtons();
}

MainWindow::~MainWindow() {
    delete ui;
}
