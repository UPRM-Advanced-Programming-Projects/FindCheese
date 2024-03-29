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
        ofRectangle border;
        int cellWidth, cellHeight;
        int currentX, currentY;
        int remyX, remyY;
        int goalX, goalY;

        // Images
        ofImage remy;
        ofImage remyCheese;
        ofImage remyDead;
        ofImage cheese;

    public:
        Maze(string fileName);
        void draw();
        vector<vector<MazeTile>> getMaze() { return maze; }
        ofImage getMazePreview();
};