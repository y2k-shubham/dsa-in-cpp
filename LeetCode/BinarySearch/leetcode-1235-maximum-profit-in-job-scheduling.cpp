// LeetCode-1235: https://leetcode.com/problems/maximum-profit-in-job-scheduling/
// Sorting + Binary Search
// not that hard as they portrayed it to be

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#include <stack>
#include <climits>
#include <unordered_map>
#include <tuple>

using namespace std;

class Solution {
private:
    bool debug;

    void showVec(vector<int>& vec, int iLo, int iHi, const char* name) {
        printf("\n----------\n");
        printf("%s vec is:-\n", name);

        printf("Ind:\t");
        for (int i = iLo; i <= iHi; i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = iLo; i <= iHi; i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");

        printf("----------\n");
    }

    vector <pair<int, int>> convertToPairVec(vector<int>& startTimes, vector<int>& endTimes) {
        if (startTimes.empty()) {
            return {};
        }

        int n = startTimes.size();
        vector <pair<int, int>> startEndTimes(n);

        for (int i = 0; i < n; i++) {
            startEndTimes[i] = make_pair(startTimes[i], endTimes[i]);
        }

        return startEndTimes;
    }

    void sortPairVec(vector <pair<int, int>>& pairVec) {
        if (pairVec.empty()) {
            return;
        }

        sort(pairVec.begin(), pairVec.end(), [](pair<int, int>& p1, pair<int, int>& p2) {
            return p1.second < p2.second;
        });
    }

    pair <vector<pair < int, int>>, vector<int> >
    breakIntoVecs(vector<tuple < int, int, int>
    >& tupleVec) {
        if (tupleVec.empty()) {
            return {{},
                    {}};
        }

        int len = tupleVec.size();
        vector <pair<int, int>> startEndTimes(len);
        vector<int> profits(len);

        for (int i = 0; i < len; i++) {
            startEndTimes[i] = make_pair(get<0>(tupleVec[i]), get<1>(tupleVec[i]));
            profits[i] = get<2>(tupleVec[i]);
        }

        return make_pair(startEndTimes, profits);
    }

    vector <tuple<int, int, int>>
    convertToTupleVec(vector<int>& startTimes, vector<int>& endTimes, vector<int>& profits) {
        if (startTimes.empty()) {
            return {};
        }

        int n = startTimes.size();
        vector<tuple < int, int, int> > startEndTimesProfits(n);

        for (int i = 0; i < n; i++) {
            startEndTimesProfits[i] = make_tuple(startTimes[i], endTimes[i], profits[i]);
        }

        return startEndTimesProfits;
    }

    void sortTupleVec(vector <tuple<int, int, int>>& tupleVec) {
        if (tupleVec.empty()) {
            return;
        }

        sort(tupleVec.begin(), tupleVec.end(), [](tuple<int, int, int>& t1, tuple<int, int, int>& t2) {
            return get<1>(t1) < get<1>(t2);
        });
    }

    int binSearchSecondItemLowerBound(
            vector <pair<int, int>>& pairVec,
            int target,
            int iLo,
            int iHi) {
        int n = iHi - iLo + 1;
        if ((n <= 0) || (iLo < 0) || (iHi >= pairVec.size())) {
            if (debug) {
                printf("returning INT_MAX for iLo=%d, iHi=%d, size=%d\n", iLo, iHi, (int) pairVec.size());
            }
            return INT_MAX;
        }

        int iMid = (iLo + iHi) / 2;
        int midEle = pairVec[iMid].second;

        if (midEle == target) {
            if (debug) {
                printf("at iMid=%d, returning midEle=target=%d for iLo=%d, iHi=%d\n", iMid, target, iLo, iHi);
            }
            return target;
        } else if (midEle < target) {
            int binSearchRes = binSearchSecondItemLowerBound(pairVec, target, iMid + 1, iHi);
            if (debug) {
                printf("at iMid=%d, returning min(mieEle=%d, binSearchUpper[..]=%d)=%d for iLo=%d, iHi=%d\n", iMid,
                       midEle, binSearchRes, min(midEle, binSearchRes), iLo, iHi);
            }

            return (binSearchRes == INT_MAX) ? midEle : binSearchRes;
        } else {
            int binSearchRes = binSearchSecondItemLowerBound(pairVec, target, iLo, iMid - 1);
            if (debug) {
                printf("at iMid=%d, returning binSearchLower[..]=%d for iLo=%d, iHi=%d\n", iMid, binSearchRes, iLo,
                       iHi);
            }

            return binSearchRes;
        }
    }

    int findMaxProfit(vector <pair<int, int>>& startEndTimes, vector<int>& profits) {
        int len = profits.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return profits[0];
        }

        vector<int> maxProfits(len, 0);
        maxProfits[0] = profits[0];
        if (debug) {
            showVec(maxProfits, 0, 0, "maxProfits");
        }

        unordered_map<int, int> endTimeMaxProfitsMap = {
                {-1,                      0},
                {0,                       0},
                {startEndTimes[0].second, maxProfits[0]}
        };

        for (int i = 1; i < len; i++) {
            pair<int, int> crrItem = startEndTimes[i];
            int crrStartTime = crrItem.first;

            int prevMaxEndTime = binSearchSecondItemLowerBound(startEndTimes, crrStartTime, 0, i - 1);
            int crrMaxProfit = max(maxProfits[i - 1], endTimeMaxProfitsMap[prevMaxEndTime] + profits[i]);

            maxProfits[i] = crrMaxProfit;
            endTimeMaxProfitsMap[crrItem.second] = max(endTimeMaxProfitsMap[crrItem.second], crrMaxProfit);

            if (debug) {
                showVec(maxProfits, 0, i, "maxProfits");
            }
        }

        return maxProfits[len - 1];
    }

public:
    friend class SolutionTest;

