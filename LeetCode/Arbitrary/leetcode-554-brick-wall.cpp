// LeetCode-554: https://leetcode.com/problems/brick-wall/

#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

class Solution {
private:
    void updateCumSumFreq(
            vector<vector<int> > &wall,
            unordered_map<int, int> &cumSumFreq,
            int row
    ) {
        int crrSum = 0;

        // note that no of bricks in each row is different
        for (int i = 0; i < wall[row].size(); i++) {
            crrSum += wall[row][i];
            cumSumFreq[crrSum]++;
        }

        // since width of entire wall is fixed,
        // we cant just draw a line at the end (right edge) of the wall
        cumSumFreq[crrSum]--;
    }

    unordered_map<int, int> buildCumSumFreqMap(vector<vector<int>> &wall) {
        unordered_map<int, int> cumSumFreq;

        for (int i = 0; i < wall.size(); i++) {
            updateCumSumFreq(wall, cumSumFreq, i);
        }

        return cumSumFreq;
    }

    int findMaxFreq(unordered_map<int, int> &freqMap) {
        int maxFreq = INT_MIN;

        for (
                unordered_map<int, int>::iterator it = freqMap.begin();
                it != freqMap.end();
                it++
                ) {
            maxFreq = max(maxFreq, it->second);
        }

        return maxFreq;
    }

public:
    int leastBricks(vector<vector<int>> &wall) {
        int numRows = wall.size();
        if (numRows <= 1) {
            if (wall[0].size() == 1) {
                // if there's just 1 brick like [[3]], then we have to cut it
                return 1;
            } else {
                // if there are multiple bricks like [[3,1,5]], then we can cut between bricks
                return 0;
            }
        }

        unordered_map<int, int> cumSumFreq = buildCumSumFreqMap(wall);
        int maxFreq = findMaxFreq(cumSumFreq);

        return numRows - maxFreq;
    }
};

