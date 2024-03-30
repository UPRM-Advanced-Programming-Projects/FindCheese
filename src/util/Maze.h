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
        double cellWidth, cellHeight;
        int currentX, currentY;
        int remyX, remyY;
        int goalX, goalY;
        string fileName;

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
        ofRectangle getBorder() { return border; }
        void reset();
};