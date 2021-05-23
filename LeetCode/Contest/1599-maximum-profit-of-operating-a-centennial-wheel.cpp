// weekly contest 208: https://leetcode.com/contest/weekly-contest-208/problems/maximum-profit-of-operating-a-centennial-wheel/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    const int UNIT_CAPACITY = 4;

   private:
   public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        bool debug = false;

        int maxInstantProfit = INT_MIN;
        int maxInstantProfitIter = -1;

        int currentProfit = 0;
        int rotations = 0;
        int numWaitingCustomers = 0;

        int len = customers.size();
        for (int i = 0; (numWaitingCustomers > 0) || (i < len); i++) {
            int numArrivedCustomers = (i < len) ? customers[i] : 0;
            numWaitingCustomers += numArrivedCustomers;
            int numBoardedCustomers = 0;

            if (numWaitingCustomers == 0) {
                // shit
            } else {
                numBoardedCustomers = min(UNIT_CAPACITY, numWaitingCustomers);
                numWaitingCustomers -= numBoardedCustomers;

                currentProfit += numBoardedCustomers * boardingCost;
                currentProfit -= runningCost;
            }

            if (debug) {
                printf("at i=%d, arrived=%d, boarded=%d, waiting=%d, profit=%d\n", i, numArrivedCustomers, numBoardedCustomers, numWaitingCustomers, currentProfit);
            }

            if ((currentProfit > 0) && (currentProfit > maxInstantProfit)) {
                maxInstantProfit = currentProfit;
                maxInstantProfitIter = i + 1;
            }
        }

        return maxInstantProfitIter;
    }
};
