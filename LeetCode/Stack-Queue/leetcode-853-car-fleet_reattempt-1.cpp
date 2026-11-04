// LeetCode-853: https://leetcode.com/problems/car-fleet/

#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <set>
#include <utility>
#include <cfloat>
#include <unordered_set>
#include <cassert>

using namespace std;

bool compare(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    if (p1.first < p2.first) {
        return true;
    } else if (p1.first > p2.first) {
        return false;
    } else {
        return p1.second > p2.second;
    }
}

class Solution {
private:

    vector<pair<int, int> > createZippedSortedPosnSpeedVec(vector<int>& position, vector<int>& speed) {
        int len = position.size();
        if (len == 0) {
            return {};
        }

        vector<pair<int, int> > zippedVec(len);

        for (int i = 0; i < len; i++) {
            zippedVec[i] = {position[i], speed[i]};
        }

        sort(zippedVec.begin(), zippedVec.end(), compare);

        return zippedVec;
    }

    vector <float> convertToExpectedReachTimesVec(int target, vector<pair<int, int> >& zippedSortedPosnSpeedVec) {
        int len = zippedSortedPosnSpeedVec.size();
        if (len == 0) {
            return {};
        }

        vector <float> expectedReachTimeVec(len);

        for (int i = 0; i < len; i++) {
            pair <int, int> posnSpeed = zippedSortedPosnSpeedVec[i];
            int distance = target - posnSpeed.first;
            expectedReachTimeVec[i] = ((float) distance) / posnSpeed.second;
        }

        return expectedReachTimeVec;
    }

    vector <pair <float, int> > createNgeRightVec(vector <float>& vec) {
        int len = vec.size();
        vector <pair <float, int> > ngeRightVec(len);
        stack <pair <float, int>> stk;

        for (int i = len - 1; i >= 0; i--) {
            float crrVal = vec[i];

            while (!stk.empty() && (stk.top().first <= crrVal)) {
                stk.pop();
            }

            pair <float, int> ngeRight = stk.empty() ? make_pair(FLT_MAX, INT_MAX) : stk.top();
            ngeRightVec[i] = ngeRight;

            stk.push({crrVal, i});
        }

        return ngeRightVec;
    }

    vector <pair <float, int> > createNgeLeftVec(vector <float>& vec) {
        int len = vec.size();
        vector <pair <float, int> > ngeLeftVec(len);
        stack <pair <float, int>> stk;

        for (int i = 0; i < len; i++) {
            float crrVal = vec[i];

            while (!stk.empty() && (stk.top().first <= crrVal)) {
                stk.pop();
            }

            pair <float, int> ngeLeft = stk.empty() ? make_pair(0.0f, -1) : stk.top();
            ngeLeftVec[i] = ngeLeft;

            stk.push({crrVal, i});
        }

        return ngeLeftVec;
    }

    int countUniqueNgeVals_1_wrong(vector <pair <float, int> >& ngeRightVec) {
        unordered_set<int> ngeIdxs;

        for (pair <float, int> nge : ngeRightVec) {
            ngeIdxs.insert(nge.second);
        }

        return ngeIdxs.size();
    }

    int countUniqueNgeVals_2_correct(vector <pair <float, int> >& ngeLeftVec) {
        int numNgeVals = 0;
        int len = ngeLeftVec.size();

        for (int i = len - 1; i >= 0; ) {
            int ngeLeftIdx = ngeLeftVec[i].second;

            int numCarsInCrrFleet = (i - ngeLeftIdx - 1); // not required but this is how we can have it
            numNgeVals++;

            i = ngeLeftIdx;
        }

        return numNgeVals;
    }

public:

    friend class SolutionTest;

    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        // zip together positions & speeds and sort by positions
        vector<pair<int, int> > zippedSortedPosnSpeedVec = createZippedSortedPosnSpeedVec(position, speed);

        // calculate expected reach times
        vector <float> expectedReachTimesVec = convertToExpectedReachTimesVec(target, zippedSortedPosnSpeedVec);

        // // create NGE-right (float val, int idx) vector
        // vector <pair <float, int> > ngeRightVec = createNgeRightVec(expectedReachTimesVec);
        // // count unique NGE (index) values
        // int numUniqueNgeVals = countUniqueNgeVals_1_wrong(ngeRightVec);

        // create NGE-left (float val, int idx) vector
        vector <pair <float, int> > ngeLeftVec = createNgeLeftVec(expectedReachTimesVec);
        // count unique NGE (index) values
        int numUniqueNgeVals = countUniqueNgeVals_2_correct(ngeLeftVec);

        return numUniqueNgeVals;
    }
};

class SolutionTest {
public:

