#include "duplicatingshape.h"
#include <QDebug>
#include <stdexcept>

DuplicatingShape::DuplicatingShape(QObject *parent, QModelIndex _index, unsigned int _usLifetime, unsigned int _vertexCount) :
    QObject(parent),
    index(_index)
{
    if(_usLifetime == 0 || _vertexCount == 0)
    {
        qDebug() << "Invalid DuplicatingShape creation: lifetime: "
                 << _usLifetime
                 << " vertex count: "
                 << _vertexCount
                 << "item index: "
                 << _index.row();
        throw std::invalid_argument("Invalid DuplicatingShape creation");
    }
    usRemaining = _usLifetime;
    vertexCount = _vertexCount;
}

QModelIndex DuplicatingShape::getIndex()
{
    return index;
}

unsigned int DuplicatingShape::getVertexCount()
{
    return vertexCount;
}

unsigned int DuplicatingShape::getUsRemaining()
{
    return usRemaining;
}

void DuplicatingShape::tick()
{
    if(usRemaining == 0)
    {
        emit onDeath(index);
    }
    usRemaining--;
}

unsigned int DuplicatingShape::getMaxVerts()
{
    return maxVerts;
}

unsigned int DuplicatingShape::getMinVerts()
{
    return minVerts;
}

