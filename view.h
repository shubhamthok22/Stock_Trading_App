#ifndef VIEW_H
#define VIEW_H

#include <QAbstractTableModel>

class TestModel : public QAbstractTableModel
{
   Q_OBJECT

public:
   TestModel(QObject *parent = 0);

   void populateData(const QString &stock, const QString &price);

   int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
   int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
   QVector<QString> stockName;
   QVector<QString> stockPrice;

};

#endif // VIEW_H
