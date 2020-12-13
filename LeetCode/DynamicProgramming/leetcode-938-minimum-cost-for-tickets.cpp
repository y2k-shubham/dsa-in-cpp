// LeetCode-938: https://leetcode.com/problems/minimum-cost-for-tickets/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void showVec(vector<int> vec) {
    cout << "Idx:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "Val:\t";
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;
}

int incTrailIdxToDiff(vector<int>& vec, int advIdx, int trailIdx, int maxDiff) {
    int len = vec.size();

    if ((len == 0) || (advIdx >= len)) {
        return -1;
    }

    if (advIdx < 0 || trailIdx < 0) {
        return -1;
    }

    if (trailIdx > advIdx) {
        return -1;
    }

    while ((vec[advIdx] - vec[trailIdx]) >= maxDiff) {
        trailIdx++;
    }

    return trailIdx;
}

void testIncTrailIdxToDiff() {
    vector<int> vec;
    int advIdx;
    int trailIdx;
    int maxDiff;
    int idxOutExpected;
    int idxOutComputed;

    vec = {};
    advIdx = -1;
    trailIdx = -1;
    maxDiff = -1;
    idxOutExpected = -1;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {};
    advIdx = 3;
    trailIdx = 1;
    maxDiff = 3;
    idxOutExpected = -1;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {2};
    advIdx = 0;
    trailIdx = 0;
    maxDiff = 3;
    idxOutExpected = 0;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {2};
    advIdx = 0;
    trailIdx = 1;
    maxDiff = 3;
    idxOutExpected = -1;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {2};
    advIdx = 1;
    trailIdx = 0;
    maxDiff = 3;
    idxOutExpected = -1;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 2;
    trailIdx = 0;
    maxDiff = 7;
    idxOutExpected = 0;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 3;
    trailIdx = 0;
    maxDiff = 7;
    idxOutExpected = 0;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 4;
    trailIdx = 0;
    maxDiff = 7;
    idxOutExpected = 1;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 5;
    trailIdx = 0;
    maxDiff = 7;
    idxOutExpected = 5;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 5;
    trailIdx = 2;
    maxDiff = 7;
    idxOutExpected = 5;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 5;
    trailIdx = 4;
    maxDiff = 7;
    idxOutExpected = 5;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 4, 6, 7, 8, 20};
    advIdx = 5;
    trailIdx = 5;
    maxDiff = 7;
    idxOutExpected = 5;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 8;
    trailIdx = 1;
    maxDiff = 7;
    idxOutExpected = 2;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 8;
    trailIdx = 2;
    maxDiff = 7;
    idxOutExpected = 2;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 8;
    trailIdx = 3;
    maxDiff = 7;
    idxOutExpected = 3;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 10;
    trailIdx = 8;
    maxDiff = 7;
    idxOutExpected = 10;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 10;
    trailIdx = 9;
    maxDiff = 7;
    idxOutExpected = 10;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 10;
    trailIdx = 10;
    maxDiff = 7;
    idxOutExpected = 10;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);

    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    advIdx = 11;
    trailIdx = 10;
    maxDiff = 7;
    idxOutExpected = 10;
    idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
    assert(idxOutExpected == idxOutComputed);
}

