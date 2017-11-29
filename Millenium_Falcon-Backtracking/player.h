#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QObject>
#include <iostream>
#include <string>

#include "astar.h"

using namespace std;

class Player: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    int width, height, factor, xFinal, yFinal;
    string route;
    
    Player(int width, int height, int factor, int xFinal, int yFinal);
    void keyPressEvent(QKeyEvent * event);
    void initialize();
    void chooseMove();

public slots:
    void spawn();
    void move();
    
private:
};

#endif // MYRECT_H
