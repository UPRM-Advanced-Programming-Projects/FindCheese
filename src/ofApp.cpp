#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
    font.load("font.otf", 12);

    for (int i = 0; i < 10; i++) {
        mazes.push_back(Maze("mazes/maze" + ofToString(i) + ".txt"));
    }

    titleScreenState = new TitleScreenState();
    mazeSelectionState = new MazeSelectionState();
    mazeState = new MazeState(mazes);
    currentState = titleScreenState;
    ofSetFrameRate(60);
    background.load("background.jpg");

    music.load("music.wav");
    music.setLoop(true);
    music.play();
    musicIcon.load("sound.png");
    muteIcon.load("mute.png");
    musicButton = new Button(ofGetWidth() - 50, 50, 50, 50, musicIcon);
}

//--------------------------------------------------------------
void ofApp::update() {
    if (currentState != nullptr) {
        if (currentState->isFinished()) {

            StateName nextState = currentState->getNextState();

            // Reset the finished and next state variables
            currentState->setFinished(false);
            currentState->setNextState(UNKNOWN);
            switch (nextState) {

            case TITLE_SCREEN:
                currentState = titleScreenState;
                break;

            case MAZE_SELECTION:
                currentState = mazeSelectionState;
                break;

            case GAME:
                mazeState->setSelectedMaze(mazeSelectionState->getSelectedMaze());
                mazeState->reset();
                currentState = mazeState;
                break;


            default:
                // Assume an error occurred or the game is finished
                ofExit();
                break;
            }

        }
        currentState->update();
    }
    musicButton->update();
}

//--------------------------------------------------------------
void ofApp::draw() {

    // Draw the background
    background.draw(0, 0, ofGetWidth(), ofGetHeight());

    if (currentState != nullptr)
        currentState->draw();

    // DEBUG: Display FPS at the top left corner
    ofSetColor(255, 255, 255);
    font.drawString("FPS: " + ofToString(ofGetFrameRate()), 10, 20);

    musicButton->draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    if (key == OF_KEY_BACKSPACE)
        currentState = titleScreenState;

    else if (currentState != nullptr)
        currentState->keyPressed(key);


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (currentState != nullptr)
        currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    if (currentState != nullptr)
        currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    if (currentState != nullptr)
        currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (currentState != nullptr)
        currentState->mousePressed(x, y, button);

    musicButton->mousePressed(x, y);

    if (musicButton->wasPressed()) {
        if (music.isPlaying()){
            music.stop();
            musicButton->setImage(muteIcon);
        }
        else{
            music.play();
            musicButton->setImage(musicIcon);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    if (currentState != nullptr)
        currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

//--------------------------------------------------------------