// O(n) solution; LC-submission speed: 100 %tile, memory: 58 %tile
vector<int> createAndFillMemoVec(vector<int>& days, vector<int> costs, bool debug) {
    int cost1Day = costs[0];
    int cost7Days = costs[1];
    int cost30Days = costs[2];
    // they have test-cases where cost of 7-days ticket is less than cost of 1-day ticket
    int costCheapestTicket = min(cost30Days, min(cost7Days, cost1Day));

    int numDays = days.size();
    vector<int> memoVec(numDays);

    /**
     * each posn of memoVec will denote the minimum cost needed to reach till that day
     * (meaning be able to travel that day)
     * so then the min cost for first travel day would be to just get a 1-day ticket
     * .
     * but taking previous comment into account,
     * we'll say we'll get the cheapest ticket to travel for 1-day
     */
    memoVec[0] = costCheapestTicket;

    int idx30DaysBack = 0;
    int idx7DaysBack = 0;
    for (int idx = 1; idx < numDays; idx++) {
        idx30DaysBack = incTrailIdxToDiff(days, idx, idx30DaysBack, 30);
        idx7DaysBack = incTrailIdxToDiff(days, idx, idx7DaysBack, 7);

        if (debug) {
            cout << endl
                 << "---------" << endl;
            printf("At days[idx=%d] = %d\n", idx, days[idx]);
            printf("days[idx7DaysBack=%d] = %d\n", idx7DaysBack, days[idx7DaysBack]);
            printf("days[idx30DaysBack=%d] = %d\n", idx30DaysBack, days[idx30DaysBack]);
        }

        int minCostToReachIdx = INT_MAX;

        /**
         * if we were to reach here by buying a (1-day) ticket today itself
         * then we ought to take cost to reach until yesterday
         * and add cost of a 1-day ticket
         * (also why buy more than a 1-day ticket? there's no reason to spend more)
         * .
         * but taking previous comment into account,
         * we'll say we'll get the cheapest ticket to travel for 1-day
         */
        minCostToReachIdx = min(minCostToReachIdx, memoVec[idx - 1] + costCheapestTicket);
        if (debug) {
            cout << endl;
            printf("1-day ticket reach cost:-\n");
            printf(" = min cost to reach prev travel day + cost of cheapest ticket\n");
            printf(" = %d + %d\n", memoVec[idx - 1], costCheapestTicket);
            printf(" = %d\n", (memoVec[idx - 1] + costCheapestTicket));
        }

        /**
         * if we were to reach here by buying a 7-day ticket 7 (or lesser) days back,
         * then we ought to take cost to reach until a day before that T-7*th day
         * and add to it the cost of a 7-day ticket
         * (note that T-7*th day could be exactly 7 days back or less than that)
         */
        int minCostToReachIdx8DaysBack = 0;
        if (idx7DaysBack >= 1) {
            minCostToReachIdx8DaysBack = memoVec[idx7DaysBack - 1];
        }
        minCostToReachIdx = min(minCostToReachIdx, minCostToReachIdx8DaysBack + cost7Days);
        if (debug) {
            cout << endl;
            printf("7-days ticket reach cost:-\n");
            printf(" = min cost to reach 8-days back + cost of 7-day ticket\n");
            printf(" = %d + %d\n", minCostToReachIdx8DaysBack, cost7Days);
            printf(" = %d\n", (minCostToReachIdx8DaysBack + cost7Days));
        }

        /**
         * if we were to reach here by buying a 30-day ticket 30 (or lesser) days back,
         * then we ought to take cost to reach until a day before that T-30*th day
         * and add to it the cost of a 30-day ticket
         * (note that T-30*th day could be exactly 30 days back or less than that)
         */
        int minCostToReachIdx31DaysBack = 0;
        if (idx30DaysBack >= 1) {
            minCostToReachIdx31DaysBack = memoVec[idx30DaysBack - 1];
        }
        minCostToReachIdx = min(minCostToReachIdx, minCostToReachIdx31DaysBack + cost30Days);
        if (debug) {
            cout << endl;
            printf("30-days ticket reach cost:-\n");
            printf(" = min cost to reach 31-days back + cost of 30-day ticket\n");
            printf(" = %d + %d\n", minCostToReachIdx31DaysBack, cost30Days);
            printf(" = %d\n", (minCostToReachIdx31DaysBack + cost30Days));
        }

        memoVec[idx] = minCostToReachIdx;
        if (debug) {
            cout << endl;
            printf("min cost to reach days[idx=%d] = %dth day is %d\n", idx, days[idx], minCostToReachIdx);
        }
    }

    return memoVec;
}

void testCreateAndFillMemoVec() {
    vector<int> days;
    vector<int> costs;
    vector<int> memoVecOutExpected;
    vector<int> memoVecOutComputed;

    days = {1, 4, 6, 7};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 4, 6, 7, 8};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 9};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 4, 6, 7, 8, 20};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 9, 11};
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9, 11};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9, 11, 13};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9, 11, 13, 14};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9, 11, 13, 14, 14};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8, 11, 12};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9, 11, 13};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 7, 7, 9, 11, 13, 15, 17};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    days = {1, 2, 4, 6, 7, 8, 20};
    costs = {2, 7, 15};
    memoVecOutExpected = {2, 4, 6, 7, 7, 9, 11};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, true);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);

    //  trick test case: cost of 1-day ticket is more than cost of 7-days ticket
    days = {1, 2, 4, 6, 7, 8, 20};
    costs = {7, 2, 15};
    memoVecOutExpected = {2, 2, 2, 2, 2, 4, 6};
    // showVec(days);
    memoVecOutComputed = createAndFillMemoVec(days, costs, false);
    // showVec(memoVecOutComputed);
    assert(memoVecOutExpected == memoVecOutComputed);
}

int main() {
    testIncTrailIdxToDiff();
    testCreateAndFillMemoVec();

    return 0;
}
