#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdlib.h>

using std::abs;

class Node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority
    int dir = 4;

    public:
        Node(int xp, int yp, int d, int p);

        int getxPos() const;
        int getyPos() const;
        int getLevel() const;
        int getPriority() const;

        void updatePriority(const int & xDest, const int & yDest);

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i); // i: direction

        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const;

        // Determine priority (in the priority queue)
        bool operator<(const Node & b) const;
};

#endif // NODE_H