    int jobScheduling(vector<int>& startTimes, vector<int>& endTimes, vector<int>& profit) {
        vector<tuple < int, int, int> > tupleVec = convertToTupleVec(startTimes, endTimes, profit);
        sortTupleVec(tupleVec);

        pair < vector<pair < int, int> > , vector<int> > brokenVecs = breakIntoVecs(tupleVec);

        vector<pair < int, int> > startEndTimes = brokenVecs.first;
        vector<int> profits = brokenVecs.second;

        return findMaxProfit(startEndTimes, profits);
    }
};

class SolutionTest {
public:
    void testSortPairVec() {
        Solution soln = Solution();
        vector <pair<int, int>> vecIn;
        vector <pair<int, int>> vecOutExpected;
        vector <pair<int, int>> vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = vecIn;
        soln.sortPairVec(vecOutComputed);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {{1, 2},
                 {1, 1},
                 {0, 4},
                 {6, -1}};
        vecOutExpected = {{6, -1},
                          {1, 1},
                          {1, 2},
                          {0, 4}};
        vecOutComputed = vecIn;
        soln.sortPairVec(vecOutComputed);
        assert(vecOutExpected == vecOutComputed);
    }

    void testBinSearchSecondItemLowerBound() {
        Solution soln = Solution();
        vector <pair<int, int>> vecIn;
        int target;
        int iLo;
        int iHi;
        int outExpected;
        int outComputed;

        vecIn = {};

        target = 0;
        iLo = 0;
        iHi = -1;
        outExpected = INT_MAX;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        target = 0;
        iLo = 0;
        iHi = 0;
        outExpected = INT_MAX;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        vecIn = {
                {6, -1},
                {1, 1},
                {1, 2},
                {0, 4}};

        target = -1;
        iLo = 0;
        iHi = 3;
        outExpected = -1;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        target = 0;
        iLo = 0;
        iHi = 3;
        outExpected = -1;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        target = 0;
        iLo = 1;
        iHi = 3;
        outExpected = INT_MAX;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        target = 1;
        iLo = 0;
        iHi = 3;
        outExpected = 1;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        target = 2;
        iLo = 0;
        iHi = 3;
        outExpected = 2;
//        soln.debug = true;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);
//        soln.debug = false;

        target = 3;
        iLo = 0;
        iHi = 3;
        outExpected = 2;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);

