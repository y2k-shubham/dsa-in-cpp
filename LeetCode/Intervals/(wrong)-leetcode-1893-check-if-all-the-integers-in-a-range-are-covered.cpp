// LeetCode-1893: https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/
// wrong soln: this is very optimal but fails in test cases where for some interval [s, e]; s = e
// there could be more edge cases, but the crux is that this optimal approach is niether required nor correct

#include <vector>

using namespace std;

#define MAX_VAL 50

class Solution {
private:
    vector<int> createRangeVec() {
        vector<int> rangeVec(MAX_VAL + 1, 0);
        return rangeVec;
    }

    void fillRangeVec(vector<vector<int>>& ranges, vector<int>& rangeVec) {
        for (int i = 0; i < ranges.size(); i++) {
            rangeVec[ranges[i][0]] += 1;
            rangeVec[ranges[i][1]] -= 1;
//            if ((ranges[i][1] + 1) <= MAX_VAL) {
//                rangeVec[ranges[i][1] + 1] -= 1;
//            }
        }
    }

    void summateRangeVec(vector<int>& rangeVec) {
        for (int i = 1; i < rangeVec.size(); i++) {
            rangeVec[i] += rangeVec[i - 1];
        }
    }

    bool checkCoverage(vector<int>& rangeVec, int left, int right) {
        int crrSum = 0;
        bool wasPrevZero = false;
        for (int i = left; i <= right; i++) {
            bool isZero = rangeVec[i] <= 0;
            bool hasSucceedingInterval = ((i + 1) > MAX_VAL) || (((i + 1) <= MAX_VAL) && (rangeVec[i + 1] >= 1));
            if (isZero && !hasSucceedingInterval) {
                return false;
            }
        }

        return true;
    }

public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        vector<int> rangeVec = createRangeVec();

        fillRangeVec(ranges, rangeVec);
        summateRangeVec(rangeVec);

        return checkCoverage(rangeVec, left, right);
    }
};
