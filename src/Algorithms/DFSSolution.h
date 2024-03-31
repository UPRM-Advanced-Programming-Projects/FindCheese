#include "AbstractSolution.h"

class DFSSolution : public AbstractSolution {
    public:
        bool solveHelper(
            int x,
            int y,
            Maze &maze,
            vector<pair<int, int>> &solutionPath,
            vector<pair<int, int>> &pathTaken
        );
};