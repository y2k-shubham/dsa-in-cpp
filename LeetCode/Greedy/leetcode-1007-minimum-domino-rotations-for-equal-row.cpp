// LeetCode-1007: https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define NUM_VALS 6

class Solution {
   private:
    vector<int> buildFreqVec(vector<int>& vec) {
        vector<int> freqVec(NUM_VALS + 1, 0);

        for (int i = 0; i < vec.size(); i++) {
            freqVec[vec[i]]++;
        }

        return freqVec;
    }

    vector<int> buildCommonFreqVec(vector<int>& vec1, vector<int>& vec2) {
        vector<int> freqVec(NUM_VALS + 1, 0);

        for (int i = 0; i < vec1.size(); i++) {
            if (vec1[i] == vec2[i]) {
                freqVec[vec1[i]]++;
            }
        }

        return freqVec;
    }

    int findMinRotations(
        int len,
        vector<int>& primaryFreqVec,
        vector<int>& secondaryFreqVec,
        vector<int>& commonFreqVec) {
        int minRotations = INT_MAX;
        for (int i = 1; i <= NUM_VALS; i++) {
            int numTargetValsInPrimary = primaryFreqVec[i];
            int numTargetValsInSecondary = secondaryFreqVec[i];
            int numTargetValsInCommon = commonFreqVec[i];

            int totalNumTargetVals = numTargetValsInPrimary + numTargetValsInSecondary - numTargetValsInCommon;
            if (totalNumTargetVals == len) {
                int numRequiredSecondaryRotations = numTargetValsInSecondary - numTargetValsInCommon;
                minRotations = min(minRotations, numRequiredSecondaryRotations);

                if (minRotations == 0) {
                    return minRotations;
                }
            }
        }

        return minRotations;
    }

   public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int len = tops.size();

        vector<int> topsFreqVec = buildFreqVec(tops);
        vector<int> bottomsFreqVec = buildFreqVec(bottoms);

        vector<int> commonFreqVec = buildCommonFreqVec(tops, bottoms);

        int minRotations1 = findMinRotations(len, topsFreqVec, bottomsFreqVec, commonFreqVec);
        if (minRotations1 == 0) {
            return minRotations1;
        }
        int minRotations2 = findMinRotations(len, bottomsFreqVec, topsFreqVec, commonFreqVec);

        int minRotations = min(minRotations1, minRotations2);
        return (minRotations == INT_MAX) ? -1 : minRotations;
    }
};
