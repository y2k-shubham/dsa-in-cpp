// LeetCode-2008: https://leetcode.com/problems/maximum-earnings-from-taxi/
// identical to LeetCode-1235: https://leetcode.com/problems/maximum-profit-in-job-scheduling/

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

    void showVec(vector<long long>& vec, int iLo, int iHi, const char* name) {
        printf("\n----------\n");
        printf("%s vec is:-\n", name);

        printf("Ind:\t");
        for (int i = iLo; i <= iHi; i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = iLo; i <= iHi; i++) {
            printf("%lld\t", vec[i]);
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
    breakIntoVecs(vector<tuple < int, int, int>>
    & tupleVec) {
        if (tupleVec.empty()) {
            return {{},
                    {}};
        }

        int len = tupleVec.size();
        vector <pair<int, int>> startEndTimes(len);
        vector<int> tips(len);

        for (int i = 0; i < len; i++) {
            startEndTimes[i] = make_pair(get<0>(tupleVec[i]), get<1>(tupleVec[i]));
            tips[i] = get<2>(tupleVec[i]);
        }

        return make_pair(startEndTimes, tips);
    }

    vector <tuple<int, int, int>>
    convertToTupleVec(vector<int>& startTimes, vector<int>& endTimes, vector<int>& tips) {
        if (startTimes.empty()) {
            return {};
        }

        int n = startTimes.size();
        vector<tuple < int, int, int> > startEndTimestips(n);

        for (int i = 0; i < n; i++) {
            startEndTimestips[i] = make_tuple(startTimes[i], endTimes[i], tips[i]);
        }

        return startEndTimestips;
    }

    vector <tuple<int, int, int>> convertToTupleVec(vector <vector<int>>& vecVec) {
        if (vecVec.empty()) {
            return {};
        }

        int len = vecVec.size();
        vector<tuple < int, int, int> > tupleVec(len);

        for (int i = 0; i < len; i++) {
            tupleVec[i] = make_tuple(vecVec[i][0], vecVec[i][1], vecVec[i][2]);
        }

        return tupleVec;
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

    long long findMaxProfit(vector <pair<int, int>>& startEndTimes, vector<int>& tips) {
        int len = tips.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return (startEndTimes[0].second - startEndTimes[0].first) + tips[0];
        }

        vector<long long> maxEarnings(len, 0);
        maxEarnings[0] = (startEndTimes[0].second - startEndTimes[0].first) + tips[0];
        if (debug) {
            showVec(maxEarnings, 0, 0, "maxEarnings");
        }

        unordered_map<int, long long> endTimeMaxEarningsMap = {
                {-1,                      0},
                {0,                       0},
                {startEndTimes[0].second, maxEarnings[0]}
        };

        for (int i = 1; i < len; i++) {
            pair<int, int> crrItem = startEndTimes[i];
            int crrStartTime = crrItem.first;

            int prevMaxEndTime = binSearchSecondItemLowerBound(startEndTimes, crrStartTime, 0, i - 1);
            long long crrMaxProfit = max(
                    maxEarnings[i - 1],
                    endTimeMaxEarningsMap[prevMaxEndTime] +
                    ((startEndTimes[i].second - startEndTimes[i].first) + tips[i]));

            maxEarnings[i] = crrMaxProfit;
            endTimeMaxEarningsMap[crrItem.second] = max(endTimeMaxEarningsMap[crrItem.second], crrMaxProfit);

            if (debug) {
                showVec(maxEarnings, 0, i, "maxEarnings");
            }
        }

        return maxEarnings[len - 1];
    }

public:
    friend class SolutionTest;

    long long maxTaxiEarnings(int n, vector <vector<int>>& rides) {
        vector<tuple < int, int, int> > tupleVec = convertToTupleVec(rides);
        sortTupleVec(tupleVec);

        pair < vector<pair < int, int> > , vector<int> > brokenVecs = breakIntoVecs(tupleVec);

        vector<pair < int, int> > startEndTimes = brokenVecs.first;
        vector<int> tips = brokenVecs.second;

        return findMaxProfit(startEndTimes, tips);
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

    void testMaxTaxiEarnings() {
        Solution soln = Solution();
        int n;
        vector <vector<int>> ridesIn;
        long long earningsOutExpected;
        long long earningsOutComputed;

        soln.debug = true;
        n = 5;
        ridesIn = {{2, 5, 4}};
        earningsOutExpected = 7;
        earningsOutComputed = soln.maxTaxiEarnings(n, ridesIn);
        assert(earningsOutExpected == earningsOutComputed);
        soln.debug = false;

        n = 5;
        ridesIn = {{2, 5, 4},
                   {1, 5, 1}};
        earningsOutExpected = 7;
        earningsOutComputed = soln.maxTaxiEarnings(n, ridesIn);
        assert(earningsOutExpected == earningsOutComputed);

        n = 20;
        ridesIn = {{1,  6,  1},
                   {3,  10, 2},
                   {10, 12, 3},
                   {11, 12, 2},
                   {12, 15, 2},
                   {13, 18, 1}};
        earningsOutExpected = 20;
        earningsOutComputed = soln.maxTaxiEarnings(n, ridesIn);
        assert(earningsOutExpected == earningsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testSortPairVec();
    solnTest.testBinSearchSecondItemLowerBound();
    solnTest.testMaxTaxiEarnings();

    return 0;
}

