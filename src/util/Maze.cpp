#include "Maze.h"

Maze::Maze(string fileName){

    remy.load("remy.png");
    remyCheese.load("remy_win.png");
    remyDead.load("remy_lose.png");
    cheese.load("cheese.png");

    // Load the maze from the .txt file
    // TODO: what happens if the file does not exist?
    ofBuffer buffer = ofBufferFromFile(fileName);
    if(buffer.size()){
        for(auto line : buffer.getLines()){                    

            // convert string to MazeTile
            vector<MazeTile> row;
            for(auto tile : ofSplitString(line, " ")){
                row.push_back((MazeTile)ofToInt(tile));
            }

            maze.push_back(row);
        }
    }

}

void Maze::draw(){
    // Draw the maze
    int left = ofGetWidth() * .01;
    int top = ofGetHeight() * .1;
    int width = ofGetWidth() * .75;
    int height = ofGetHeight() * .75;
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetLineWidth(3);
    ofSetColor(0);
    ofNoFill();
    ofDrawRectangle(left, top, width, height);

    if (maze.size() == 0)
        ofLogError("Maze::draw") << "Maze is empty";

    if (maze[0].size() == 0)
        ofLogError("Maze::draw") << "Maze row is empty";

    int cellWidth = width / maze[0].size();
    int cellHeight = height / maze.size();

    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[i].size(); j++){
            ofNoFill();
            switch(maze[i][j]){
                case WALL:
                    ofFill();
                case START:
                case FREE:
                    ofSetColor(0);
                    break;
                case VISITED:
                    ofSetColor(255, 0, 0);
                    break;
                case GOAL:
                    ofSetColor(0, 255, 0);
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
}