// LeetCode-2833: https://leetcode.com/problems/furthest-point-from-origin/

#include <string>

using namespace std;

class Solution {
private:
    int calcFurthestDistanceLeft(string& moves) {
        int crrPos = 0;

        for (int i = 0; i < moves.size(); i++) {
            char ch = moves.at(i);

            if (ch == 'R') {
                crrPos++;
            } else {
                crrPos--;
            }
        }

        return abs(crrPos);
    }

    int calcFurthestDistanceRight(string& moves) {
        int crrPos = 0;

        for (int i = 0; i < moves.size(); i++) {
            char ch = moves.at(i);

            if (ch == 'L') {
                crrPos--;
            } else {
                crrPos++;
            }
        }

        return abs(crrPos);
    }

public:
    int furthestDistanceFromOrigin(string moves) {
        return max(
                calcFurthestDistanceLeft(moves),
                calcFurthestDistanceRight(moves)
        );
    }
};
