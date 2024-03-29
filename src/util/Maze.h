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
        // Maze data
        vector<vector<MazeTile>> maze;
        int cellWidth;
        int cellHeight;
        int currentX;
        int currentY;
        int goalX;
        int goalY;
        int width;
        int height;

        // Images
        ofImage mazePreview;
        ofImage remy;
        ofImage remyCheese;
        ofImage remyDead;
        ofImage cheese;

    public:
        Maze(string fileName);

        void draw();


};