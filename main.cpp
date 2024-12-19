#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

//    StockSimulator simulator;
//    simulator.setWindowTitle("Stock Market Simulator");
//    simulator.resize(600, 400);
//    simulator.show();

    MainWindow m;
    m.setWindowTitle("Stock Trading App");
    m.resize(700,700);
    m.show();

    return app.exec();
}
