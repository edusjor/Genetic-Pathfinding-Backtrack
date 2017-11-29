#ifndef TINYMETEOR_H
#define TINYMETEOR_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>

// 150p, 75p and 25p size

class TinyMeteor: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    int height, width, factor;
    TinyMeteor(int width, int height, int factor);

public slots:
    void destroy();
};

#endif // TINYMETEOR_H
