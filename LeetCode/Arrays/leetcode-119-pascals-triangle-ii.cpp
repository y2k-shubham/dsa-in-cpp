// LeetCode-119: https://leetcode.com/problems/pascals-triangle-ii

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return {1};
        }

        vector<int> prevVec = {1, 1};
        if (rowIndex == 1) {
            return prevVec;
        }

        for (int i = 2; i <= rowIndex; i++) {
            vector<int> crrVec(i + 1, 0);
            crrVec[0] = 1;
            crrVec[i] = 1;

            for (int j = 1; j < i; j++) {
                crrVec[j] = prevVec[j - 1] + prevVec[j];
            }

            if (i == rowIndex) {
                return crrVec;
            }

            prevVec = crrVec;
        }

        return {};
    }
};
