#include "State.h"
#include <vector>
#include "Button.h"

class MazeSelectionState : public State {
    private:
        ofTrueTypeFont font;
        vector<Button*> buttons;
        vector<Button*> imageButtons;
        int selectedMaze = -1;

    public:
        MazeSelectionState(){
            font.load("font.otf", 24);
            reset();
        }
        void update();
        void draw();
        void reset();
        void mousePressed(int x, int y, int button);
        int getSelectedMaze(){return selectedMaze;};
};