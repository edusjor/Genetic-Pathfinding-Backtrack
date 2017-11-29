#include "bigmeteor.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <stdlib.h>

#include "player.h"

StandardMeteor::StandardMeteor(int width, int height, int factor)
{
    this->width = width;
    this->height = height;
    this->factor = factor;

    // draw the meteor
    setRect(0,0,2*factor, 2*factor); //2*factor wide & tall

    this->setBrush(Qt::gray);

    // connect
    QTimer * timer = new QTimer();

    timer->singleShot(200,this,SLOT(destroy()));
    timer->start();
}

void StandardMeteor::destroy()
{
    // if meteor or player collides with him, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i<n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(TinyMeteor)) {
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
}
