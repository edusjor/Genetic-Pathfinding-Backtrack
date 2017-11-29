#ifndef NODE_H
#define NODE_H

class Node
{
public:
    bool move0;
    bool move1;
    bool move2;
    bool move3;

    Node(bool move0, bool move1, bool move2, bool move3) {
        this->move0 = move0;
        this->move1 = move1;
        this->move2 = move2;
        this->move3 = move3;
    }

    Node(){
        this->move0 = false;
        this->move1 = false;
        this->move2 = false;
        this->move3 = false;
    }
};

#endif // NODE_H
