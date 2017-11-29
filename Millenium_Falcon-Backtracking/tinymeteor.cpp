#include "bigmeteor.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <stdlib.h>

#include "enemy.h"
#include "player.h"
#include "astar.h"

TinyMeteor::TinyMeteor(int width, int height, int factor)
{
    this->width = width;
    this->height = height;
    this->factor = factor;
    this->setBrush(Qt::gray);

    // draw the meteor
    setRect(0,0,factor, factor); //factor wide & tall

    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    int speed = rand() % 2 + 1;
    if (speed == 1){
        speed = 1000;
    } else if (speed == 2) {
        speed = 750;
    }
    timer->start(speed);
}

void TinyMeteor::move()
{
    //Clean A* matrix
    int size = this->rect().width()/10 + 2;
    int i2 = this->x()/10 - 1;
    int j2 = this->y()/10 - 1;
    int j1 = j2;

    for(int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){

            AStar::Amap[i2][j2]=0;
            j2++;
        }
        i2++;
        j2=j1;
    }

    // if meteor or player collides with him, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i<n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player) ||
                typeid(*(colliding_items[i])) == typeid(TinyMeteor) ||
                typeid(*(colliding_items[i])) == typeid(Enemy)){
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        } else if (typeid(*(colliding_items[i])) == typeid(BigMeteor)){
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // move meteor down
    setPos(x(), y()+factor);

    // delete the meteor when is off the screen
    if (pos().y() > this->height){
        scene()->removeItem(this);
        delete this;
        return;
    }

    //Block A* matrix
    i2 = this->x()/10 - 1;
    j2 = this->y()/10 - 1;
    j1 = j2;

    for(int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){

            AStar::Amap[i2][j2]=1;
            j2++;
        }
        i2++;
        j2=j1;
    }
}

