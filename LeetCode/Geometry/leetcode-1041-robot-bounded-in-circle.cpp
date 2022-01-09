// LeetCode-1041: https://leetcode.com/problems/robot-bounded-in-circle/

// impossible to solve without looking at the soln
// NeetCode: https://www.youtube.com/watch?v=nKv2LnC_g6E

/**
 *
 * input
 * "GGLLGG"
 * output
 * true
 *
 * input
 * "GG"
 * output
 * false
 *
 * input
 * "GL"
 * output
 * true
 *
 * input
 * "L"
 * output
 * true
 *
 * input
 * "R"
 * output
 * true
 *
 * input
 * "G"
 * output
 * false
 *
 * input
 * "GLRGRGRGLRLGLRGLRGLRGGRRGLRGLRGLGRLLLLLGRRGRLGRLGRLGRLGRLGLRGLRGLRGLRGL"
 * output
 * true
 *
 */

#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
   public:
    bool isRobotBounded(string instructions) {
        int dirX = 0, dirY = 1;
        int posX = 0, posY = 0;

        for (int i = 0; i < instructions.size(); i++) {
            char ch = instructions.at(i);

            switch (ch) {
                case 'G':
                    posX += dirX;
                    posY += dirY;
                    break;

                case 'L':
                    int tmp = dirX;
                    dirX = -dirY;
                    dirY = tmp;
                    break;

                default:
                    int tmp = dirX;
                    dirX = dirY;
                    dirY = -tmp;
                    break;
            }
        }

        bool isAtOrigin = (posX == 0) && (posY == 0);
        bool hasDirnChanged = (dirX != 0) || (dirY != 1);

        return isAtOrigin || hasDirnChanged;
    }
};
