#include "MazeState.h"

void MazeState::update() {
    //maze.update();
}

void MazeState::draw() {
    // TEMP: Draw the selected maze value in the middle of the screen
    font.drawString("Maze " + ofToString(selectedMaze), ofGetWidth()/2 - font.stringWidth("Maze " + ofToString(selectedMaze))/2, ofGetHeight()/2);
    //maze.draw();
}

void MazeState::reset() {
    // TODO: use selectedMaze to load the correct maze
    //maze = Maze();
}

void MazeState::mousePressed(int x, int y, int button) {
    //maze.mousePressed(x, y);
}