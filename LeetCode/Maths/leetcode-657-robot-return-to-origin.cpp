// LeetCode-657: https://leetcode.com/problems/robot-return-to-origin/

#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        int numMoves = moves.size();
        if ((numMoves % 2) == 1) {
            return false;
        }

        int xPos = 0;
        int yPos = 0;

        for (int i = 0; i < numMoves; i++) {
            char ch = moves.at(i);
            if (ch == 'U') {
                yPos++;
            } else if (ch == 'D') {
                yPos--;
            } else if (ch == 'L') {
                xPos--;
            } else {
                xPos++;
            }

            // this pruning actually slows down the code
            int remMoves = numMoves - i - 1;
            if ((abs(xPos) + abs(yPos)) > remMoves) {
                return false;
            }
        }

        return (xPos == 0) && (yPos == 0);
    }
};

