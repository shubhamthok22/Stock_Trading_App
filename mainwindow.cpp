#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMenu>
//#include "view.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
//    delete ptrStockSim;
    delete ui;
}

void MainWindow::on_actionStock_List_triggered()
{
    ptrStockSim = new StockSimulator();
    ptrStockSim->show();
}
