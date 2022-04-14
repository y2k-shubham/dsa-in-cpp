// LeetCode-1893: https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/
// current plain solution makes the question dumb
// but the clever solution didnt work https://github.com/y2k-shubham/dsa-in-cpp/pull/610/files

#include <vector>

using namespace std;

#define MAX_VAL 50

class Solution {
private:
    void fillSingleInterval(vector<bool>& rangeVec, int begin, int end) {
        for (int i = begin; i <= end; i++) {
            rangeVec[i] = true;
        }
    }

    void fillAllIntervals(vector<vector<int>>& ranges, vector<bool>& rangeVec) {
        for (int i = 0; i < ranges.size(); i++) {
            fillSingleInterval(rangeVec, ranges[i][0], ranges[i][1]);
        }
    }

    bool checkCoverage(vector<bool>& rangeVec, int left, int right) {
        for (int i = left; i <= right; i++) {
            if (!rangeVec[i]) {
                return false;
            }
        }

        return true;
    }

public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        vector<bool> rangeVec(MAX_VAL, false);
        fillAllIntervals(ranges, rangeVec);

        return checkCoverage(rangeVec, left, right);
    }
};
