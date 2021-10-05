#include "duplicatingshape.h"
#include <QDebug>
#include <stdexcept>

unsigned int DuplicatingShape::minVerts = 3;
unsigned int DuplicatingShape::maxVerts = 3;
unsigned int DuplicatingShape::usDefaultLifetime = 1000;

DuplicatingShape::DuplicatingShape(QObject *parent, unsigned int _vertexCount, unsigned int _usLifetime) :
    QObject(parent)
{
    if(_usLifetime == 0 || _vertexCount == 0 || _vertexCount < minVerts || _vertexCount > maxVerts)
    {
        qDebug() << "Invalid DuplicatingShape creation: lifetime: "
                 << _usLifetime
                 << " vertex count: "
                 << _vertexCount;
        throw std::invalid_argument("Invalid DuplicatingShape creation");
    }
    usRemaining = _usLifetime;
    vertexCount = _vertexCount;
}

unsigned int DuplicatingShape::getVertexCount()
{
    return vertexCount;
}

unsigned int DuplicatingShape::getUsRemaining()
{
    return usRemaining;
}

unsigned int DuplicatingShape::getDefaultLifetime()
{
    return usDefaultLifetime;
}

unsigned int DuplicatingShape::getMaxVerts()
{
    return maxVerts;
}

void DuplicatingShape::setMinVerts(unsigned int value)
{
    if(value < 3)
    {
        qDebug() << "DuplicatingShape attempt to set bad minVerts value: " << value;
        throw std::invalid_argument("DuplicatingShape attempt to set bad minVerts value: ");
    }

    minVerts = value;
}

void DuplicatingShape::setMaxVerts(unsigned int value)
{
    if(value < 3 || value < minVerts)
    {
        qDebug() << "DuplicatingShape attempt to set bad maxVerts value: " << value << "while minVerts value is: " << minVerts;
        throw std::invalid_argument("DuplicatingShape attempt to set bad maxVerts value: ");
    }

    maxVerts = value;
}

void DuplicatingShape::setDefaultLifetime(unsigned int usValue)
{
    usDefaultLifetime = usValue;
}

unsigned int DuplicatingShape::getMinVerts()
{
    return minVerts;
}

