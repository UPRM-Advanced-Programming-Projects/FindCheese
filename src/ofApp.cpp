#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {
    font.load("font.otf", 12);
    titleScreenState = new TitleScreenState();
    currentState = titleScreenState;
    ofSetFrameRate(60);
    background.load("background.jpg");

    music.load("music.wav");
    music.setLoop(true);
    music.play();
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
            default:
                // Assume an error occurred or the game is finished
                ofExit();
                break;
            }

        }
        currentState->update();
    }
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
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (currentState != nullptr)
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