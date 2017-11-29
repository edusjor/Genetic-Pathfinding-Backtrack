#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>

#include "standardMeteor.h"
#include "bigmeteor.h"
#include "tinymeteor.h"
#include "player.h"
#include "astar.h"
#include "enemy.h"

const int factor = 50;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const int width = 20*factor;
    const int height = 18 * factor;

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    Player * player = new Player(width, height, factor,2*factor,height/2);

    // add the item to the scene
    scene->addItem(player);

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add a view
    QGraphicsView * view = new QGraphicsView(scene);

    Enemy * enemy1 = new Enemy(width, height, factor,player);
    Enemy * enemy2 = new Enemy(width, height, factor,player);
    enemy1->setPos(18*factor,9*factor - 4*factor);
    enemy2->setPos(18*factor,9*factor + 3*factor);
    scene->addItem(enemy1);
    scene->addItem(enemy2);
    enemy1->initialize();
    enemy2->initialize();

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // show the view
    view->show();
    view->setFixedSize(width,height); // width and height
    scene->setSceneRect(0,0,width,height);

    player->setPos(17*factor,9*factor - factor/2);

    // spawn meteorites
    player->initialize();

    QTimer * timerSpawn = new QTimer();
    QObject::connect(timerSpawn,SIGNAL(timeout()),player,SLOT(spawn()));

    timerSpawn->start(1000);

    scene->setBackgroundBrush(Qt::black);

    return a.exec();
}
