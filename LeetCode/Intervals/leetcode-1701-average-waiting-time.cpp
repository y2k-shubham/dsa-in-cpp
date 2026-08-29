// LeetCode-1701: https://leetcode.com/problems/average-waiting-time/

#include <vector>

using namespace std;

class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int nxtStartTime = 0;
        long long totalWaitTime = 0;

        for (vector<int> customerArrivalTimeAndMealPrepDuration : customers) {
            int arrivalTime = customerArrivalTimeAndMealPrepDuration[0];
            int mealPrepDuration = customerArrivalTimeAndMealPrepDuration[1];

            int waitDueToDelayedStart;
            if (nxtStartTime >= arrivalTime) {
                // chef is already preparing something when current customer arrives
                waitDueToDelayedStart = nxtStartTime - arrivalTime;
                nxtStartTime += mealPrepDuration;
            } else {
                // chef is free when current customer arrives
                waitDueToDelayedStart = 0;
                nxtStartTime = arrivalTime + mealPrepDuration;
            }

            int waitTime = waitDueToDelayedStart + mealPrepDuration;
            totalWaitTime += waitTime;
        }

        int numCustomers = customers.size();
        return ((double) totalWaitTime) / numCustomers;
    }
};
