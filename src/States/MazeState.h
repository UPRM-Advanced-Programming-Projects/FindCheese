#include "State.h"

class MazeState : public State{
    private:
        int selectedMaze = 0;
        ofTrueTypeFont font;


    public:
        MazeState(){
            font.load("font.otf", 24);
            reset();
        }
        void update();
        void draw();
        void reset();
        void mousePressed(int x, int y, int button);
        void setSelectedMaze(int selectedMaze){this->selectedMaze = selectedMaze;};
};