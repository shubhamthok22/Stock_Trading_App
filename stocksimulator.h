#ifndef STOCKSIMULATOR_H
#define STOCKSIMULATOR_H

#include <QDialog>
#include <QTableView>

namespace Ui {
class StockSimulator;
}

struct Row{
     QString stock;
     QString price;
};

class StockSimulator : public QDialog
{
    Q_OBJECT

public:
    explicit StockSimulator(QWidget *parent = 0);
    ~StockSimulator();

    renderData(QVector<Row> *v);
    void processTransaction(bool isBuy);
//    void onCellClicked(const QModelIndex &index);

private slots:
    void on_buyStock_clicked();
    void on_sellStock_clicked();

private:
    Ui::StockSimulator *ui;

    double investedAmount = 0;
    double balance = 10000;

    QTableView *stockTable;
    QLineEdit *inputQuantity;
};

#endif // STOCKSIMULATOR_H
