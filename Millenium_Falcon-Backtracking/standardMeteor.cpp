#include "bigmeteor.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <stdlib.h>

#include "player.h"
#include "enemy.h"

StandardMeteor::StandardMeteor(int width, int height, int factor)
{
    this->width = width;
    this->height = height;
    this->factor = factor;
    this->setBrush(Qt::gray);

    // draw the meteor
    setRect(0,0,2*factor, 2*factor); //2*factor wide & tall

    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    int speed;
    if ((rand()%4) == 0){
        speed = 750;
    } else {
        speed = 1000;
    }

    timer->start(speed);
}

void StandardMeteor::move()
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
                typeid(*(colliding_items[i])) == typeid(Enemy)){
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        } else if (typeid(*(colliding_items[i])) == typeid(StandardMeteor) ||
                   typeid(*(colliding_items[i])) == typeid(TinyMeteor)) {
            int y = this->y();
            int x = this->x();
            QGraphicsScene * oldScene = this->scene();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // set position
            TinyMeteor * newMeteor1 = new TinyMeteor(this->width, this->height, this->factor);
            TinyMeteor * newMeteor2 = new TinyMeteor(this->width, this->height, this->factor);

            newMeteor1->setPos(x-factor, y);
            newMeteor2->setPos(x+factor, y+factor);

            oldScene->addItem(newMeteor1);
            oldScene->addItem(newMeteor2);

            delete colliding_items[i];
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
