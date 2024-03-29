#pragma once

#include <vector>
#include "ofMain.h"

class Maze{

    enum MazeTile{
        FREE = 0,
        WALL = 1,
        START = 2,
        GOAL = 3,
        VISITED = 4
    };

    private:
        vector<vector<MazeTile>> maze;
        ofImage mazePreview;
        ofImage remy;
        ofImage remyCheese;
        ofImage remyDead;
        ofImage cheese;

    public:
        Maze(string fileName);

        void draw();


};