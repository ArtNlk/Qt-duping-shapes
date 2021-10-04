#include "duplicatingshapesmodel.h"

DuplicatingShapesModel::DuplicatingShapesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant DuplicatingShapesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant(tr("Duplicating Shapes"));
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

    default:
        qDebug() << "DuplicatingShapesModel Attempt to get unknown role: " << role;
        throw std::invalid_argument("DuplicatingShapesModel Attempt to get unknown role");
    }
}

QHash<int, QByteArray> DuplicatingShapesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
        roles[VertexCountRole] = "vertexCount";
        roles[LifetimeRole] = "lifetime";

        return roles;
}

void DuplicatingShapesModel::addShape(unsigned int vertexCount, unsigned int lifetime)
{
    DuplicatingShape* newShape = new DuplicatingShape(nullptr,index(shapes.size(),0),vertexCount,lifetime);
    beginInsertRows(QModelIndex(),shapes.size(),shapes.size());
    shapes.append(newShape);
    endInsertRows();
}

void DuplicatingShapesModel::deleteAt(QModelIndex index)
{
    if(index.row() >= shapes.size())
    {
        qDebug() << "DuplicatingShapesModel attempt to delete shape at invalid index: " << index.row();
        throw std::invalid_argument("DuplicatingShapesModel attempt to delete shape at invalid index");
    }
    shapes.takeAt(index.row())->deleteLater();
}

void DuplicatingShapesModel::tick()
{
    qDebug() << "DuplicatingShapesModel: tick!";
    for(DuplicatingShape* shape : shapes)
    {
        shape->tick();
    }
    qDebug() << "Changed from: " << index(0) << " to " <<index(shapes.size()-1);
    emit dataChanged(index(0),index(shapes.size()-1));
}
