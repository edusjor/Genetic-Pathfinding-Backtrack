#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>

#include "node.h"

using namespace std;

class AStar
{
public:
    static const int factor = 50;
    static const int n=90; // horizontal size of the map
    static const int m=100; // vertical size size of the map
    static int Amap[90][100];
    static int closed_nodes_map[90][100]; // map of closed (tried-out) nodes
    static int open_nodes_map[90][100]; // map of open (not-yet-tried) nodes
    static int dir_map[90][100]; // map of directions
    static const int dir=4; // number of possible directions to go at any position
    // if dir==4
    static constexpr int dx[4]={1, 0, -1, 0};
    static constexpr int dy[4]={0, 1, 0, -1};
    // if dir==8
    //static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
    //static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

    static string pathFind( const int & xStart, const int & yStart,
                     const int & xFinish, const int & yFinish );

};
#endif // ASTAR_H
