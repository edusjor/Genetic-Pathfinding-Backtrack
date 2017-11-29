#include "bigmeteor.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <stdlib.h>

#include "player.h"

BigMeteor::BigMeteor(int width, int height,int factor)
{
    this->width = width;
    this->height = height;
    this->factor = factor;

    // draw the meteor
    setRect(0,0,3*factor, 3*factor); //40p wide, 40p tall

    this->setBrush(Qt::gray);

    // connect
    QTimer * timer = new QTimer();

    timer->singleShot(200,this,SLOT(destroy()));
    timer->start();
}

void BigMeteor::destroy()
{
    // if meteor or player collides with him, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i<n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(BigMeteor) ||
                   typeid(*(colliding_items[i])) == typeid(StandardMeteor)) {
            int y = this->y();
            int x = this->x();
            QGraphicsScene * oldScene = this->scene();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // set position
            StandardMeteor * newMeteor1 = new StandardMeteor(this->width, this->height, this->factor);
            StandardMeteor * newMeteor2 = new StandardMeteor(this->width, this->height, this->factor);

            newMeteor1->setPos(x-2*factor, y);
            newMeteor2->setPos(x+2*factor, y+2*factor);

            oldScene->addItem(newMeteor1);
            oldScene->addItem(newMeteor2);

            delete colliding_items[i];
            delete this;
            return;
        }
    }
}
