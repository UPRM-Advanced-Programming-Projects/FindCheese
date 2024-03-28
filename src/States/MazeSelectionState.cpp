#include "MazeSelectionState.h"

void MazeSelectionState::update(){
    for (int i = 0; i < buttons.size(); i++){
        buttons[i]->update();
    }
}

void MazeSelectionState::draw(){

    // Write "Select a maze" centered at the top of the screen
    font.drawString("Select a maze", ofGetWidth()/2 - font.stringWidth("Select a maze")/2, 30);


    for (int i = 0; i < buttons.size(); i++){
        buttons[i]->draw();
    }

    for (int i = 0; i < mazeImages.size(); i++){
        mazeImages[i].draw(imageBorders[i]);
    }

}

void MazeSelectionState::reset(){
    buttons.clear();
    // TEMP: use default.jpg for all maze images
    ofImage defaultImage;
    defaultImage.load("default.jpg");

    // Create 10 buttons and 10 images
    for (int i = 0; i < 10; i++){
        mazeImages.push_back(ofImage());
        //mazeImages[i].load("mazes/maze" + ofToString(i+1) + ".jpg");
        mazeImages[i] = defaultImage;

        imageBorders.push_back(ofRectangle(
            ofGetWidth()/2 +(ofGetWidth()/5 * ((i%5)-2))-75, 
            ofGetWidth()/3 + ofGetWidth()/3*(i/5)-225,  
            150, 
            150
        ));

        buttons.push_back(new Button(
            ofGetWidth()/2 +(ofGetWidth()/5 * ((i%5)-2)), 
            ofGetWidth()/3 + ofGetWidth()/3*(i/5),  
            100, 
            50, 
            "Maze " + ofToString(i)
        ));
    }




}

void MazeSelectionState::mousePressed(int x, int y, int button){
    for (int i = 0; i < buttons.size(); i++){
        buttons[i]->mousePressed(x, y);

        if (buttons[i]->wasPressed()){
            selectedMaze = i;
            this->setFinished(true);
            this->setNextState(GAME);
        }
    }
}