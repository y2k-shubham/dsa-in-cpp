// LeetCode-1014: https://leetcode.com/problems/best-sightseeing-pair

#include <vector>

using namespace std;

class Solution {
private:
    vector <int> createAdjustedMaxValueOnRightVec(vector <int>& vec) {
        int len = vec.size();
        vector <int> adjustedMaxValueOnRightVec(len, 0);
        if (len <= 1) {
            return adjustedMaxValueOnRightVec;
        }

        int adjustedMaxValueOnRight = 0;
        for (int i = len - 1; i >= 0; i--) {
            adjustedMaxValueOnRightVec[i] = adjustedMaxValueOnRight;

            adjustedMaxValueOnRight = max(adjustedMaxValueOnRight, vec[i]);
            adjustedMaxValueOnRight--;
        }

        return adjustedMaxValueOnRightVec;
    }

    int findMaxScoreSightseeingPair(vector <int>& vec, vector <int>& adjustedMaxValueOnRightVec) {
        int maxScore = 0;
        for (int i = 0; i < adjustedMaxValueOnRightVec.size(); i++) {
            maxScore = max(maxScore, vec[i] + adjustedMaxValueOnRightVec[i]);
        }

        return maxScore;
    }

public:
    int maxScoreSightseeingPair(vector <int>& values) {
        vector <int> adjustedMaxValueOnRightVec = createAdjustedMaxValueOnRightVec(values);
        return findMaxScoreSightseeingPair(values, adjustedMaxValueOnRightVec);
    }
};
