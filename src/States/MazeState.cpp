#include "MazeState.h"

void MazeState::update() {
    //maze.update();
    playButton->update();
    forwardButton->update();
    backwardButton->update();
    resetButton->update();
}

void MazeState::draw() {
    this->mazes[selectedMaze].draw();

    // Draw the buttons
    playButton->draw();
    forwardButton->draw();
    backwardButton->draw();
    resetButton->draw();

}

void MazeState::reset() {
}

void MazeState::mousePressed(int x, int y, int button) {
    playButton->mousePressed(x, y);
    forwardButton->mousePressed(x, y);
    backwardButton->mousePressed(x, y);
    resetButton->mousePressed(x, y);
}