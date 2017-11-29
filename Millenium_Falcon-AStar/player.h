#ifndef MYRECT_H
#define MYRECT_H

#include <QList>
#include <QGraphicsRectItem>
#include <QObject>
#include <iostream>
#include <string>
#include <QTimer>

#include "node.h"

using namespace std;

class Player: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    int width, height, factor, xFinal, yFinal, stepCounter = 0;
    static string steps;
    static QList<QGraphicsItem *> colliding_items;
    static QTimer *timer;
    static std::list<Node*> movementList;
    static int lastMovement;
    
    Player(int width, int height, int factor);
    void keyPressEvent(QKeyEvent * event);
    void initialize();
    bool verifyCollides();
    void goBack();
    void move(bool repeat);

public slots:
    void moveSlot();
    
private:
};

#endif // MYRECT_H
