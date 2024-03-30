#include "Maze.h"
#include <vector>

class AbstractSolution {

    protected:
        vector<vector<MazeTile>> maze;
        vector<pair<int, int>> pathTaken;
        vector<pair<int, int>> pathToTake;

    public:
        AbstractSolution(vector<vector<MazeTile>> maze){
            this->maze = maze;
        }

        // Solve the maze. Path taken is stored in pathTaken, and path to take is stored in pathToTake
        virtual void solve() = 0;
        vector<pair<int, int>> getPathTaken() { return pathTaken; }
        vector<pair<int, int>> getPathToTake() { return pathToTake; }
}