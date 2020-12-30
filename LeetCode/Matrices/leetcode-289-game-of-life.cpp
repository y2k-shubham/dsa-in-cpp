// LeetCode-289: https://leetcode.com/problems/game-of-life/
// LeetCode Dec 2020 Challenge: https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/573/week-5-december-29th-december-31st/3586/
// shittiest LC question seen till date (30th Dec 2020)

#include <cmath>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<pair<int, int>> getNeighbours(vector<vector<int>>& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<pair<int, int>> neighbours;

        for (int rDiff = -1; rDiff <= 1; rDiff++) {
            for (int cDiff = -1; cDiff <= 1; cDiff++) {
                if ((rDiff == 0) && (cDiff == 0)) {
                    continue;
                }

                int rNew = r + rDiff;
                int cNew = c + cDiff;
                if ((min(rNew, cNew) < 0) || (rNew >= rows) || (cNew >= cols)) {
                    continue;
                } else {
                    neighbours.push_back({rNew, cNew});
                }
            }
        }

        return neighbours;
    }

    int getNumLiveNeighbours(vector<vector<int>>& grid, int r, int c) {
        vector<pair<int, int>> neighbours = getNeighbours(grid, r, c);

        int numLiveNeighbours = 0;
        for (int i = 0; i < neighbours.size(); i++) {
            pair<int, int> nInd = neighbours[i];
            if (grid[nInd.first][nInd.second] == 1) {
                numLiveNeighbours++;
            }
        }

        return numLiveNeighbours;
    }

    void gameOfLife(vector<vector<int>>& board) {
        vector<vector<int>> grid = board;

        int rows = grid.size();
        int cols = grid[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int numLiveNeighbours = getNumLiveNeighbours(grid, i, j);
                bool isAlive = grid[i][j] == 1;

                if (numLiveNeighbours <= 1) {
                    // die (irrespective of whether it was living or dead)
                    board[i][j] = 0;
                } else if (isAlive) {
                    if ((2 <= numLiveNeighbours) && (numLiveNeighbours <= 3)) {
                        // no-op
                    } else if (numLiveNeighbours > 3) {
                        // die
                        board[i][j] = 0;
                    }
                } else if (!isAlive) {
                    if (numLiveNeighbours == 3) {
                        // become alive
                        board[i][j] = 1;
                    }
                }
            }
        }
    }
};
