#include "State.h"
#include "Maze.h"
#include "Button.h"
#include "AbstractSolution.h"
#include "DFSSolution.h"
#include "BFSSolution.h"
#include "RecursionSolution.h"

class MazeState : public State{
    private:

        int selectedMaze = 0;
        ofTrueTypeFont resultFont;
        ofTrueTypeFont uiFont;

        // Buttons
        Button* playButton;
        Button* forwardButton;
        Button* backwardButton;
        Button* resetButton;
        Button* nextSolutionButton;
        Button* previousSolutionButton;

        vector<Maze> mazes;

        // Variables for the end; once we reach the end of pathToTake
        bool solved = false;                    // Whether or not we reached the goal of the maze
        bool finishedVisualization = false;     // True when pathIndex == pathToTake.size()

        // Maze Visualization Variables
        vector<pair<int, int>> pathToTake;      // The path to take to solve the maze
        int pathIndex = 0;                      // The index of the path to take
        bool visualizeSolution = false;         // Whether or not to visualize the solution
                                                // If false, the exploration path will be visualized
                                                // instead. If true, the solution path will be visualized

        vector<string> mazeAlgorithmNames;


        // Maze Algorithms
        AbstractSolution* solution;             // The solution to use
        vector<AbstractSolution*> solutions;    // The solutions to choose from
        int solutionIndex = 0;                  // The index of the solution to use

        // Functions
        void advancePath();
        void retreatPath();

    public:
        MazeState(vector<Maze> mazes);
        void update();
        void draw();
        void reset();
        void mousePressed(int x, int y, int button);
        void keyPressed(int key);
        void setSelectedMaze(int selectedMaze){this->selectedMaze = selectedMaze;};
};