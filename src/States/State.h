#pragma once

#include "ofMain.h"


enum StateName {
    UNKNOWN,
    TITLE_SCREEN,
    GAME
};

class State {

private:
    bool finished = false; // Whether or not the state is finished and should be switched
    StateName nextState;   // The next state to switch to

public:

    // Required functions
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void reset() = 0; // This is called when the state is reset

    // Optional functions
    virtual void keyPressed(int key){};
    virtual void keyReleased(int key){};
    virtual void mouseMoved(int x, int y){};
    virtual void mouseDragged(int x, int y, int button){};
    virtual void mousePressed(int x, int y, int button){};
    virtual void mouseReleased(int x, int y, int button){};

    bool isFinished() { return finished; }
    void setFinished(bool finished) { this->finished = finished; }

    StateName getNextState() { return nextState; }
    void setNextState(StateName nextState) { this->nextState = nextState; }
};