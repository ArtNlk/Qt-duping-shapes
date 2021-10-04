#ifndef DUPLICATINGSHAPE_H
#define DUPLICATINGSHAPE_H

#include <QObject>
#include <QPoint>
#include <QAbstractItemModel>
#include <qqml.h>

class DuplicatingShape : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QModelIndex index READ getIndex)

    Q_PROPERTY(unsigned int vertexCount READ getVertexCount CONSTANT)

    Q_PROPERTY(unsigned int usRemaining READ getUsRemaining() CONSTANT)

    Q_PROPERTY(unsigned int minVerts READ getMinVerts WRITE setMinVerts)

    Q_PROPERTY(unsigned int maxVerts READ getMaxVerts WRITE setMaxVerts)

    Q_PROPERTY(unsigned int usDefaultLifetime READ getDefaultLifetime WRITE setDefaultLifetime)

public:
    explicit DuplicatingShape(QObject *parent = nullptr,
                              QModelIndex _index = QModelIndex(),
                              unsigned int _vertexCount = minVerts,
                              unsigned int _usLifetime = usDefaultLifetime);

    QModelIndex getIndex();

    unsigned int getVertexCount();

    unsigned int getUsRemaining();

    static unsigned int getMinVerts();
    static unsigned int getMaxVerts();
    static unsigned int getDefaultLifetime();

    static void setMinVerts(unsigned int value);
    static void setMaxVerts(unsigned int value);
    static void setDefaultLifetime(unsigned int value);

public slots:
    void tick();

signals:
    void onDeath(QModelIndex index);

protected:
    static unsigned int minVerts;
    static unsigned int maxVerts;
    static unsigned int usDefaultLifetime;
    unsigned int vertexCount;
    unsigned int usRemaining;
    QModelIndex index;
};

Q_DECLARE_METATYPE(DuplicatingShape*)
#endif // DUPLICATINGSHAPE_H
