#include "Maze.h"

Maze::Maze(string fileName){

    // Load the images
    remy.load("remy.png");
    remyCheese.load("remy_win.png");
    remyDead.load("remy_lose.png");
    cheese.load("cheese.png");

    // Load the maze from the .txt file
    ofBuffer buffer = ofBufferFromFile(fileName);
    if(buffer.size()){
        for(auto line : buffer.getLines()){                    

            // convert string to MazeTile
            vector<MazeTile> row;
            for(auto tile : ofSplitString(line, " ")){
                MazeTile tileType = (MazeTile)ofToInt(tile);

                // Handle special tiles
                if (tileType == START){
                    currentX = row.size();
                    currentY = maze.size();
                    tileType = FREE; // Start is a free tile
                }
                else if (tileType == GOAL){
                    goalX = row.size();
                    goalY = maze.size();
                    tileType = FREE; // Goal is a free tile
                }
                row.push_back(tileType);
            }

            maze.push_back(row);
        }

        // Set the maze width and height
        width = ofGetWidth() * .75;
        height = ofGetHeight() * .75;

        // Set the cell width and height
        cellWidth = width / maze[0].size();
        cellHeight = height / maze.size();

    }

}

void Maze::draw(){
    // Draw the maze
    int left = ofGetWidth() * .01;
    int top = ofGetHeight() * .1;

    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetLineWidth(3);
    ofSetColor(0);
    ofNoFill();
    ofDrawRectangle(left, top, width, height);

    if (maze.size() == 0)
        ofLogError("Maze::draw") << "Maze is empty";

    if (maze[0].size() == 0)
        ofLogError("Maze::draw") << "Maze row is empty";

    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[i].size(); j++){
            ofNoFill();
            switch(maze[i][j]){
                case WALL:
                    ofFill();
                case FREE:
                    ofSetColor(0);
                    break;
                case VISITED:
                    ofSetColor(255, 0, 0);
                    break;
                default:
                    ofSetColor(255, 255, 0);
            }

            ofRectangle border(left + j * cellWidth, top + i * cellHeight, cellWidth, cellHeight);
            ofDrawRectangle(border);
            if (maze[i][j] == START){
                ofSetColor(255,255,255);
                remy.draw(border);
            }
            else if (maze[i][j] == GOAL){
                ofSetColor(255,255,255);
                cheese.draw(border);
            }
        }
    }

    // Draw remy at the current position
    ofRectangle border(left + currentX * cellWidth, top + currentY * cellHeight, cellWidth, cellHeight);
    ofSetColor(255,255,255);
    remy.draw(border);

    // Draw the goal
    ofRectangle goalBorder(left + goalX * cellWidth, top + goalY * cellHeight, cellWidth, cellHeight);
    cheese.draw(goalBorder);
}