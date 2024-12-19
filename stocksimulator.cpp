#include "stocksimulator.h"
#include "ui_stocksimulator.h"
#include "view.h"
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>

StockSimulator::StockSimulator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockSimulator)
{
    ui->setupUi(this);
    this->setWindowTitle("Stock List");
    this->resize(700,700);

    ui->investedLabel->setText(QString("Invested: %1").arg(investedAmount));
    ui->balanceLabel->setText(QString("Balance: %1").arg(balance));

    QVector<Row> v;
    QVector<Row>::iterator it;

    StockSimulator::renderData(&v);

    // Create the model:
    TestModel *stockModel = new TestModel();

    for (auto it = v.begin(); it != v.end(); it++) {
        // Populate model with the data:
        stockModel->populateData(it->stock,it->price);
    }

    // Connect model to the table view:
    ui->tableViewStocks->setModel(stockModel);

    // Set background color for the table header:
    ui->tableViewStocks->setStyleSheet("QHeaderView::section { background-color:orange }");

    // Make the table header visible:
    ui->tableViewStocks->horizontalHeader()->setVisible(true);

    //display the table:
    ui->tableViewStocks->show();

}

StockSimulator::~StockSimulator()
{
    delete ui;
}

void StockSimulator::processTransaction(bool isBuy) {

    QModelIndex currentIndex = ui->tableViewStocks->currentIndex();
    if (!currentIndex.isValid()) {
        qDebug() << "No stock selected.";
        return;
    }

    bool quantityOk;
    int quantity = ui->lineEditQuantity->text().toInt(&quantityOk);
    if (!quantityOk || quantity <= 0) {
        qDebug() << "Invalid quantity.";
        return;
    }

    QAbstractItemModel *tableModel = ui->tableViewStocks->model();
    int row = currentIndex.row();

    QString stockName = tableModel->data(tableModel->index(row, 0)).toString();
    double stockPrice = tableModel->data(tableModel->index(row, 1)).toDouble();

    double transactionAmount = stockPrice * quantity;

    if (isBuy) {
        if (transactionAmount > balance) {
            qDebug() << "Insufficient balance.";
            return;
        }
        investedAmount += transactionAmount;
        balance -= transactionAmount;
    } else {
        if (transactionAmount > investedAmount) {
            qDebug() << "Insufficient invested amount.";
            return;
        }
        investedAmount -= transactionAmount;
        balance += transactionAmount;
    }

    // Update labels
    ui->investedLabel->setText(QString("Invested Amount: %1").arg(investedAmount));
    ui->balanceLabel->setText(QString("Balance: %1").arg(balance));

    qDebug() << (isBuy ? "Bought" : "Sold") << quantity << stockName
             << "for" << transactionAmount;
}


StockSimulator::renderData(QVector<Row> *v)
{
    Row r;

    QMap<QString,QString> stocks = {
        {"IRFC", "200"},
        {"RVNL", "400"},
        {"IREDA","300"}
    };

    // Iterate through the QMap and print each key-value pair
    for (auto it = stocks.begin(); it != stocks.end(); ++it) {
        r.stock = it.key();
        r.price = it.value();

        v->push_back(r);
    }
}

void StockSimulator::on_buyStock_clicked()
{
    processTransaction(true);
}

void StockSimulator::on_sellStock_clicked()
{
    processTransaction(false);
}
