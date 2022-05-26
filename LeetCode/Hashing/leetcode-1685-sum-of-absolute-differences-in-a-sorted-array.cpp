// LeetCode-1685: https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    map<int, int> buildFreqMap(vector<int>& vec) {
        map<int, int> freqMap;

        for (auto it = vec.begin(); it != vec.end(); it++) {
            freqMap[*it]++;
        }

        return freqMap;
    }

    map<int, int> convertToCumFreqMap(map<int, int>& freqMap) {
        map<int, int> cumFreqMap;

        int cumFreq = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            cumFreq += it->second;
            cumFreqMap[it->first] = cumFreq;
        }

        return cumFreqMap;
    }

    map<int, pair<int, int> > convertToSumMap(map<int, int>& freqMap) {
        map<int, pair<int, int> > sumMap;

        int prefixSum = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            prefixSum += it->first * it->second;
            sumMap[it->first] = {prefixSum, INT_MIN};
        }

        int suffixSum = 0;
        for (auto it = freqMap.rbegin(); it != freqMap.rend(); it++) {
            suffixSum += it->first * it->second;
            sumMap[it->first].second = suffixSum;
        }

        return sumMap;
    }

    pair<int, int> findNumLowerAndHigherVals(int totalFreq, map<int, int>& cumFreqMap, map<int, int>::iterator it) {
        int numLowerEles = 0;
        if (it != cumFreqMap.begin()) {
            it--;
            numLowerEles = it->second;
            it++;
        }

        int numGreaterEles = 0;
        if (it != cumFreqMap.end()) {
            numGreaterEles = totalFreq - it->second;
        }

        return {numLowerEles, numGreaterEles};
    }

    pair<int, int>
    findSumLowerAndHigherVals(map<int, pair<int, int> >& sumMap, map<int, pair<int, int> >::iterator it) {
        int sumLowerEles = 0;
        if (it != sumMap.begin()) {
            it--;
            sumLowerEles = it->second.first;
            it++;
        }

        int sumGreaterEles = 0;
        map<int, pair<int, int> >::iterator lastIt = sumMap.end();
        lastIt--;
        if (it != lastIt) {
            it++;
            sumGreaterEles = it->second.second;
            it--;
        }

        return {sumLowerEles, sumGreaterEles};
    }

public:
    friend class SolutionTest;

    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) {
            return {};
        }

        map<int, int> freqMap = buildFreqMap(nums);

        map<int, int> cumFreqMap = convertToCumFreqMap(freqMap);
        map<int, pair<int, int> > sumMap = convertToSumMap(freqMap);

        vector<int> absDiffVec(len);
        for (int i = 0; i < nums.size(); i++) {
            int crrEle = nums[i];

            auto it1 = cumFreqMap.lower_bound(crrEle);
            auto it2 = sumMap.lower_bound(crrEle);

            pair<int, int> numLowerHigherVals = findNumLowerAndHigherVals(len, cumFreqMap, it1);
            pair<int, int> sumLowerHigherVals = findSumLowerAndHigherVals(sumMap, it2);

            int lowerDiffAbsSum = (crrEle * numLowerHigherVals.first) - sumLowerHigherVals.first;
            int higherDiffAbsSum = sumLowerHigherVals.second - (crrEle * numLowerHigherVals.second);
            absDiffVec[i] = abs(lowerDiffAbsSum + higherDiffAbsSum);

            if (debug) {
                printf("\n----at nums[i=%d] = %d----\n", i, crrEle);
                printf("diffLowerVals  = {(crrEle=%d x numLowerVals=%d) - sumLowerVals=%d} = %d\n", crrEle,
                       numLowerHigherVals.first, sumLowerHigherVals.first, lowerDiffAbsSum);
                printf("diffHigherVals = {sumHigherVals=%d - (crrEle=%d x numHigherVals=%d)} = %d\n",
                       sumLowerHigherVals.second, crrEle, numLowerHigherVals.second, higherDiffAbsSum);
                printf("res = diffLowerVals=%d + diffHigherVals=%d = %d\n", lowerDiffAbsSum, higherDiffAbsSum,
                       absDiffVec[i]);
            }
        }

        return absDiffVec;
    }
};

class SolutionTest {
public:
    void testGetSumAbsoluteDifferences() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected;
        vector<int> vecOutComputed;

        vecIn = {2, 3, 5};
        vecOutExpected = {4, 3, 5};
        vecOutComputed = soln.getSumAbsoluteDifferences(vecIn);
        assert(vecOutExpected == vecOutComputed);

//        soln.debug = true;
        vecIn = {1, 4, 6, 8, 10};
        vecOutExpected = {24, 15, 13, 15, 21};
        vecOutComputed = soln.getSumAbsoluteDifferences(vecIn);
        assert(vecOutExpected == vecOutComputed);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testGetSumAbsoluteDifferences();

    return 0;
}