    void testCreateZippedSortedPosnSpeedVec() {
        Solution soln = Solution();
        vector <int> posnVecIn;
        vector <int> speedVecIn;
        vector <pair <int, int> > zippedSortedPosnSpeedVecOutExpected;
        vector <pair <int, int> > zippedSortedPosnSpeedVecOutComputed;

        posnVecIn = {};
        speedVecIn = {};
        zippedSortedPosnSpeedVecOutExpected = {};
        zippedSortedPosnSpeedVecOutComputed = soln.createZippedSortedPosnSpeedVec(posnVecIn, speedVecIn);
        assert(zippedSortedPosnSpeedVecOutExpected == zippedSortedPosnSpeedVecOutComputed);

        posnVecIn = {11};
        speedVecIn = {9};
        zippedSortedPosnSpeedVecOutExpected = {{11, 9}};
        zippedSortedPosnSpeedVecOutComputed = soln.createZippedSortedPosnSpeedVec(posnVecIn, speedVecIn);
        assert(zippedSortedPosnSpeedVecOutExpected == zippedSortedPosnSpeedVecOutComputed);

        posnVecIn = {10,8,0,5,3};
        speedVecIn = {2,4,1,1,3};
        zippedSortedPosnSpeedVecOutExpected = {{0, 1}, {3, 3}, {5, 1}, {8,4}, {10,2}};
        zippedSortedPosnSpeedVecOutComputed = soln.createZippedSortedPosnSpeedVec(posnVecIn, speedVecIn);
        assert(zippedSortedPosnSpeedVecOutExpected == zippedSortedPosnSpeedVecOutComputed);

        posnVecIn = {3};
        speedVecIn = {3};
        zippedSortedPosnSpeedVecOutExpected = {{3, 3}};
        zippedSortedPosnSpeedVecOutComputed = soln.createZippedSortedPosnSpeedVec(posnVecIn, speedVecIn);
        assert(zippedSortedPosnSpeedVecOutExpected == zippedSortedPosnSpeedVecOutComputed);

        posnVecIn = {0, 2, 4};
        speedVecIn = {4, 2, 1};
        zippedSortedPosnSpeedVecOutExpected = {{0,4}, {2,2}, {4,1}};
        zippedSortedPosnSpeedVecOutComputed = soln.createZippedSortedPosnSpeedVec(posnVecIn, speedVecIn);
        assert(zippedSortedPosnSpeedVecOutExpected == zippedSortedPosnSpeedVecOutComputed);
    }

    void testConvertToExpectedReachTimesVec() {
        Solution soln = Solution();
        vector <pair <int, int> > zippedSortedPosnSpeedVecIn;
        int targetIn;
        vector <float> expectedReachTimesVecOutExpected;
        vector <float> expectedReachTimesVecOutComputed;

        zippedSortedPosnSpeedVecIn = {{11, 9}};
        targetIn = 12;
        expectedReachTimesVecOutExpected = {(1.0f / 9)};
        expectedReachTimesVecOutComputed = soln.convertToExpectedReachTimesVec(targetIn, zippedSortedPosnSpeedVecIn);
        assert(expectedReachTimesVecOutExpected == expectedReachTimesVecOutComputed);

        zippedSortedPosnSpeedVecIn = {{0, 1}, {3, 3}, {5, 1}, {8,4}, {10,2}};
        targetIn = 12;
        expectedReachTimesVecOutExpected = {12.0f, 3.0f, 7.0f, 1.0f, 1.0f};
        expectedReachTimesVecOutComputed = soln.convertToExpectedReachTimesVec(targetIn, zippedSortedPosnSpeedVecIn);
        assert(expectedReachTimesVecOutExpected == expectedReachTimesVecOutComputed);

        zippedSortedPosnSpeedVecIn = {{3, 3}};
        targetIn = 10;
        expectedReachTimesVecOutExpected = {(7.0f / 3)};
        expectedReachTimesVecOutComputed = soln.convertToExpectedReachTimesVec(targetIn, zippedSortedPosnSpeedVecIn);
        assert(expectedReachTimesVecOutExpected == expectedReachTimesVecOutComputed);

        zippedSortedPosnSpeedVecIn = {{0,4}, {2,2}, {4,1}};
        targetIn = 100;
        expectedReachTimesVecOutExpected = {25.0f, 49.0f, 96.0f};
        expectedReachTimesVecOutComputed = soln.convertToExpectedReachTimesVec(targetIn, zippedSortedPosnSpeedVecIn);
        assert(expectedReachTimesVecOutExpected == expectedReachTimesVecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateZippedSortedPosnSpeedVec();
    solnTest.testConvertToExpectedReachTimesVec();

    return 0;
}
