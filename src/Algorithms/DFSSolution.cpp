#include "DFSSolution.h"

void DFSSolution::solve() {
    // Initialize the pathTaken and pathToTake vectors
    pathTaken.clear();
    pathToTake.clear();

    // Initialize the visited vector
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));

    // Initialize the stack
    stack<pair<int, int>> s;

    // Push the start position onto the stack
    s.push(make_pair(1, 1));

    // While the stack is not empty
    while (!s.empty()) {
        // Get the top of the stack
        pair<int, int> current = s.top();
        s.pop();

        // If the current position is the end position, break
        if (current.first == maze.size()-2 && current.second == maze[0].size()-2) {
            break;
        }

        // If the current position is not visited
        if (!visited[current.first][current.second]) {
            // Mark the current position as visited
            visited[current.first][current.second] = true;

            // Add the current position to the pathTaken vector
            pathTaken.push_back(current);

            // Check the four directions
            if (maze[current.first-1][current.second] == MazeTile::EMPTY) {
                s.push(make_pair(current.first-1, current.second));
            }
            if (maze[current.first+1][current.second] == MazeTile::EMPTY) {
                s.push(make_pair(current.first+1, current.second));
            }
            if (maze[current.first][current.second-1] == MazeTile::EMPTY) {
                s.push(make_pair(current.first, current.second-1));
            }
            if (maze[current.first][current.second+1] == MazeTile::EMPTY) {
                s.push(make_pair(current.first, current.second+1));
            }
        }
    }

    // Set the pathToTake vector to be the same as the pathTaken vector
    pathToTake = pathTaken;
}