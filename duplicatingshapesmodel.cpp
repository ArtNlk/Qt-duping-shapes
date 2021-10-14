#include "duplicatingshapesmodel.h"

#include <QRandomGenerator>
#include <QDebug>

DuplicatingShapesModel::DuplicatingShapesModel(QObject *parent)
    : QAbstractListModel(parent),
      initialSpawnCount(3)
{
}

DuplicatingShapesModel::~DuplicatingShapesModel()
{
    while(!shapes.isEmpty())
    {
        deleteAt(0);
    }
}

QVariant DuplicatingShapesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant(tr("Множащиеся числа"));
}

int DuplicatingShapesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return shapes.size();
}

QVariant DuplicatingShapesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
    case(VertexCountRole):
        return QVariant::fromValue(shapes.at(index.row())->getVertexCount());
        break;

    case (LifetimeRole):
        return QVariant::fromValue(shapes.at(index.row())->getUsRemaining());
        break;

    case (DefaultLifetimeRole):
        return QVariant::fromValue(DuplicatingShape::getDefaultLifetime());
        break;

    default:
        qDebug() << "DuplicatingShapesModel Attempt to get unknown role: " << role;
        throw std::invalid_argument("DuplicatingShapesModel Attempt to get unknown role");
    }
}

QHash<int, QByteArray> DuplicatingShapesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
        roles[VertexCountRole] = "vertexCount";
        roles[DefaultLifetimeRole] = "defaultLifetime";

        return roles;
}

void DuplicatingShapesModel::addShape(unsigned int vertexCount, unsigned int lifetime)
{
    DuplicatingShape* newShape = new DuplicatingShape(nullptr,vertexCount,lifetime);
    beginInsertRows(QModelIndex(),shapes.size(),shapes.size());
    shapes.append(newShape);
    endInsertRows();
}

void DuplicatingShapesModel::deleteAt(int index)
{
    if(index >= shapes.size())
    {
        qDebug() << "DuplicatingShapesModel attempt to delete shape at invalid index: " << index;
        throw std::invalid_argument("DuplicatingShapesModel attempt to delete shape at invalid index");
    }
    beginRemoveRows(QModelIndex(),index,index);
    shapes.takeAt(index)->deleteLater();
    endRemoveRows();
}

void DuplicatingShapesModel::reset()
{
    while(!shapes.empty())
    {
        deleteAt(0);
    }

    spawn(initialSpawnCount);
}

void DuplicatingShapesModel::spawn(int n)
{
    int minSides = DuplicatingShape::getMinVerts();
    int maxSides = DuplicatingShape::getMaxVerts();
    if(minSides == maxSides)//Fix bounded random assert failure if min==max
    {
        for(int i = 0; i < n; i++)
        {
            addShape(minSides,DuplicatingShape::getDefaultLifetime());
        }
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            addShape(QRandomGenerator::global()->bounded(minSides,maxSides),DuplicatingShape::getDefaultLifetime());
        }
    }
}

int DuplicatingShapesModel::getDefaultShapeLifetime()
{
    return DuplicatingShape::getDefaultLifetime();
}

void DuplicatingShapesModel::changeSettings(int initialCount, int sidesMin, int sidesMax, int lifespan)
{
    initialSpawnCount = initialCount;
    DuplicatingShape::setMinVerts(sidesMin);
    DuplicatingShape::setMaxVerts(sidesMax);
    DuplicatingShape::setDefaultLifetime(lifespan);
}
