#ifndef DUPLICATINGSHAPESMODEL_H
#define DUPLICATINGSHAPESMODEL_H

#include <QAbstractListModel>
#include "duplicatingshape.h"

class DuplicatingShapesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
            VertexCountRole = Qt::UserRole + 1,
            LifetimeRole
        };

    explicit DuplicatingShapesModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

public slots:

    void addShape(unsigned int vertexCount, unsigned int lifespan);

    void deleteAt(QModelIndex index);

    Q_INVOKABLE void tick();

private:
    QVector<DuplicatingShape*> shapes;
};

#endif // DUPLICATINGSHAPESMODEL_H
