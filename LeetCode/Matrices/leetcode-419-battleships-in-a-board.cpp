// LeetCode-419: https://leetcode.com/problems/battleships-in-a-board/

#include <vector>

using namespace std;

class Solution {
   public:
    int countBattleships(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        int numBattleShips = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == 'X') {
                    ++numBattleShips;

                    // eat horizontal cells (if battleship is placed horizontally)
                    if ((j < (cols - 1)) && (board[i][j + 1] == 'X')) {
                        while ((j < cols) && (board[i][j] == 'X')) {
                            board[i][j] = 'Y';
                            j++;
                        }
                    }

                    // eat vertical cells (if battleship is placed vertically)
                    int k = i;
                    if ((j < cols) && (k < (rows - 1)) && (board[k + 1][j] == 'X')) {
                        while ((k < rows) && (board[k][j] == 'X')) {
                            board[k][j] = 'Y';
                            k++;
                        }
                    }
                }
            }
        }

        return numBattleShips;
    }
};
