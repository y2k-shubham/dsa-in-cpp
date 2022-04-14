// LeetCode-1893: https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/
// incomplete (mis-understood the problem)

#include <vector>

using namespace std;

#define MAX_VAL 50

class Solution {
private:
    vector <int> createRangeVec() {
        vector <int> rangeVec(MAX_VAL + 1, 0);
        return rangeVec;
    }

    void fillRangeVec(vector<vector<int>>& ranges, vector <int>& rangeVec) {
        for (int i = 0; i < ranges.size(); i++) {
            rangeVec[ranges[i][0]] += 1;
            rangeVec[ranges[i][1]] -= 1;
        }
    }

    bool checkCoverage(vector <int>& rangeVec) {
        int crrSum = 0;
        bool wasPrevZero = false;
        for (int i = 1; i < rangeVec.size(); i++) {
            crrSum += rangeVec[i];
            if (crrSum <= 0) {
                if (wasPrevZero) {
                    return false;
                } else {
                    wasPrevZero = true;
                }
            } else {
                wasPrevZero = false;
            }
        }

        return true;
    }

public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        vector <int> rangeVec = createRangeVec();
        fillRangeVec(ranges, rangeVec);
        return checkCoverage(rangeVec);
    }
};
