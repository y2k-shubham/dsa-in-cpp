// LeetCode-1306: https://leetcode.com/problems/jump-game-iii/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    bool canReach(vector<int>& arr, int start) {
        int len = arr.size();

        vector<int> minStepsToReachIdx(len, INT_MAX);
        minStepsToReachIdx[start] = 0;

        queue<int> idxs;
        idxs.push(start);

        while (!idxs.empty()) {
            int idx = idxs.front();
            idxs.pop();

            int stepsToReachIdx = minStepsToReachIdx[idx];
            int stepSize = arr[idx];

            // jump towards left
            int leftIdx = idx - stepSize;
            if ((leftIdx >= 0) && ((stepsToReachIdx + 1) < minStepsToReachIdx[leftIdx])) {
                minStepsToReachIdx[leftIdx] = stepsToReachIdx + 1;
                idxs.push(leftIdx);
            }

            // jump towards right
            int rightIdx = idx + stepSize;
            if ((rightIdx < len) && ((stepsToReachIdx + 1) < minStepsToReachIdx[rightIdx])) {
                minStepsToReachIdx[rightIdx] = stepsToReachIdx + 1;
                idxs.push(rightIdx);
            }
        }

        int minStepsToReachSomeZero = INT_MAX;
        for (int i = 0; i < len; i++) {
            if (arr[i] == 0) {
                minStepsToReachSomeZero = min(minStepsToReachSomeZero, minStepsToReachIdx[i]);
            }
        }

        return minStepsToReachSomeZero != INT_MAX;
    }
};
