// LeetCode-1838: https://leetcode.com/problems/frequency-of-the-most-frequent-element/

/**
 * input
 * [1,2,4]
 * 5
 * output
 * 3
 *
 * input
 * [1,4,8,13]
 * 5
 * output
 * 2
 *
 * input
 * [3,9,6]
 * 2
 * output
 * 1
 *
 * input
 * [9940,9995,9944,9937,9941,9952,9907,9952,9987,9964,9940,9914,9941,9933,9912,9934,9980,9907,9980,9944,9910,9997]
 * 7925
 * output
 * 22
 *
 * input
 * [40,95,44,37,41,52,7,52,87,64,40,14,41,33,12,34,80,7,80,44,10,97]
 * 25
 * output
 * 7
 */

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   private:
    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    set<int> buildSet(vector<int>& vec) {
        set<int> mSet(vec.begin(), vec.end());
        return mSet;
    }

    int findJustGreaterEle(set<int>& mSet, int ele) {
        if (mSet.empty()) {
            return INT_MIN;
        }

        set<int>::iterator it = mSet.upper_bound(ele);

        if (it == mSet.end()) {
            return INT_MIN;
        } else {
            return *it;
        }
    }

    int findNumElesElapsedBetween(vector<int>& freqPrefixSumVec, int eleLoExc, int eleHiInc) {
        int len = freqPrefixSumVec.size();
        return freqPrefixSumVec[min(eleHiInc, len - 1)] - freqPrefixSumVec[max(0, eleLoExc)];
    }

    vector<int> buildFreqVec(vector<int>& vec) {
        int maxEle = *max_element(vec.begin(), vec.end());

        vector<int> freqVec(maxEle + 1);
        for (int i = 0; i < vec.size(); i++) {
            freqVec[vec[i]]++;
        }

        return freqVec;
    }

    vector<int> buildPrefixSumVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefixSumVec(len);
        prefixSumVec[0] = vec[0];

        for (int i = 1; i < len; i++) {
            prefixSumVec[i] += prefixSumVec[i - 1] + vec[i];
        }

        return prefixSumVec;
    }

    vector<int> buildCumSumVec(vector<int>& freqVec) {
        int len = freqVec.size();

        vector<int> cumSumVec(len);
        for (int i = 1; i < len; i++) {
            cumSumVec[i] = cumSumVec[i - 1] + (i * freqVec[i]);
        }

        return cumSumVec;
    }

    int binSearchMaxPositiveConsumedEle(
        vector<int>& cumSumVec,
        int k,
        int baseVal,
        int lo,
        int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return INT_MIN;
        }

        int mid = (hi + lo) / 2;
        int midVal = cumSumVec[mid];

        int consumedElesCost = midVal - baseVal;
        int diff = k - consumedElesCost;

        if (diff < 0) {
            return binSearchMaxPositiveConsumedEle(cumSumVec, k, baseVal, lo, mid - 1);
        } else if (diff == 0) {
            return mid;
        } else {
            return max(mid, binSearchMaxPositiveConsumedEle(cumSumVec, k, baseVal, mid + 1, hi));
        }
    }

    int findMaxPossibleFreq(
        int k,
        set<int>& mSet,
        vector<int>& freqVec,
        vector<int>& freqPrefixSumVec,
        vector<int>& cumSumVec) {
        int len = freqVec.size();

        int maxFreq = 1;
        for (int i = 0; i < len; i++) {
            bool eleExists = freqVec[i] > 0;
            if (!eleExists) {
                continue;
            }

            int crrEle = i;
            int crrEleFreq = freqVec[crrEle];

            int maxInd = binSearchMaxPositiveConsumedEle(
                cumSumVec,
                k,
                ((i == 0) ? 0 : cumSumVec[i - 1]),
                crrEle + 1,
                len - 1);

            int newFreq = 0;
            if (maxInd == INT_MIN) {
                int nextEle = findJustGreaterEle(mSet, crrEle);
                if (nextEle == INT_MIN) {
                    continue;
                }

                int numElesTransformed = k / (nextEle - crrEle);
                newFreq = crrEleFreq + numElesTransformed;
            } else {
                int numElesCompletelyTransformed = findNumElesElapsedBetween(
                    freqPrefixSumVec,
                    crrEle,
                    maxInd);
                int sumConsumedInCompletelyTransformedEles = cumSumVec[maxInd] - cumSumVec[crrEle];
                int remSum = k - sumConsumedInCompletelyTransformedEles;

                int nextEle = findJustGreaterEle(mSet, maxInd);
                int numElesPartiallyTransformed = remSum / (nextEle - crrEle);

                newFreq = crrEleFreq + numElesCompletelyTransformed + numElesPartiallyTransformed;
            }

            maxFreq = max(maxFreq, newFreq);
        }

        return maxFreq;
    }

   public:
    friend class SolutionTest;

    int maxFrequency(vector<int>& nums, int k) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        set<int> mSet = buildSet(nums);
        vector<int> freqVec = buildFreqVec(nums);
        vector<int> freqPrefixSumVec = buildPrefixSumVec(freqVec);
        vector<int> cumSumVec = buildCumSumVec(freqVec);

        return findMaxPossibleFreq(
            k,
            mSet,
            freqVec,
            freqPrefixSumVec,
            cumSumVec);
    }
};

