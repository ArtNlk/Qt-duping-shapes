#ifndef DUPLICATINGSHAPE_H
#define DUPLICATINGSHAPE_H

#include <QObject>
#include <QPoint>
#include <QAbstractItemModel>

class DuplicatingShape : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QModelIndex index READ getIndex)

    Q_PROPERTY(unsigned int vertexCount READ getVertexCount)

    Q_PROPERTY(unsigned int usRemaining READ getUsRemaining())

    Q_PROPERTY(unsigned int minVerts READ getMinVerts WRITE setMinVerts)

    Q_PROPERTY(unsigned int maxVerts READ getMaxVerts WRITE setMaxVerts)

public:
    explicit DuplicatingShape(QObject *parent = nullptr,
                              QModelIndex _index = QModelIndex(),
                              unsigned int _usLifetime = 5000,
                              unsigned int _vertexCount = 3);

    QModelIndex getIndex();

    unsigned int getVertexCount();

    unsigned int getUsRemaining();

    static unsigned int getMinVerts();

    static unsigned int getMaxVerts();

    static void setMinVerts(unsigned int value);
    static void setMaxVerts(unsigned int value);

public slots:
    void tick();

signals:
    void onDeath(QModelIndex index);

protected:
    static unsigned int minVerts;
    static unsigned int maxVerts;
    unsigned int vertexCount;
    unsigned int usRemaining;
    QModelIndex index;
};

Q_DECLARE_METATYPE(DuplicatingShape*)
#endif // DUPLICATINGSHAPE_H
