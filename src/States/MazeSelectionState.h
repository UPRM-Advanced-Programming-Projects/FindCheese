#include "State.h"
#include <vector>
#include "Button.h"

class MazeSelectionState : public State {
    private:
        ofTrueTypeFont font;
        vector<ofImage> mazeImages;
        vector<ofRectangle> imageBorders;
        vector<Button*> buttons;

    public:
        MazeSelectionState(){
            font.load("font.otf", 24);
            reset();
        }
        void update();
        void draw();
        void reset();
        void mousePressed(int x, int y, int button);
};