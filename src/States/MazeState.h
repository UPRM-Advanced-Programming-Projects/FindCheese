#include "State.h"
#include "Maze.h"
#include "Button.h"

class MazeState : public State{
    private:
        int selectedMaze = 0;
        ofTrueTypeFont font;
        Button* playButton;
        Button* forwardButton;
        Button* backwardButton;
        Button* resetButton;
        vector<Maze> mazes;
        

        // Maze Visualization Variables
        vector<pair<int, int>> pathTaken;       // The full path taken by the algorithm
        vector<pair<int, int>> pathToTake;      // The path to take to solve the maze
        int pathIndex = 0;                      // The index of the path to take

    public:
        MazeState(vector<Maze> mazes){
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

            reset();
        }
        void update();
        void draw();
        void reset();
        void mousePressed(int x, int y, int button);
        void setSelectedMaze(int selectedMaze){this->selectedMaze = selectedMaze;};
};