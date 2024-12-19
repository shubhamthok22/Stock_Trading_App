#include "view.h"

TestModel::TestModel(QObject *parent) : QAbstractTableModel(parent)
{
}

// Create a method to populate the model with data:
void TestModel::populateData(const QString &stock, const QString &price)
{
//      stockName.clear();
      stockName.push_back(stock);
//      stockPrice.clear();
      stockPrice.push_back(price);

    return;
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return stockName.size();
}

int TestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return stockName[index.row()];
    }else if (index.column() == 1) {
        return stockPrice[index.row()];
    }
    return QVariant();
}

QVariant TestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Stock");
        } else if (section == 1) {
            return QString("Price");
        }
    }
    return QVariant();
}
