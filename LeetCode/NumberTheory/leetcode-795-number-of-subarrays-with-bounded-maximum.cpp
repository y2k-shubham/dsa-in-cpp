// LeetCode-795: https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/

// approach seems to be correct and optimal
// unable to understand the last test case (check test-cases) which is failing

#include <vector>
#include <stack>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    bool debug = false;

    vector<int> buildNgeLeftIdxVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {-1};
        }

        vector<int> ngeLeftIdxVec(len, -1);
        stack<int> stk;

        for (int i = 0; i < len; i++) {
            int crrEle = vec[i];

            while (!stk.empty() && (vec[stk.top()] < crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeLeftIdxVec[i] = stk.top();
            }
            stk.push(i);
        }

        return ngeLeftIdxVec;
    }

    vector<int> buildNgeRightIdxVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {len};
        }

        vector<int> ngeRightIdxVec(len, len);
        stack<int> stk;

        for (int i = len - 1; i >= 0; i--) {
            int crrEle = vec[i];

            while (!stk.empty() && (vec[stk.top()] <= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeRightIdxVec[i] = stk.top();
            }
            stk.push(i);
        }

        return ngeRightIdxVec;
    }

    long long gcd(long long big, long long small) {
        if (big < small) {
            return gcd(small, big);
        }

        long long rem = big % small;
        if (rem == 0) {
            return small;
        } else {
            return gcd(small, rem);
        }
    }

    int nCr(int n, int r) {
        r = min(r, n - r);

        long long numr = 1;
        long long denr = 1;
        while (r >= 1) {
            numr *= n;
            denr *= r;

            long long hcf = gcd(numr, denr);
            numr /= hcf;
            denr /= hcf;

            n--;
            r--;
        }

        return (int) (numr / denr);
    }

    int calcNumSubarrsWithThisEleMax(
            vector<int>& ngeLeftIdxVec,
            vector<int>& ngeRightIdxVec,
            int idx
    ) {
        int ngeLeftIdx = ngeLeftIdxVec[idx];
        int ngeRightIdx = ngeRightIdxVec[idx];

        int subarrLen = ngeRightIdx - ngeLeftIdx - 1;
        return subarrLen;
    }

public:
    friend class SolutionTest;

    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int len = nums.size();

        if (left > right) {
            int tmp = left;
            left = right;
            right = tmp;
        }

        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return ((left <= nums[0]) && (nums[0] <= right)) ? 1 : 0;
        }

        vector<int> ngeLeftIdxVec = buildNgeLeftIdxVec(nums);
        vector<int> ngeRightIdxVec = buildNgeRightIdxVec(nums);

        int numSubarrs = 0;
        for (int i = 0; i < len; i++) {
            int crrEle = nums[i];
            bool isInRange = (left <= crrEle) && (crrEle <= right);

            if (isInRange) {
                if (debug) {
                    printf("for vec[%d]=%d, ", i, crrEle);
                    if (ngeLeftIdxVec[i] >= 0) {
                        printf("ngeLeft=vec[%d]=%d, ", ngeLeftIdxVec[i], nums[ngeLeftIdxVec[i]]);
                    } else {
                        printf("ngeLeft= -\t, ");
                    }
                    if (ngeRightIdxVec[i] < len) {
                        printf("ngeRight=vec[%d]=%d, ", ngeRightIdxVec[i], nums[ngeRightIdxVec[i]]);
                    } else {
                        printf("ngeRight= -\t, ");
                    }
                    printf("contrib=%d\n", calcNumSubarrsWithThisEleMax(ngeLeftIdxVec, ngeRightIdxVec, i));
                }

                numSubarrs += calcNumSubarrsWithThisEleMax(ngeLeftIdxVec, ngeRightIdxVec, i);
            } else {
                if (debug) {
                    printf("for vec[%d]=%d, skipping as it is outside range [left=%d, right=%d]\n", i, crrEle, left,
                           right);
                }
            }
        }

        return numSubarrs;
    }
};

class SolutionTest {
public:
    void testNumSubarrayBoundedMax() {
        Solution soln = Solution();
        vector<int> vecIn;
        int leftIn, rightIn;
        int outExpected, outComputed;

        vecIn = {};
        leftIn = 5;
        rightIn = 14;
        outExpected = 0;
        outComputed = soln.numSubarrayBoundedMax(vecIn, leftIn, rightIn);
        assert(outExpected == outComputed);

//        soln.debug = true;
        vecIn = {13};
        leftIn = 5;
        rightIn = 14;
        outExpected = 1;
        outComputed = soln.numSubarrayBoundedMax(vecIn, leftIn, rightIn);
        assert(outExpected == outComputed);
//        soln.debug = false;

        vecIn = {2, 1, 4, 3};
        leftIn = 2;
        rightIn = 3;
        outExpected = 3;
        outComputed = soln.numSubarrayBoundedMax(vecIn, leftIn, rightIn);
        assert(outExpected == outComputed);

        vecIn = {2, 9, 2, 5, 6};
        leftIn = 2;
        rightIn = 8;
        outExpected = 7;
        outComputed = soln.numSubarrayBoundedMax(vecIn, leftIn, rightIn);
        assert(outExpected == outComputed);

        soln.debug = true;
        vecIn = {73, 55, 36, 5, 55, 14, 9, 7, 72, 52};
        leftIn = 32;
        rightIn = 69;
        outExpected = 22;
        outComputed = soln.numSubarrayBoundedMax(vecIn, leftIn, rightIn);
        assert(outExpected == outComputed);
        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testNumSubarrayBoundedMax();

    return 0;
}
