#include "bigmeteor.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <stdlib.h>

#include "player.h"

TinyMeteor::TinyMeteor(int width, int height, int factor)
{
    this->width = width;
    this->height = height;
    this->factor = factor;

    // draw the meteor
    setRect(0,0,factor, factor); //factor wide & tall

    this->setBrush(Qt::gray);

    // connect
    QTimer * timer = new QTimer();

    timer->singleShot(200,this,SLOT(destroy()));
    timer->start();
}

void TinyMeteor::destroy()
{
    // if meteor or player collides with him, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i<n; ++i){
          if (typeid(*(colliding_items[i])) == typeid(BigMeteor)){
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
