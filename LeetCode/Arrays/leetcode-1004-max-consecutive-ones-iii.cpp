// LC-1004: https://leetcode.com/problems/max-consecutive-ones-iii/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void setDebug(bool debug) {
        this->debug = debug;
    }

    vector<int> calcPrefix1sCount(vector<int>& vec) {
        int len = vec.size();
        vector<int> prefix1sCount(len, 0);

        int crrPref1s = 0;
        for (int i = 0; i < len; i++) {
            if (vec[i] == 1) {
                crrPref1s++;
            } else {
                crrPref1s = 0;
            }

            prefix1sCount[i] = crrPref1s;
        }

        return prefix1sCount;
    }

    vector<int> calcSuffix1sCount(vector<int>& vec) {
        int len = vec.size();
        vector<int> suffix1sCount(len, 0);

        int crrSuff1s = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (vec[i] == 1) {
                crrSuff1s++;
            } else {
                crrSuff1s = 0;
            }

            suffix1sCount[i] = crrSuff1s;
        }

        return suffix1sCount;
    }

    int count0s(vector<int>& vec) {
        int len = vec.size();

        int num0s = 0;
        for (int i = 0; i < len; i++) {
            if (vec[i] == 0) {
                num0s++;
            }
        }

        return num0s;
    }

    vector<int> find0Inds(vector<int>& vec) {
        int num0s = count0s(vec);
        if (num0s == 0) {
            return {};
        }

        vector<int> zeroInds(num0s);
        int k = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == 0) {
                zeroInds[k++] = i;
            }
        }

        return zeroInds;
    }

    int findKth0FromLeftInd(vector<int>& vec, int k) {
        int len = vec.size();
        if (k > len) {
            return len;
        }
        if (k == 0) {
            return 0;
        }

        int numZeroes = 0;
        int i = 0;
        while ((i < len) && (numZeroes < k)) {
            if (vec[i] == 0) {
                numZeroes++;
            }

            i++;
        }

        // printf("len=%d, k=%d, numZeroes=%d, i=%d\n", len, k, numZeroes, i);
        if (numZeroes == k) {
            return i - 1;
        } else {
            return len;
        }
    }

    int findNumConseq1sLeftOf(vector<int>& prefix1sCount, int idx) {
        int leftIdx = idx - 1;
        if (leftIdx < 0) {
            return 0;
        }

        return prefix1sCount[leftIdx];
    }

    int findNumConseq1sRightOf(vector<int>& suffix1sCount, int idx) {
        int rightIdx = idx + 1;
        if (rightIdx >= ((int)suffix1sCount.size())) {
            return 0;
        }

        return suffix1sCount[rightIdx];
    }

   public:
    friend class SolutionTest;

    int longestOnes(vector<int>& nums, int k) {
        int len = nums.size();
        if (k >= len) {
            return len;
        }

        vector<int> zeroInds = find0Inds(nums);
        int numZeroes = zeroInds.size();
        if (zeroInds.empty() || (((int)zeroInds.size()) <= k)) {
            return len;
        }

        vector<int> prefix1sCount = calcPrefix1sCount(nums);
        vector<int> suffix1sCount = calcSuffix1sCount(nums);
        if (k == 0) {
            return *max_element(prefix1sCount.begin(), prefix1sCount.end());
        }

        int maxConseq1s = 0;
        for (int i = 0; i < numZeroes; i++) {
            int winLo = i;
            int winHi = i + k - 1;

            if (winHi >= numZeroes) {
                break;
            }

            int crrConseq1s = findNumConseq1sLeftOf(prefix1sCount, zeroInds[winLo]) + (zeroInds[winHi] - zeroInds[winLo] + 1) + findNumConseq1sRightOf(suffix1sCount, zeroInds[winHi]);
            if (this->debug) {
                printf("at i=%d, window [%d]=%d .. [%d]=%d, left1s=%d, window1s=%d, right1s=%d\n", i, winLo, zeroInds[winLo], winHi, zeroInds[winHi], findNumConseq1sLeftOf(prefix1sCount, zeroInds[winLo]), (zeroInds[winHi] - zeroInds[winLo] + 1), findNumConseq1sRightOf(suffix1sCount, zeroInds[winHi]));
            }
            maxConseq1s = max(maxConseq1s, crrConseq1s);
        }

        return maxConseq1s;
    }
};

