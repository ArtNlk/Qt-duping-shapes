#ifndef DUPLICATINGSHAPESMODEL_H
#define DUPLICATINGSHAPESMODEL_H

#include <QAbstractListModel>
#include "duplicatingshape.h"

class DuplicatingShapesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DuplicatingShapesModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void deleteAt(const QModelIndex index);

    void spawnShapes();

private:
    QVector<DuplicatingShape*> shapes;
};

#endif // DUPLICATINGSHAPESMODEL_H
