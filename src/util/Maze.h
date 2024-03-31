#pragma once

#include <vector>
#include "ofMain.h"

// Type definitions, to make the code more readable
// typedef vector<MazeTile> MazeRow;
// typedef vector<MazeRow> MazeGrid;
// typedef pair<int, int> MazePosition;
// typedef vector<MazePosition> MazePath;

enum MazeTile{
    FREE = 0,
    WALL = 1,
    START = 2,
    GOAL = 3,
    VISITED = 4
};

class Maze{

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
        void reset();

        // Getters
        vector<vector<MazeTile>> getMaze() { return maze; }
        ofImage getMazePreview();
        ofRectangle getBorder() { return border; }
        MazeTile getTile(int x, int y){ return maze[y][x]; }
        MazeTile getTile(pair<int, int> pos){ return getTile(pos.first, pos.second);}
        pair<int, int> getStartPosition(){ return make_pair(remyX, remyY); }
        pair<int, int> getGoalPosition(){ return make_pair(goalX, goalY); }

        bool isFree(int x, int y);
        bool isFree(pair<int, int> pos);

        void setTile(int x, int y, MazeTile tile){ maze[y][x] = tile; }
        void setTile(pair<int, int> pos, MazeTile tile){ setTile(pos.first, pos.second, tile); }

        void setCurrentPosition(int x, int y){ currentX = x; currentY = y; }
        void setCurrentPosition(pair<int, int> pos){ setCurrentPosition(pos.first, pos.second); }
        
   
};