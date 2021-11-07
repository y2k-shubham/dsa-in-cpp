// LeetCode-1011: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
// incomplete: doesnt compile

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    long long findTotalWeight(vector<int>& weights) {
        return accumulate(weights.begin(), weights.end(), (long long)0);
    }

    bool canShip(
        vector<int>& weights,
        int maxDays,
        int cap) {
        int len = weights.size();
        int crrDay = 1;
        int crrIdx = 0;

        while (crrIdx < len) {
            if (crrDay > maxDays) {
                return false;
            }

            int crrDayWeight = 0;
            printf("cap=%d, crrDayWeight=%d, weights[crrIdx=%d]=%d\n", cap, crrDayWeight, crrIdx, weights[crrIdx]);
            while ((crrDayWeight + weights[crrIdx]) <= cap) {
                crrDayWeight += weights[crrIdx];
                crrIdx++;
            }

            crrDay++;
        }

        return crrDay <= maxDays;
    }

   public:
    int shipWithinDays(vector<int>& weights, int days) {
        long long totalWeight = findTotalWeight(weights);
        int minPerDayWeight = (int)ceil(totalWeight / (days * 1.0));
        long long maxPerDayWeight = totalWeight;

        int minReqPerDayWeight = INT_MAX;
        while (minPerDayWeight <= maxPerDayWeight) {
            int crrPerDayWeight = (int)((minPerDayWeight + maxPerDayWeight) / 2);
            if (canShip(weights, days, crrPerDayWeight)) {
                minReqPerDayWeight = min(minReqPerDayWeight, crrPerDayWeight);
                maxPerDayWeight = crrPerDayWeight - 1;
            } else {
                minPerDayWeight = crrPerDayWeight + 1;
            }
        }

        return minReqPerDayWeight;
    }
};