        target = 3;
        iLo = 0;
        iHi = 2;
        outExpected = 2;
        outComputed = soln.binSearchSecondItemLowerBound(vecIn, target, iLo, iHi);
        assert(outExpected == outComputed);
    }

    void testFindMaxProfit() {
        Solution soln = Solution();
        vector <pair<int, int>> startEndTimes;
        vector<int> profits;
        int outExpected;
        int outComputed;

        startEndTimes = {};
        profits = {};
        outExpected = 0;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {{1, 2}};
        profits = {3};
        outExpected = 3;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {
                {0, 1},
                {1, 2},
                {1, 3},
                {0, 4}};
        profits = {1, 2, 3, 4};
        outExpected = 4;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

//        soln.debug = true;
        startEndTimes = {
                {0, 1},
                {1, 2},
                {1, 3},
                {0, 4}};
        profits = {5, 2, 3, 4};
        outExpected = 8;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);
//        soln.debug = false;

        startEndTimes = {
                {0, 1},
                {1, 3},
                {1, 2},
                {0, 4}};
        profits = {5, 3, 2, 4};
        outExpected = 8;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {
                {0, 1},
                {1, 2},
                {1, 3},
                {0, 4}};
        profits = {1, 2, 4, 4};
        outExpected = 5;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {
                {0, 1},
                {1, 2},
                {0, 2},
                {1, 3},
                {0, 4}};
        profits = {1, 2, 6, 4, 4};
        outExpected = 6;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {{1, 3},
                         {2, 4},
                         {3, 5},
                         {3, 6}};
        profits = {50, 10, 40, 70};
        outExpected = 120;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {{1, 3},
                         {2, 5},
                         {4, 6},
                         {6, 9},
                         {3, 10}};
        profits = {20, 20, 70, 60, 100};
        outExpected = 150;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);

        startEndTimes = {{1, 2},
                         {1, 3},
                         {1, 4}};
        profits = {5, 6, 4};
        outExpected = 6;
        outComputed = soln.findMaxProfit(startEndTimes, profits);
        assert(outExpected == outComputed);
    }

    void testJobScheduling() {
        Solution soln = Solution();
        vector<int> startTimes;
        vector<int> endTimes;
        vector<int> profits;
        int outExpected;
        int outComputed;

        startTimes = {};
        endTimes = {};
        profits = {};
        outExpected = 0;
        outComputed = soln.jobScheduling(startTimes, endTimes, profits);
        assert(outExpected == outComputed);

        startTimes = {1, 2, 3, 3};
        endTimes = {3, 4, 5, 6};
        profits = {50, 10, 40, 70};
        outExpected = 120;
        outComputed = soln.jobScheduling(startTimes, endTimes, profits);
        assert(outExpected == outComputed);

        startTimes = {1, 2, 3, 4, 6};
        endTimes = {3, 5, 10, 6, 9};
        profits = {20, 20, 100, 70, 60};
        outExpected = 150;
        outComputed = soln.jobScheduling(startTimes, endTimes, profits);
        assert(outExpected == outComputed);

        startTimes = {1, 1, 1};
        endTimes = {2, 3, 4};
        profits = {5, 6, 4};
        outExpected = 6;
        outComputed = soln.jobScheduling(startTimes, endTimes, profits);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testSortPairVec();
    solnTest.testBinSearchSecondItemLowerBound();
    solnTest.testFindMaxProfit();
    solnTest.testJobScheduling();

    return 0;
}
