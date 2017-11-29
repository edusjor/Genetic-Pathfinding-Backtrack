#include "player.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include "bigmeteor.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

using std::cout;
using std::endl;

Player::Player(int width, int height, int factor, int xFinal, int yFinal)
{
    this->width = width;
    this->height = height;
    this->factor = factor;
    this->xFinal = xFinal;
    this->yFinal = yFinal;
    setRect(0,0,factor/2,factor/2);
    this->setBrush(Qt::white);
}

void Player::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Left){
        setPos(x()-factor/5,y());
    } else if (event->key() == Qt::Key_Right) {
        setPos(x()+factor/5,y());
    } else if (event->key() == Qt::Key_Up) {
        setPos(x(),y()-factor/5);
    } else if (event->key() == Qt::Key_Down) {
        setPos(x(),y()+factor/5);
    }
}

void Player::spawn()
{
    // set position
    int randomFactor;
    int randomSelector = rand() % 100;

    if (randomSelector < 50){
        randomFactor = rand() % 11 + 5;
        TinyMeteor * newMeteor = new TinyMeteor(this->width, this->height, this->factor);
        newMeteor->setPos(randomFactor*factor,0);
        scene()->addItem(newMeteor);

    } else if (50 <= randomSelector && randomSelector < 90){
        randomFactor = rand() % 10 + 5;
        StandardMeteor * newMeteor = new StandardMeteor(this->width, this->height, this->factor);
        newMeteor->setPos(randomFactor*factor,0);
        scene()->addItem(newMeteor);

    } else if (randomSelector >= 90){
        randomFactor = rand() % 9 + 5;
        BigMeteor * newMeteor = new BigMeteor(this->width, this->height, this->factor);
        newMeteor->setPos(randomFactor*factor,0);
        scene()->addItem(newMeteor);
    }
}

void Player::move()
{
    int x = this->x()/10;
    int y = this->y()/10;
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
        string newRoute = AStar::pathFind(x,y,this->xFinal/10,this->yFinal/10);
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

void Player::initialize(){
    //Original 15
    for (int i = 0; i < 15; ++i){
        // set position
        int randomFactorx;
        int randomFactory;
        int randomSelector = rand() % 100;

        if (randomSelector < 50){
            randomFactorx = rand() % 11 + 5;
            randomFactory = rand() % 16;
            TinyMeteor * newMeteor = new TinyMeteor(this->width, this->height, this->factor);
            newMeteor->setPos(randomFactorx*factor,randomFactory*factor);
            //BigMeteor * newMeteor = new BigMeteor(this->width, this->height, this->factor);
            //newMeteor->setPos(10*factor,9*factor - factor/2);
            scene()->addItem(newMeteor);

        } else if (50 <= randomSelector && randomSelector < 90){
            randomFactorx = rand() % 10 + 5;
            randomFactory = rand() % 15;
            StandardMeteor * newMeteor = new StandardMeteor(this->width, this->height, this->factor);
            newMeteor->setPos(randomFactorx*factor,randomFactory*factor);
            scene()->addItem(newMeteor);

        } else if (randomSelector >= 90){
            randomFactorx = rand() % 9 + 5;
            randomFactory = rand() % 14;
            BigMeteor * newMeteor = new BigMeteor(this->width, this->height, this->factor);
            newMeteor->setPos(randomFactorx*factor,randomFactory*factor);
            scene()->addItem(newMeteor);
        }
    }

    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(100);
}

void Player::chooseMove()
{
    if(this->route != ""){

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
        this->route.erase(this->route.begin());
    }
}

