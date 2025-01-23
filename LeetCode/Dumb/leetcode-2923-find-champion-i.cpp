// LeetCode-2923: https://leetcode.com/problems/find-champion-i/

#include <vector>

using namespace std;

class Solution {
private:
    int count1sInRow(vector <vector <int>>& grid, int row) {
        int num1s = 0;
        for (int j = 0; j < grid[0].size(); j++) {
            num1s += grid[row][j];
        }

        return num1s;
    }

public:
    int findChampion(vector <vector <int>>& grid) {
        int numTeams = grid.size();

        for (int i = 0; i < numTeams; i++) {
            int numWeakerTeams = count1sInRow(grid, i);
            if (numWeakerTeams == (numTeams - 1)) {
                return i;
            }
        }

        return -1;
    }
};