class SolutionTest {
   public:
    void testCalcPrefix1sCount() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected;
        vector<int> vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0};
        vecOutExpected = {0};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1};
        vecOutExpected = {1};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 1};
        vecOutExpected = {0, 1};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 0};
        vecOutExpected = {1, 0};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 1, 1};
        vecOutExpected = {0, 1, 2};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 1, 0};
        vecOutExpected = {1, 2, 0};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 1, 0, 1};
        vecOutExpected = {1, 2, 0, 1};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 0, 1, 1};
        vecOutExpected = {1, 0, 1, 2};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 1, 1, 0, 1, 1, 0, 1, 0};
        vecOutExpected = {1, 2, 3, 0, 1, 2, 0, 1, 0};
        vecOutComputed = soln.calcPrefix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }

    void testCalcSuffix1sCount() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected;
        vector<int> vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0};
        vecOutExpected = {0};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1};
        vecOutExpected = {1};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 1};
        vecOutExpected = {0, 1};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 0};
        vecOutExpected = {1, 0};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 1, 1};
        vecOutExpected = {0, 2, 1};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 1, 0};
        vecOutExpected = {2, 1, 0};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 1, 0, 1};
        vecOutExpected = {2, 1, 0, 1};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 0, 1, 1};
        vecOutExpected = {1, 0, 2, 1};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 1, 1, 0, 1, 1, 0, 1, 0};
        vecOutExpected = {3, 2, 1, 0, 2, 1, 0, 1, 0};
        vecOutComputed = soln.calcSuffix1sCount(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }

    void testFindKth0FromLeftInd() {
        Solution soln = Solution();
        vector<int> vec;
        int k;
        int outExpected;
        int outComputed;

        vec = {};
        k = 0;
        outExpected = 0;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {};
        k = 4;
        outExpected = 0;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0};
        k = 0;
        outExpected = 0;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0};
        k = 1;
        outExpected = 0;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        // printf("expected=%d, computed=%d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vec = {0};
        k = 2;
        outExpected = 1;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 1};
        k = 2;
        outExpected = 2;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 1, 0};
        k = 2;
        outExpected = 2;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 1, 0, 0};
        k = 2;
        outExpected = 2;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 1, 0, 0};
        k = 3;
        outExpected = 3;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 0, 1, 0};
        k = 2;
        outExpected = 1;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 0, 1, 0};
        k = 3;
        outExpected = 3;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);

        vec = {0, 0, 0, 1};
        k = 3;
        outExpected = 2;
        outComputed = soln.findKth0FromLeftInd(vec, k);
        assert(outExpected == outComputed);
    }

    void testFind0Inds() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected;
        vector<int> vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1};
        vecOutExpected = {};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 1};
        vecOutExpected = {0};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 0};
        vecOutExpected = {1};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {1, 0, 1};
        vecOutExpected = {1};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 1, 0};
        vecOutExpected = {0, 2};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {0, 0};
        vecOutExpected = {0, 1};
        vecOutComputed = soln.find0Inds(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }

    void testLongestOnes() {
        Solution soln = Solution();
        vector<int> vec;
        int k;
        int outExpected;
        int outComputed;

        vec = {};
        k = 4;
        outExpected = 0;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1};
        k = 4;
        outExpected = 1;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 0};
        k = 4;
        outExpected = 2;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 0, 1};
        k = 0;
        outExpected = 1;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 0, 1};
        k = 1;
        outExpected = 3;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0};
        k = 0;
        outExpected = 2;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0};
        k = 1;
        outExpected = 3;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0};
        k = 2;
        outExpected = 3;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1};
        k = 1;
        outExpected = 4;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1, 0, 0, 1};
        k = 2;
        outExpected = 5;
        // soln.setDebug(true);
        outComputed = soln.longestOnes(vec, k);
        // soln.setDebug(false);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1, 0, 0, 1};
        k = 3;
        outExpected = 7;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1, 0, 0, 1, 1, 1};
        k = 1;
        outExpected = 4;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1, 0, 0, 1, 1, 1};
        k = 2;
        outExpected = 6;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1, 0, 0, 1, 1, 1};
        k = 3;
        outExpected = 9;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);

        vec = {1, 1, 0, 1, 0, 0, 1, 1, 1};
        k = 4;
        outExpected = 9;
        outComputed = soln.longestOnes(vec, k);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcPrefix1sCount();
    solnTest.testCalcSuffix1sCount();
    solnTest.testFindKth0FromLeftInd();
    solnTest.testFind0Inds();
    solnTest.testLongestOnes();

    return 0;
}
