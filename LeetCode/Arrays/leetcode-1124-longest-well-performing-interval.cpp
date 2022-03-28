// LeetCode-1124: https://leetcode.com/problems/longest-well-performing-interval/
// tricky problem

#include <vector>
#include <unordered_map>

using namespace std;

#define HOURS_THRESHOLD 8

class Solution {
private:
    vector<int> buildSignVec(vector<int> &hours) {
        int len = hours.size();

        vector<int> signVec(len);
        for (int i = 0; i < len; i++) {
            if (hours[i] > HOURS_THRESHOLD) {
                signVec[i] = 1;
            } else {
                signVec[i] = -1;
            }
        }

        return signVec;
    }

public:
    int longestWPI(vector<int> &hours) {
        int len = hours.size();
        vector<int> signVec = buildSignVec(hours);

        unordered_map<int, int> sumFirstIdxMap;
        sumFirstIdxMap[0] = -1;

        int longestWindowLen = 0;
        int crrSum = 0;
        for (int i = 0; i < len; i++) {
            crrSum += signVec[i];

            if (crrSum > 0) {
                int crrWindowBeginIdx = 0;
                int crrWindowEndIdx = i;
                int crrWindowLen = crrWindowEndIdx - crrWindowBeginIdx + 1;

                longestWindowLen = max(longestWindowLen, crrWindowLen);
            } else if (crrSum <= 0) {
                if (sumFirstIdxMap.find(crrSum - 1) != sumFirstIdxMap.end()) {
                    int crrWindowBeginIdx = sumFirstIdxMap[crrSum - 1] + 1;
                    int crrWindowEndIdx = i;
                    int crrWindowLen = crrWindowEndIdx - crrWindowBeginIdx + 1;

                    longestWindowLen = max(longestWindowLen, crrWindowLen);
                }
            }

            if (sumFirstIdxMap.find(crrSum) == sumFirstIdxMap.end()) {
                sumFirstIdxMap[crrSum] = i;
            }
        }

        return longestWindowLen;
    }
};
