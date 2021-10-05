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
            LifetimeRole,
            DefaultLifetimeRole
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

    Q_INVOKABLE void deleteAt(int index);

    Q_INVOKABLE void spawn(int n);

    Q_INVOKABLE int getDefaultShapeLifetime();
private:
    QVector<DuplicatingShape*> shapes;
};

#endif // DUPLICATINGSHAPESMODEL_H
