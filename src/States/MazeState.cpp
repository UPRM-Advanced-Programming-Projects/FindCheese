#include "MazeState.h"

MazeState::MazeState(vector<Maze> mazes){
    this->mazes = mazes;
    font.load("font.otf", 24);

    ofRectangle border = this->mazes[0].getBorder();

    int buttonWidth = 75;
    int buttonHeight = 75;
    int spacing = 10;
    int x = border.x + border.width/2 - buttonWidth/2;
    int y = border.getBottom() + buttonHeight/2 + 10;

    this->playButton = new Button(
        x,
        y,
        buttonWidth,
        buttonHeight,
        ofImage("play.png")
    );

    this->forwardButton = new Button(
        x + buttonWidth + spacing,
        y,
        buttonWidth,
        buttonHeight,
        ofImage("forward.png")
    );

    this->backwardButton = new Button(
        x - buttonWidth - spacing,
        y,
        buttonWidth,
        buttonHeight,
        ofImage("backward.png")
    );

    this->resetButton = new Button(
        x - 2*(buttonWidth + spacing),
        y,
        buttonWidth,
        buttonHeight,
        ofImage("reset.png")
    );

    // Create the solutions
    // NOTE: The order that the solutions are added here will be the order
    // that they will be represented as internally
    // for example: solutions[0] will be the first solution added here
    solutions.push_back(new RecursionSolution());
    solutions.push_back(new DFSSolution());
    solutions.push_back(new BFSSolution());

    reset();
}

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

    // Draw the result if we finished the visualization
    if (finishedVisualization) {
        // Create a slightly transparent rectangle
        // Green if solved, red if not
        ofSetColor(solved ? ofColor(0,100,0) : ofColor(100,0,0), 150);

        ofFill();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        // Draw the result text
        ofSetColor(0, 0, 0);
        font.drawString(solved ? "Solved!" : "Not Solved!", ofGetWidth()/2 - font.stringWidth(solved ? "Solved!" : "Not Solved!")/2, ofGetHeight()/2);

    }

}

void MazeState::reset() {
    pathIndex = 0;
    finishedVisualization = false;
    
    // Reset all the mazes
    for (int i = 0; i < mazes.size(); i++) {
        mazes[i].reset();
    }


    // Grab the solution to use, and create the vectors
    // that will store our result
    solution = solutions[solutionIndex];
    vector<pair<int, int>> solutionPath;
    vector<pair<int, int>> pathTaken;

    // Solve the maze. This function will populate solutionPath and pathTaken
    // with the path to take and the path explored to solve the maze
    solution->solve(
        mazes[selectedMaze], 
        solutionPath, 
        pathTaken
    );

    // After this point, solutionPath should contain the path to take to solve the maze
    // and pathTaken should contain the path explored to solve the maze
    pathToTake = visualizeSolution ? 
        solutionPath : 
        pathTaken;
}

void MazeState::mousePressed(int x, int y, int button) {

    playButton->mousePressed(x, y);
    forwardButton->mousePressed(x, y);
    backwardButton->mousePressed(x, y);
    resetButton->mousePressed(x, y);

    if (forwardButton->wasPressed()) {
        advancePath();
    }

    if (backwardButton->wasPressed()) {
        retreatPath();
    }

    if (resetButton->wasPressed()) {
        reset();
    }
}

void MazeState::keyPressed(int key) {

    if (key == OF_KEY_RIGHT) {
        advancePath();
    }

    if (key == OF_KEY_LEFT) {
        retreatPath();
    }

    if (key == ' ') {
        reset();
    }
}

void MazeState::advancePath() {

    // Get the current maze
    Maze currentMaze = mazes[selectedMaze];

    // Get the current position
    pair<int, int> currentPosition = pathToTake.size() == 0 ? 
        currentMaze.getStartPosition() : 

        // NOTE: pathIndex is always valid, since we only increment it
        // if we haven't finished the visualization
        pathToTake[pathIndex];  

    // Determine if we reached the goal and if we finished the visualization
    finishedVisualization = pathIndex+1 >= pathToTake.size();
    solved = currentPosition == currentMaze.getGoalPosition();

    // Only increment the pathIndex if we haven't finished the visualization
    if(!finishedVisualization){

        // Set the current position to VISITED
        currentMaze.setTile(currentPosition, MazeTile::VISITED);

        // Increment the pathIndex
        pair<int, int> nextPosition = pathToTake[++pathIndex];

        currentMaze.setCurrentPosition(nextPosition);

        // Update the maze
        mazes[selectedMaze] = currentMaze;
        
    }
}

void MazeState::retreatPath() {
    if (pathIndex > 0) {
        Maze currentMaze = mazes[selectedMaze];

        // Decrement the pathIndex
        pair<int, int> nextPosition = pathToTake[--pathIndex];

        // Set the current position to FREE
        currentMaze.setTile(nextPosition, MazeTile::FREE);

        // Set the current position to the new position
        currentMaze.setCurrentPosition(nextPosition);

        // Update the maze
        mazes[selectedMaze] = currentMaze;

        finishedVisualization = false;
    }
}