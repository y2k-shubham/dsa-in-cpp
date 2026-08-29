// LeetCode-2240: https://leetcode.com/problems/number-of-ways-to-buy-pens-and-pencils/

#include <iostream>

using namespace std;

class Solution {
public:
    // slower: 9 ms (LC submission)
    long long soln1_useSmall_asBase(int total, int cost1, int cost2) {
        int costSmall = min(cost1, cost2);
        int costBig = max(cost1, cost2);

        long long numWays = 0;
        for (int numSmallCostItems = 0; (numSmallCostItems * costSmall) <= total; numSmallCostItems++) {
            int totalCostSmall = numSmallCostItems * costSmall;
            int totalRemainingCost = total - totalCostSmall;

            int numBigCostItems = totalRemainingCost / costBig;

            printf("for numSmallCostItems=%d, calculated numBigCostItems=%d, adding=%d, (cum) numWays=%lld\n", numSmallCostItems, numBigCostItems, (numBigCostItems + 1), numWays);
            numWays += numBigCostItems + 1;
        }

        return numWays;
    }

    // faster: 3 ms (LC submission)
    long long soln2_useBig_asBase(int total, int cost1, int cost2) {
        int costSmall = min(cost1, cost2);
        int costBig = max(cost1, cost2);

        long long numWays = 0;
        for (int numBigCostItems = 0; (numBigCostItems * costBig) <= total; numBigCostItems++) {
            int totalCostBig = numBigCostItems * costBig;
            int totalRemainingCost = total - totalCostBig;

            int numSmallCostItems = totalRemainingCost / costSmall;

            numWays += numSmallCostItems + 1;
            printf("for numBigCostItems=%d, calculated numSmallCostItems=%d, adding=%d, (cum) numWays=%lld\n", numBigCostItems, numSmallCostItems, (numSmallCostItems + 1), numWays);
        }

        return numWays;
    }

    long long waysToBuyPensPencils(int total, int cost1, int cost2) {
        return soln2_useBig_asBase(total, cost1, cost2);
    }
};
