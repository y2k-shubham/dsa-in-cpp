// LeetCode-3096: https://leetcode.com/problems/minimum-levels-to-gain-more-points/
// remember that both players need to play at least one level

#include <vector>

using namespace std;

class Solution {
private:
    int calcBobsPointsFromRight(vector <int>& possible) {
        int totalPoints = 0;

        for (int i = possible.size() - 1; i >= 0; i--) {
            if (possible[i] == 1) {
                totalPoints += 1;
            } else {
                totalPoints -= 1;
            }
        }

        return totalPoints;
    }

    int findMinLevels(vector <int>& possible, int bobPoints) {
        int alicePoints = 0;
        for (int i = 0; i < possible.size() - 1; i++) {
            if (possible[i] == 0) {
                alicePoints -= 1;
                bobPoints += 1;
            } else {
                alicePoints += 1;
                bobPoints -= 1;
            }

            if (alicePoints > bobPoints) {
                return (i + 1);
            }
        }

        return -1;
    }

public:
    int minimumLevels(vector <int>& possible) {
        int bobPoints = calcBobsPointsFromRight(possible);
        return findMinLevels(possible, bobPoints);
    }
};
