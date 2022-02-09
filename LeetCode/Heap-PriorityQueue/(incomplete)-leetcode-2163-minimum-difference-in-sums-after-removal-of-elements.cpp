// LeetCode-2163: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/
// Ordered map being used instead of heap over here

#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    map<int, int> buildFreqMap(vector<int>& vec, int lo, int hi) {
        map<int, int> freqMap;
        for (int i = lo; i <= hi; i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    void incEleFreq(map<int, int>& freqMap, int ele) {
        freqMap[ele]++;
    }

    void decEleFreq(map<int, int>& freqMap, int ele) {
        freqMap[ele]--;
        if (freqMap[ele] == 0) {
            freqMap.erase(ele);
        }
    }

    pair<int, int> findCrrLeftRemovalCandidate(map<int, int>& freqMapLeft, map<int, int>& freqMapMid) {
        if (freqMapMid.empty()) {
            return {0, 0};
        }

        int outgoingEle = freqMapLeft.rbegin()->first;
        int incomingEle = freqMapMid.begin()->first;

        return {outgoingEle, incomingEle};
    }

    pair<int, int> findCrrRightRemovalCandidate(map<int, int>& freqMapMid, map<int, int>& freqMapRight) {
        if (freqMapMid.empty()) {
            return {0, 0};
        }

        int outgoingEle = freqMapRight.begin()->first;
        int incomingEle = freqMapMid.rbegin()->first;

        return {outgoingEle, incomingEle};
    }

    bool removeSingleEle(
        map<int, int>& freqMapMid,
        map<int, int>& freqMapLeft,
        int& sumLeft,
        map<int, int>& freqMapRight,
        int& sumRight) {
        if (freqMapMid.empty()) {
            return false;
        }

        pair<int, int> leftRemovalCandidate = findCrrLeftRemovalCandidate(freqMapLeft, freqMapMid);
        int leftRemovalGain = leftRemovalCandidate.second - leftRemovalCandidate.first;

        pair<int, int> rightRemovalCandidate = findCrrRightRemovalCandidate(freqMapMid, freqMapRight);
        int rightRemovalGain = rightRemovalCandidate.first - rightRemovalCandidate.second;

        if (max(leftRemovalGain, rightRemovalGain) <= 0) {
            return false;
        }

        if (leftRemovalGain >= rightRemovalGain) {
            decEleFreq(freqMapMid, leftRemovalCandidate.second);
            incEleFreq(freqMapMid, leftRemovalCandidate.first);

            decEleFreq(freqMapLeft, leftRemovalCandidate.first);
            incEleFreq(freqMapLeft, leftRemovalCandidate.second);

            sumLeft -= leftRemovalCandidate.first;
            sumLeft += leftRemovalCandidate.second;
        } else {
            decEleFreq(freqMapMid, rightRemovalCandidate.second);
            incEleFreq(freqMapMid, rightRemovalCandidate.first);

            decEleFreq(freqMapRight, rightRemovalCandidate.first);
            incEleFreq(freqMapRight, rightRemovalCandidate.second);

            sumRight -= rightRemovalCandidate.first;
            sumRight += rightRemovalCandidate.second;
        }

        return true;
    }

   public:
    friend class SolutionTest;

    long long minimumDifference(vector<int>& nums) {
        int n3 = nums.size();
        int n1 = n3 / 3;
        int n2 = n1 * 2;

        map<int, int> freqMapLeft = buildFreqMap(nums, 0, n1 - 1);
        map<int, int> freqMapMid = buildFreqMap(nums, n1, n2 - 1);
        map<int, int> freqMapRight = buildFreqMap(nums, n2, n3 - 1);

        int sumLeft = accumulate(nums.begin(), nums.begin() + n1, 0);
        int sumRight = accumulate(nums.begin() + n2, nums.end(), 0);

        bool canOptimize = false;
        do {
            canOptimize = removeSingleEle(
                freqMapMid,
                freqMapLeft,
                sumLeft,
                freqMapRight,
                sumRight);
        } while (canOptimize);

        return sumLeft - sumRight;
    }
};

class SolutionTest {
   private:
    list<map<int, int>> buildFreqMaps(Solution soln, vector<int>& nums) {
        int n3 = nums.size();
        int n1 = n3 / 3;
        int n2 = n1 * 2;
        if ((n1 <= 0) || ((n3 % 3) > 0)) {
            return {{}, {}, {}};
        }

        map<int, int> freqMapLeft = soln.buildFreqMap(nums, 0, n1 - 1);
        map<int, int> freqMapMid = soln.buildFreqMap(nums, n1, n2 - 1);
        map<int, int> freqMapRight = soln.buildFreqMap(nums, n2, n3 - 1);

        list<map<int, int>> freqMaps = {freqMapLeft, freqMapMid, freqMapRight};
        return freqMaps;
    }

    

   public:
    void testBuildFreqMap() {
        Solution soln = Solution();
        vector<int> vecIn;
        list<map<int, int>> freqMapsOutExpected;
        list<map<int, int>> freqMapsOutComputed;

        vecIn = {};
        freqMapsOutExpected = {{}, {}, {}};
        freqMapsOutExpected = buildFreqMaps(soln, vecIn);
        // assert(freqMapsOutExpected == freqMapsOutComputed);

        vecIn = {3, 2, 1};
        freqMapsOutExpected = {{{3, 1}}, {{1, 1}}, {{2, 1}}};
        freqMapsOutExpected = buildFreqMaps(soln, vecIn);
        assert(freqMapsOutExpected == freqMapsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildFreqMap();
}
