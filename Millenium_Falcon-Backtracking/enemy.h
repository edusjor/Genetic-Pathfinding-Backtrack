#ifndef ENEMY_H
#define ENEMY_H


#include <QGraphicsRectItem>
#include <QObject>
#include <iostream>
#include <string>

#include "astar.h"
#include "player.h"

using namespace std;

class Enemy: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    int width, height, factor, xFinal, yFinal;
    string route;
    Player * player;

    Enemy(int width, int height, int factor, Player *player);
    void initialize();
    void chooseMove();

public slots:
    void move();

private:
};

#endif // ENEMY_H
