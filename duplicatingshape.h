#ifndef DUPLICATINGSHAPE_H
#define DUPLICATINGSHAPE_H

#include <QObject>
#include <QPoint>
#include <QAbstractItemModel>
#include <qqml.h>

class DuplicatingShape : public QObject
{
    Q_OBJECT

public:
    explicit DuplicatingShape(QObject *parent = nullptr,
                              unsigned int _vertexCount = minVerts,
                              unsigned int _usLifetime = usDefaultLifetime);

    unsigned int getVertexCount();

    unsigned int getUsRemaining();

    static unsigned int getMinVerts();
    static unsigned int getMaxVerts();
    static unsigned int getDefaultLifetime();

    static void setMinVerts(unsigned int value);
    static void setMaxVerts(unsigned int value);
    static void setDefaultLifetime(unsigned int value);

protected:
    static unsigned int minVerts;
    static unsigned int maxVerts;
    static unsigned int usDefaultLifetime;
    unsigned int vertexCount;
    unsigned int usRemaining;
};

Q_DECLARE_METATYPE(DuplicatingShape*)
#endif // DUPLICATINGSHAPE_H
