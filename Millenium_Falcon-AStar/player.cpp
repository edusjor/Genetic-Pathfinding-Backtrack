#include "player.h"
#include "tinymeteor.h"
#include "standardMeteor.h"
#include "bigmeteor.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

using std::cout;
using std::endl;

QList<QGraphicsItem *> Player::colliding_items;
string Player::steps;
QTimer *Player::timer;
std::list<Node*> Player::movementList;
int Player::lastMovement;

Player::Player(int width, int height, int factor)
{
    this->width = width;
    this->height = height;
    this->factor = factor;
    setRect(0,0,factor/2,factor/2);
    timer = new QTimer();
    steps = "4";
    lastMovement = 4;

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

void Player::move(bool repeat)
{
    //cout << steps << endl;
    if (this->x() == factor){ //Ends when it reaches the end
        timer->stop();
        return;
    } else {

        int xreturn = this->x();
        int yreturn = this->y();

        if(!repeat){
            Node *newNode = new Node();
            movementList.push_back(newNode);
        }

        setPos(x()-factor/5, y()); //izquierda
        if (!verifyCollides() && !movementList.back()->move2 && x() > 0){
            const char *step = "2";
            steps.append(step);
            ++stepCounter;
            movementList.back()->move2 = true;
            lastMovement = 2;
            return;
        }

        setPos(xreturn, yreturn);

        switch (lastMovement) {
        case 0:{
            setPos(x()+factor/5, y()); //derecha
            if (!verifyCollides() && !movementList.back()->move0 && x() < scene()->height()){
                const char *step = "0";
                steps.append(step);
                ++stepCounter;
                movementList.back()->move0 = true;
                lastMovement = 0;
                return;
            }
            break;
        }
        case 1:{
            setPos(x(), y()+factor/5); // abajo
            if (!verifyCollides() && !movementList.back()->move1 && y() < scene()->width()){
                const char *step = "1";
                steps.append(step);
                ++stepCounter;
                movementList.back()->move1 = true;
                lastMovement = 1;
                return;
            }
            break;
        }
        case 3:{
            setPos(x(), y()-factor/5); //arriba
            if (!verifyCollides() && !movementList.back()->move3 && y() > 0){
                const char *step = "3";
                steps.append(step);
                ++stepCounter;
                movementList.back()->move3 = true;
                lastMovement = 3;
                return;
            }
            break;
        }
        }

        setPos(xreturn, yreturn);
        setPos(x(), y()-factor/5); //arriba
        if (!verifyCollides() && !movementList.back()->move3 && y() > 0){
            const char *step = "3";
            steps.append(step);
            ++stepCounter;
            movementList.back()->move3 = true;
            lastMovement = 3;
            return;
        }

        setPos(xreturn, yreturn);
        setPos(x(), y()+factor/5); // abajo
        if (!verifyCollides() && !movementList.back()->move1 && y() < scene()->width()){
            const char *step = "1";
            steps.append(step);
            ++stepCounter;
            movementList.back()->move1 = true;
            lastMovement = 1;
            return;
        }

        setPos(xreturn, yreturn);
        setPos(x()+factor/5, y()); //derecha
        if (!verifyCollides() && !movementList.back()->move0 && x() < scene()->height()){
            const char *step = "0";
            steps.append(step);
            ++stepCounter;
            movementList.back()->move0 = true;
            lastMovement = 0;
            return;
        }

        setPos(xreturn, yreturn);

        goBack();
         // After all the if's didn't work
    }
}

void Player::moveSlot()
{
    this->move(false);
}

bool Player::verifyCollides(){
    bool collides = false;
    colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i<n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(TinyMeteor) ||
                typeid(*(colliding_items[i])) == typeid(StandardMeteor) ||
                typeid(*(colliding_items[i])) == typeid(BigMeteor)){
            collides = true;
        } else if (this->x() > scene()->width() ||
                   this->x() < 0 ||
                   this->y() > scene()->height() ||
                   this->y() < 0) {
            collides = true;
        }
    }
    return collides;
}

void Player::goBack()
{
    Node *deleteNode = movementList.back();
    delete deleteNode;
    movementList.pop_back();
    --stepCounter;
    this->move(true);
}

void Player::initialize(){
    //Original 15
    for (int i = 0; i < 100; ++i){
        // set position
        int randomFactorx;
        int randomFactory;
        int randomSelector = rand() % 100;

        if (randomSelector < 50){
            randomFactorx = rand() % 12 + 4;
            randomFactory = rand() % 16;
            TinyMeteor * newMeteor = new TinyMeteor(this->width, this->height, this->factor);
            newMeteor->setPos(randomFactorx*factor,randomFactory*factor);
            //BigMeteor * newMeteor = new BigMeteor(this->width, this->height, this->factor);
            //newMeteor->setPos(10*factor,9*factor - factor/2);
            scene()->addItem(newMeteor);

        } else if (50 <= randomSelector && randomSelector < 90){
            randomFactorx = rand() % 11 + 4;
            randomFactory = rand() % 15;
            StandardMeteor * newMeteor = new StandardMeteor(this->width, this->height, this->factor);
            newMeteor->setPos(randomFactorx*factor,randomFactory*factor);
            scene()->addItem(newMeteor);

        } else if (randomSelector >= 90){
            randomFactorx = rand() % 10 + 4;
            randomFactory = rand() % 14;
            BigMeteor * newMeteor = new BigMeteor(this->width, this->height, this->factor);
            newMeteor->setPos(randomFactorx*factor,randomFactory*factor);
            scene()->addItem(newMeteor);
        }
    }

    connect(timer,SIGNAL(timeout()),this,SLOT(moveSlot()));

    timer->start(150);
}

