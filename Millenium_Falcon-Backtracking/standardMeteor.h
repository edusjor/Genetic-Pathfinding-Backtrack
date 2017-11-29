#ifndef STANDARDMETEOR_H
#define STANDARDMETEOR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>

// 150p, 75p and 25p size

class StandardMeteor: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    int height, width, factor;
    StandardMeteor(int width, int height, int factor);

public slots:
    void move();
};

#endif // STANDARDMETEOR_H
