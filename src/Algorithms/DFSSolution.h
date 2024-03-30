#include "AbstractSolution.h"

class DFSSolution : public AbstractSolution {
    public:
        DFSSolution(vector<vector<MazeTile>> maze) : AbstractSolution(maze) {}
        void solve();
};