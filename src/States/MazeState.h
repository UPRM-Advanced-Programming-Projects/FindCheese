#include "State.h"
#include "Maze.h"

class MazeState : public State{
    private:
        int selectedMaze = 0;
        ofTrueTypeFont font;
        vector<Maze> mazes;

    public:
        MazeState(vector<Maze> mazes){
            this->mazes = mazes;
            font.load("font.otf", 24);
            reset();
        }
        void update();
        void draw();
        void reset();
        void mousePressed(int x, int y, int button);
        void setSelectedMaze(int selectedMaze){this->selectedMaze = selectedMaze;};
};