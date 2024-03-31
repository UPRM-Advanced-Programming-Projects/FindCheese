#include "MazeState.h"

MazeState::MazeState(vector<Maze> mazes){
    this->mazes = mazes;
    uiFont.load("font.otf", 18);
    resultFont.load("font.otf", 24);
    statisticsFont.load("font.otf", 14);

    // Load sounds
    loseSound.load("lose.mp3");
    winSound.load("win.mp3");

    ofRectangle border = this->mazes[0].getBorder();

    int buttonWidth = 75;
    int buttonHeight = 75;
    int spacing = 10;
    int x = border.x + border.width/2 - buttonWidth/2;
    int y = border.getBottom() + buttonHeight/2 + 10;

    playButtonImage.load("play.png");
    pauseButtonImage.load("pause.png");

    this->playButton = new Button(
        x,
        y,
        buttonWidth,
        buttonHeight,

        // If autoPlay is true, then we want to display the pause button
        autoPlay ? pauseButtonImage : playButtonImage
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

    this->nextSolutionButton = new Button(
        mazes[0].getBorder().getRight() + 3*(buttonWidth/2 + 20),
        mazes[0].getBorder().getTop() + buttonHeight + 50,
        buttonWidth,
        buttonHeight,
        ofImage("forward.png")
    );

    this->previousSolutionButton = new Button(
        mazes[0].getBorder().getRight() + buttonWidth/2 + 30,
        mazes[0].getBorder().getTop() + buttonHeight + 50,
        buttonWidth,
        buttonHeight,
        ofImage("backward.png")
    );

    // Create the solutions
    // NOTE: The order that the solutions are added here will be the order
    // that they will be represented as internally
    // for example: solutions[0] will be the first solution added here
    solutions.push_back(new RecursionSolution());
    solutions.push_back(new DFSSolution());
    solutions.push_back(new BFSSolution());

    mazeAlgorithmNames.push_back("Recursion");
    mazeAlgorithmNames.push_back("DFS");
    mazeAlgorithmNames.push_back("BFS");

    reset();
}

void MazeState::update() {
    //maze.update();
    playButton->update();
    forwardButton->update();
    backwardButton->update();
    resetButton->update();
    nextSolutionButton->update();
    previousSolutionButton->update();

    if (autoPlay && !finishedVisualization) {
        if (autoPlayCounter++ >= AUTO_PLAY_DELAY) {
            advancePath();
            autoPlayCounter = 0;
        }
    }
}

void MazeState::draw() {
    this->mazes[selectedMaze].draw();

    // Draw the buttons
    playButton->draw();
    forwardButton->draw();
    backwardButton->draw();
    resetButton->draw();
    nextSolutionButton->draw();
    previousSolutionButton->draw();


    // Draw the solution name centered above both the next/previous solution buttons
    ofSetColor(0, 0, 0);
    int right = nextSolutionButton->getBounds().getRight();
    int left = previousSolutionButton->getBounds().getLeft();
    int center = left + (right - left)/2;
    uiFont.drawString(mazeAlgorithmNames[solutionIndex], center - uiFont.stringWidth(mazeAlgorithmNames[solutionIndex])/2, nextSolutionButton->getBounds().getTop() - 30);

    // Draw "Current Solution" above the solution name
    string currentSolution = "Current Solution";
    uiFont.drawString(currentSolution, center - uiFont.stringWidth(currentSolution)/2, nextSolutionButton->getBounds().getTop() - 60);

    int x = mazes[selectedMaze].getBorder().getRight() + 10;
    // Draw "Statistics" below the next/previous solution buttons
    string statistics = "Statistics";
    uiFont.drawString(statistics, center - uiFont.stringWidth(statistics)/2, nextSolutionButton->getBounds().getBottom() + 30);

    string currentStep = "Current Step: " + to_string(pathIndex);
    statisticsFont.drawString(currentStep, x, nextSolutionButton->getBounds().getBottom() + 60);

    string stepsSearched = "Steps Searched: " + to_string(pathToTake.size());
    statisticsFont.drawString(stepsSearched, x, nextSolutionButton->getBounds().getBottom() + 90);

    string solutionLength = "Solution Length: " + to_string(solutionPath.size());
    statisticsFont.drawString(solutionLength, x, nextSolutionButton->getBounds().getBottom() + 120);

    // Draw the result if we finished the visualization
    if (finishedVisualization) {
        // Create a slightly transparent rectangle
        // Green if solved, red if not
        ofSetColor(ofColor::white, 150);

        ofFill();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

        // Draw the result text
        string topText = "This Maze Is...";
        ofSetColor(0, 0, 0);
        uiFont.drawString(topText, ofGetWidth()/2 - uiFont.stringWidth(topText)/2, 50);

        ofSetColor(solved ? ofColor::green : ofColor::red);
        string result = solved ? "POSSIBLE" : "IMPOSSIBLE";
        resultFont.drawString(result, ofGetWidth()/2 - resultFont.stringWidth(result)/2, ofGetHeight()/2);

        // Draw the "Press R to Reset" text
        ofSetColor(0,0,0);
        string resetText = "Press R to Reset";
        uiFont.drawString(resetText, ofGetWidth()/2 - uiFont.stringWidth(resetText)/2, ofGetHeight() - 50);
    }

}

void MazeState::reset() {
    pathIndex = 0;
    finishedVisualization = false;
    autoPlay = false;
    autoPlayCounter = 0;

    // Update play button image
    playButton->setImage(autoPlay ? pauseButtonImage : playButtonImage);
    
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

    // Save the solution path, so that we can render the steps
    // needed to solve the maze
    this->solutionPath = solutionPath;

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
    nextSolutionButton->mousePressed(x, y);
    previousSolutionButton->mousePressed(x, y);

    if (forwardButton->wasPressed()) {
        advancePath();
    }

    if (backwardButton->wasPressed()) {
        retreatPath();
    }

    if (resetButton->wasPressed()) {
        reset();
    }

    if (nextSolutionButton->wasPressed()) {
        solutionIndex = (solutionIndex + 1) % solutions.size();
        reset();
    }

    if (previousSolutionButton->wasPressed()) {
        solutionIndex = (solutionIndex - 1 + solutions.size()) % solutions.size();
        reset();
    }

    if (playButton->wasPressed()) {
        autoPlay = !autoPlay;
        autoPlayCounter = 0;

        playButton->setImage(autoPlay ? pauseButtonImage : playButtonImage);
    }
}

void MazeState::keyPressed(int key) {

    if (key == OF_KEY_RIGHT) {
        advancePath();
    }

    if (key == OF_KEY_LEFT) {
        retreatPath();
    }

    if (key == 'r') {
        reset();
    }

    if (key == ' ') {
        autoPlay = !autoPlay;
        autoPlayCounter = 0;

        playButton->setImage(autoPlay ? pauseButtonImage : playButtonImage);
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

    else{
        // Play the win sound if we solved the maze
        if (solved) {
            winSound.play();
        } else {
            loseSound.play();
        }
    
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