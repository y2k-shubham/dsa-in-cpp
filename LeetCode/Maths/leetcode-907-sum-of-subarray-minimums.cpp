// LeetCode-907: https://leetcode.com/problems/sum-of-subarray-minimums/

/**
 * elegant problem
 * 
 * here's the solution right away
 * 1a. determine indexes of next (strictly) lesser element on left
 * 1b. determine indexes of next lesser (or equal) element on right
 * 2. let's  say the current element 'ele' at index 'idx' has lesser elements to it's left and right like this
 *    [ ... nle-left ... ele ... nle-right ... ]
 *    now 'ele' will be included in our sum for each subarray which has
 *    - starting index b/w ( nle-left .. idx] and
 *    - ending index b/w [idx .. nle-right )
 *    so each element will be included in the sum (idx - nle-left) x (nle-right - idx) times
 * 3. point: edge-case (already factored in above soln) is when a single element
 *    is repeated; like in e.g. [71, 55, 82, 55]
 *    - here the first 55 will be included in 5 subarrays
 *    - whereas the second 55 will only be included in 2 subarrays (cannot be included in 3 -> that would be double-counting)
 *    to overcome double-counting, in step 1a. we determined nle-left by taking strictly lesser elements only
 *    (and vice-versa for nle-right by taking less-than-or-equal elements)
 */

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    bool debug = false;

    void showVec(vector<int>& nleRightIdxVec, vector<int>& valVec) {
        int len = nleRightIdxVec.size();

        printf("Idx:\t\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", valVec[i]);
        }
        cout << endl;

        printf("Nle-Idx:\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", nleRightIdxVec[i]);
        }
        cout << endl;

        printf("Nle-Val:\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", ((nleRightIdxVec[i] < len) ? valVec[nleRightIdxVec[i]] : -1));
        }
        cout << endl;
    }

    vector<int> buildNleLeftVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> nleRightVec(len, -1);

        stack<int> stk;
        for (int i = 0; i < len; i++) {
            int crrEle = vec[i];
            // note that here we DONT take equality
            while (!stk.empty() && (vec[stk.top()] > crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleRightVec[i] = stk.top();
            }

            stk.push(i);
        }

        return nleRightVec;
    }

    vector<int> buildNleRightVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> nleRightVec(len, len);

        stack<int> stk;
        for (int i = len - 1; i >= 0; i--) {
            int crrEle = vec[i];
            // note that here we DO take equality
            while (!stk.empty() && (vec[stk.top()] >= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleRightVec[i] = stk.top();
            }

            stk.push(i);
        }

        return nleRightVec;
    }

    int findSubarrsMinSum(
        vector<int>& vec,
        vector<int>& nleLeftVec,
        vector<int>& nleRightVec) {
        int len = vec.size();

        int sum = 0;
        for (int i = 0; i < len; i++) {
            int crrEleVal = vec[i];

            int nleLeftIdx = nleLeftVec[i];
            // if ((nleLeftIdx >= 0) && (vec[nleLeftIdx] == crrEleVal)) {
            //     nleLeftIdx++;
            // }
            int nleRightIdx = nleRightVec[i];

            int numSubarrs = (i - nleLeftIdx) * (nleRightIdx - i);
            int crrEleSumContrib = (int) ((numSubarrs * ((long long) crrEleVal)) % MOD);

            if (this->debug) {
                printf(
                    "at vec[i=%d]=%d, nleLIdx=%d, nleRIdx=%d, numSubarrs=%d, contrib=%d\n",
                    i,
                    crrEleVal,
                    nleLeftIdx,
                    nleRightIdx,
                    numSubarrs,
                    crrEleSumContrib);
            }

            sum += crrEleSumContrib;
            sum %= MOD;
        }

        return sum;
    }

   public:
    friend class SolutionTest;

    int sumSubarrayMins(vector<int>& arr) {
        int len = arr.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return arr[0];
        }

        vector<int> nleLeftVec = buildNleLeftVec(arr);
        vector<int> nleRightVec = buildNleRightVec(arr);
        // showVec(nleRightVec, arr);

        return findSubarrsMinSum(arr, nleLeftVec, nleRightVec);
    }
};

class SolutionTest {
   public:
    void testFindSubarrsMinSum() {
        Solution soln = Solution();
        vector<int> vecIn;
        int sumOutExpected, sumOutComputed;

        vecIn = {};
        sumOutExpected = 0;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {5};
        sumOutExpected = 5;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {9, 19};
        sumOutExpected = 37;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {3, 1, 2, 4};
        sumOutExpected = 17;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);

        vecIn = {11, 81, 94, 43, 3};
        sumOutExpected = 444;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);

        // soln.debug = true;
        vecIn = {71, 55, 82, 55};
        sumOutExpected = 593;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);
        // soln.debug = false;

        vecIn = {5, 5, 3, 1, 1, 1, 9, 8, 2};
        sumOutExpected = 88;
        sumOutComputed = soln.sumSubarrayMins(vecIn);
        assert(sumOutExpected == sumOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindSubarrsMinSum();

    return 0;
}
