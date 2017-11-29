#include "node.h"

Node::Node(int xp, int yp, int d, int p)
{
    this->xPos=xp;
    this->yPos=yp;
    this->level=d;
    this->priority=p;
}

int Node::getxPos() const {return xPos;}
int Node::getyPos() const {return yPos;}
int Node::getLevel() const {return level;}
int Node::getPriority() const {return priority;}

void Node::updatePriority(const int & xDest, const int & yDest)
{
     priority=level+estimate(xDest, yDest)*10; //A*
}

void Node::nextLevel(const int & i) // i: direction
{
     level+=(dir==8?(i%2==0?10:14):10);
}

const int & Node::estimate(const int & xDest, const int & yDest) const
{
    static int xd, yd, d;
    xd=xDest-xPos;
    yd=yDest-yPos;

    // Euclidian Distance
    //d=static_cast<int>(sqrt(xd*xd+yd*yd));

    // Manhattan distance
    d=abs(xd)+abs(yd);

    // Chebyshev distance
    //d=max(abs(xd), abs(yd));

    return(d);
}

bool Node::operator<(const Node & b) const
{
  return this->getPriority() > b.getPriority();
}
