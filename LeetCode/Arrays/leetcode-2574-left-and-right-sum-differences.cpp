// LeetCode-2574: https://leetcode.com/problems/left-and-right-sum-differences

#include <vector>

using namespace std;

class Solution {
private:
    vector<int> createLeftSumVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> leftSumVec(len, 0);

        int leftSum = 0;
        for (int i = 1; i < len; i++) {
            leftSum += vec[i - 1];
            leftSumVec[i] = leftSum;
        }

        return leftSumVec;
    }

    vector<int> createRightSumVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> rightSumVec(len, 0);

        int rightSum = 0;
        for (int i = len - 2; i >= 0; i--) {
            rightSum += vec[i + 1];
            rightSumVec[i] = rightSum;
        }

        return rightSumVec;
    }

    vector<int> createModDiffVec(vector<int>& vec1, vector<int>& vec2) {
        int len = vec1.size();
        vector<int> modDiffVec(len, 0);

        for (int i = 0; i < len; i++) {
            modDiffVec[i] = abs(vec1[i] - vec2[i]);
        }

        return modDiffVec;
    }

public:
    vector<int> leftRightDifference(vector<int>& nums) {
        vector<int> leftSumVec = createLeftSumVec(nums);
        vector<int> rightSumVec = createRightSumVec(nums);
        return createModDiffVec(leftSumVec, rightSumVec);
    }
};
