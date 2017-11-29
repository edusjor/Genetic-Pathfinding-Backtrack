#include "enemy.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include "bigmeteor.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

Enemy::Enemy(int width, int height, int factor, Player *player)
{
    this->width = width;
    this->height = height;
    this->factor = factor;
    this->player = player;
    setRect(0,0,factor/2,factor/2);
    this->setBrush(Qt::red);
}

void Enemy::move()
{
    // if meteor or player collides with him, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i<n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy) ||
                typeid(*(colliding_items[i])) == typeid(Player)){
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    int x = this->x()/10;
    int y = this->y()/10;
    int xtarget;
    int ytarget;
    try {
        xtarget = player->x()/10;
        ytarget = player->y()/10;
    } catch (...){
        xtarget = 18*factor/10;
        ytarget = this->scene()->height()/20;
    }

    if(AStar::Amap[x][y-1] == 1){ //Arriba hay algo
        const char * run = "1";
        this->route.insert(0, run);
        chooseMove();
    } else if (AStar::Amap[x-1][y] == 1) { //Izquierda hay algo
        const char * run = "0";
        this->route.insert(0, run);
        chooseMove();
    } else if (AStar::Amap[x+1][y] == 1) { //Derecha hay algo
        const char * run = "2";
        this->route.insert(0, run);
        chooseMove();
    } else if (AStar::Amap[x][y+1] == 1) { //Abajo hay algo
        const char * run = "3";
        this->route.insert(0, run);
        chooseMove();
    } else {

        string newRoute = AStar::pathFind(x,y,xtarget,ytarget);
        if(newRoute == ""){
            chooseMove();
        } else {
            this->route = newRoute;
            chooseMove();
        }
    }

    //cout << this->route << endl;

        // follow the route on the map and display it
        /*if(this->route.length()>0)
        {
            int j; char c;
            int x=this->x()/10;
            int y=this->y()/10;
            AStar::Amap[x][y]=2;
            for(int i=0;i<route.length();i++)
            {
                c =route.at(i);
                j=atoi(&c);
                x=x+AStar::dx[j];
                y=y+AStar::dy[j];
                AStar::Amap[x][y]=3;
            }
            AStar::Amap[x][y]=4;

            // display the map with the route
            for(int y=0;y<100;y++)
            {
                for(int x=0;x<90;x++)
                    if(AStar::Amap[x][y]==0)
                        cout<<".";
                    else if(AStar::Amap[x][y]==1)
                        cout<<"O"; //obstacle
                    else if(AStar::Amap[x][y]==2)
                        cout<<"S"; //start
                    else if(AStar::Amap[x][y]==3)
                        cout<<"R"; //route
                    else if(AStar::Amap[x][y]==4)
                        cout<<"F"; //finish
                cout<<endl;
            }

            x=this->x()/10;
            y=this->y()/10;
            AStar::Amap[x][y]=0;
            for(int i=0;i<route.length();i++)
            {
                c =route.at(i);
                j=atoi(&c);
                x=x+AStar::dx[j];
                y=y+AStar::dy[j];
                AStar::Amap[x][y]=0;
            }
            AStar::Amap[x][y]=0;
        }
        cout << endl;*/
}

void Enemy::initialize(){

    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(150);
}

void Enemy::chooseMove()
{
    char digit = this->route.front();
    int movement = digit - '0';
    switch (movement) {
    case 0:{ // derecha
        if(!(x()+factor+factor/5 > scene()->width())){
            setPos(x()+factor/5,y());
        } else {
            setPos(x()-factor/5,y());
        }
        break;
    }
    case 1:{ // abajo
        if(!(y()+factor+factor/5 > scene()->height())){
            setPos(x(),y()+factor/5);
        } else {
            setPos(x(),y()-factor/5);
        }
        break;
    }
    case 2:{ // izquierda
        if(!(x()-factor-factor/5 < 0)){
            setPos(x()-factor/5,y());
        } else {
            setPos(x()+factor/5,y());
        }
        break;
    }
    case 3:{ // arriba
        if (!(y()-factor-factor/5 < 0)){
            setPos(x(),y()-factor/5);
        } else {
            setPos(x(),y()+factor/5);
        }
        break;
    }
    default:
        break;
    }
    if(this->route != ""){
        this->route.erase(this->route.begin());
    }
}