class SolutionTest {
   public:
    void testFindJustGreaterEle() {
        Solution soln = Solution();
        set<int> mSet;
        int eleIn;
        int outExpected, outComputed;

        mSet = {};
        eleIn = 5;
        outExpected = INT_MIN;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        mSet = {4};
        eleIn = 5;
        outExpected = INT_MIN;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        mSet = {5};
        eleIn = 5;
        outExpected = INT_MIN;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        mSet = {5, 9};
        eleIn = 5;
        outExpected = 9;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        mSet = {1, 3, 8, 9};

        eleIn = 1;
        outExpected = 3;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        eleIn = 2;
        outExpected = 3;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        eleIn = 3;
        outExpected = 8;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        eleIn = 5;
        outExpected = 8;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        eleIn = 8;
        outExpected = 9;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);

        eleIn = 9;
        outExpected = INT_MIN;
        outComputed = soln.findJustGreaterEle(mSet, eleIn);
        assert(outExpected == outComputed);
    }

    void testFindNumElesElapsedBetween() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> freqVecExpected;
        vector<int> freqVecComputed;
        vector<int> freqPrefixSumVecExpected;
        vector<int> freqPrefixSumVecComputed;
        int eleLoExc, eleHiInc;
        int numElesElapsedExpected, numElesElapsedComputed;

        vecIn = {0, 1, 3, 2, 1, 3, 5, 3, 7, 1};

        freqVecExpected = {1, 3, 1, 3, 0, 1, 0, 1};
        freqVecComputed = soln.buildFreqVec(vecIn);
        // soln.showVec(freqVecComputed, "freqVecComputed");
        assert(freqVecExpected == freqVecComputed);

        freqPrefixSumVecExpected = {1, 4, 5, 8, 8, 9, 9, 10};
        freqPrefixSumVecComputed = soln.buildPrefixSumVec(freqVecComputed);
        assert(freqPrefixSumVecExpected == freqPrefixSumVecComputed);

        eleLoExc = 0;
        eleHiInc = 5;
        numElesElapsedExpected = 8;
        numElesElapsedComputed = soln.findNumElesElapsedBetween(freqPrefixSumVecComputed, eleLoExc, eleHiInc);
        assert(numElesElapsedExpected == numElesElapsedComputed);

        eleLoExc = 0;
        eleHiInc = 6;
        numElesElapsedExpected = 8;
        numElesElapsedComputed = soln.findNumElesElapsedBetween(freqPrefixSumVecComputed, eleLoExc, eleHiInc);
        assert(numElesElapsedExpected == numElesElapsedComputed);

        eleLoExc = 3;
        eleHiInc = 5;
        numElesElapsedExpected = 1;
        numElesElapsedComputed = soln.findNumElesElapsedBetween(freqPrefixSumVecComputed, eleLoExc, eleHiInc);
        assert(numElesElapsedExpected == numElesElapsedComputed);

        eleLoExc = 3;
        eleHiInc = 9;
        numElesElapsedExpected = 2;
        numElesElapsedComputed = soln.findNumElesElapsedBetween(freqPrefixSumVecComputed, eleLoExc, eleHiInc);
        assert(numElesElapsedExpected == numElesElapsedComputed);
    }

    void testBuildCumSumVec() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> freqVecExpected;
        vector<int> freqVecComputed;
        vector<int> cumSumVecExpected;
        vector<int> cumSumVecComputed;

        vecIn = {0, 1, 3, 2, 1, 3, 5, 3, 7, 1};

        freqVecExpected = {1, 3, 1, 3, 0, 1, 0, 1};
        freqVecComputed = soln.buildFreqVec(vecIn);
        // soln.showVec(freqVecComputed, "freqVecComputed");
        assert(freqVecExpected == freqVecComputed);

        cumSumVecExpected = {0, 3, 5, 14, 14, 19, 19, 26};
        cumSumVecComputed = soln.buildCumSumVec(freqVecComputed);
        assert(cumSumVecExpected == cumSumVecComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindJustGreaterEle();
    solnTest.testFindNumElesElapsedBetween();
    solnTest.testBuildCumSumVec();

    return 0;
}
