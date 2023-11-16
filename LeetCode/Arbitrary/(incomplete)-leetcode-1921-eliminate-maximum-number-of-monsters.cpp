// LeetCode-1921: https://leetcode.com/problems/eliminate-maximum-number-of-monsters/
// wrong answer

#include <vector>

#define RECHARGE_TIME 1.0f

using namespace std;

class Solution {
private:
    vector<float> findReachTimes(vector<int>& dist, vector<int>& speed) {
        int len = dist.size();
        vector<float> reachTimes(len);

        for (int i = 0; i < len; i++) {
            reachTimes[i] = (float) dist[i] / speed[i];
        }

        return reachTimes;
    }

    int countTimesSpacedApartByMoreThan1Minute(vector<float>& sortedReachTimes) {
        int len = sortedReachTimes.size();
        float totalExcessTime = sortedReachTimes[0] - RECHARGE_TIME;
        for (int i = 1; i < len; i++) {
            float currentExcessTime = sortedReachTimes[i] - sortedReachTimes[i - 1];
            totalExcessTime += currentExcessTime;

            if (totalExcessTime <= RECHARGE_TIME) {
                return i;
            }
        }

        return len;
    }

public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        vector<float> reachTimes = findReachTimes(dist, speed);
        sort(reachTimes.begin(), reachTimes.end());

        return countTimesSpacedApartByMoreThan1Minute(reachTimes);
    }
};
