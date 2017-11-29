#ifndef BIGMETEOR_H
#define BIGMETEOR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>

// 150p, 75p and 25p size

class BigMeteor: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    int height, width, factor;
    BigMeteor(int width, int height, int factor);

public slots:
    void move();
};

#endif // BIGMETEOR_H
