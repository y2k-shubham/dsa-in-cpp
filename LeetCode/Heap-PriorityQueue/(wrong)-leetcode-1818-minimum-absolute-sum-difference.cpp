// LeetCode-1818: https://leetcode.com/problems/minimum-absolute-sum-difference/
/**
 * approach is correct as explained by Cherry Coding: https://www.youtube.com/watch?v=cMWnXLnY93c
 * - but somehow iterators of (ordered) set are messing up things
 * - so will have to implement binary-search for 'closest element in arr' manually
 */

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    bool debug = false;

    unordered_set<int> createUnorderedSet(vector<int>& vec) {
        unordered_set<int> mSet(vec.begin(), vec.end());
        return mSet;
    }

    set<int> createOrderedSet(vector<int>& vec) {
        set<int> mSet(vec.begin(), vec.end());
        return mSet;
    }

    pair<int, priority_queue<pair<int, int>>> createDiffHeap(vector<int>& vec1, vector<int>& vec2) {
        int diffSum = 0;

        priority_queue<pair<int, int>> heap;
        for (int i = 0; i < vec1.size(); i++) {
            int diff = abs(vec1[i] - vec2[i]);
            if (diff == 0) {
                continue;
            }

            diffSum += diff;
            diffSum %= MOD;

            heap.push({diff, i});
        }

        return {diffSum, heap};
    }

    int findMaxGain(
        vector<int>& nums1,
        vector<int>& nums2,
        unordered_set<int>& mUnorderedSet,
        set<int>& mOrderedSet,
        priority_queue<pair<int, int>>& diffHeap) {
        int len = nums1.size();
        if (len <= 0) {
            return 0;
        }

        int dipMax = INT_MIN;
        int dipMaxIdx = -1;
        int dipMaxRepl = -1;
        int iter = 0;
        while (!diffHeap.empty() && ((dipMax == INT_MIN) || (diffHeap.top().first > dipMax))) {
            int diffOrg = diffHeap.top().first;
            int idx = diffHeap.top().second;
            diffHeap.pop();

            if (debug) {
                printf("iter=%d, idx=%d, nums1[idx]=%d, nums2[idx]=%d, diff=%d\n", iter, idx, nums1[idx], nums2[idx], diffOrg);
            }

            int val1 = nums1[idx];
            int val2 = nums2[idx];

            // check if diff can be made zero (val2 should exist in nums1)
            if (mUnorderedSet.find(val2) != mUnorderedSet.end()) {
                dipMax = diffOrg;
                break;
            }

            // check how much can be minimize the diff
            // find the element(s) closest to val2 that are present in nums1
            set<int>::iterator it = mOrderedSet.lower_bound(val2);
            int gain = INT_MIN;
            int dipRepl = -1;

            if (debug) {
                printf("here1\n");
            }

            // find element greater than val2
            if (it != mOrderedSet.end()) {
                dipRepl = *it;
                int diffHi = abs(val2 - *it);
                if (diffHi < diffOrg) {
                    gain = max(gain, diffOrg - diffHi);
                    if (debug) {
                        printf("idx=%d, nums1[idx]=%d, nums2[idx]=%d, diffOrg=%d, diffHi=%d, gain=%d\n", idx, nums1[idx], nums2[idx], diffOrg, diffHi, gain);
                    }
                }
            }

            if (debug) {
                printf("here2 it=%d\n", *it);
                printf("here2 itPos=%d it=%d\n", (int)distance(mOrderedSet.begin(), it), *it);
            }

            // find element smaller than val2
            it--;
            int diffLo = abs(val2 - *it);
            if (diffLo < diffOrg) {
                dipRepl = *it;
                gain = max(gain, diffOrg - diffLo);
                if (debug) {
                    printf("idx=%d, nums1[idx]=%d, nums2[idx]=%d, diffOrg=%d, diffLo=%d, gain=%d\n", idx, nums1[idx], nums2[idx], diffOrg, diffLo, gain);
                }
            }

            if (debug) {
                printf("here3\n");
            }

            if ((gain != INT_MIN) && (gain > dipMax)) {
                dipMax = gain;
                dipMaxIdx = idx;
                dipMaxRepl = dipRepl;
            }

            iter++;
        }

        if (debug) {
            printf("replacement idx=%d, nums1[idx]=%d, nums2[idx]=%d, repl=%d\n", dipMaxIdx, nums1[dipMaxIdx], nums2[dipMaxIdx], dipMaxRepl);
        }
        return max(dipMax, 0);
    }

   public:
    friend class SolutionTest;
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int len = nums1.size();
        if (len == 0) {
            return 0;
        }

        pair<int, priority_queue<pair<int, int>>> diffsResponse = createDiffHeap(nums1, nums2);
        int orgDiffSum = diffsResponse.first;
        priority_queue<pair<int, int>> diffHeap = diffsResponse.second;

        if ((len == 1) || (orgDiffSum == 0)) {
            return orgDiffSum;
        }

        unordered_set<int> mUnorderedSet = createUnorderedSet(nums1);
        set<int> mOrderedSet = createOrderedSet(nums1);

        int dipMax = findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        int reducedDiffSum = (orgDiffSum - dipMax) % MOD;

        return reducedDiffSum;
    }
};

class SolutionTest {
   public:
    void testFindMaxGain() {
        Solution soln = Solution();
        vector<int> nums1, nums2;
        unordered_set<int> mUnorderedSet;
        set<int> mOrderedSet;
        priority_queue<pair<int, int>> diffHeap;
        int outExpected, outComputed;

        nums1 = {};
        nums2 = {};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 0;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {3};
        nums2 = {4};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 0;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {3, 5};
        nums2 = {4, 9};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 0;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {6, 5};
        nums2 = {4, 9};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 1;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {6, 5};
        nums2 = {3, 11};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 1;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        soln.debug = true;
        nums1 = {150, 100};
        nums2 = {90, 10};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 50;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);
        soln.debug = false;

        nums1 = {2, 0};
        nums2 = {2, 3};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 2;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {2, 4};
        nums2 = {2, 2};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 2;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {1, 7, 5};
        nums2 = {2, 3, 5};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 2;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);

        nums1 = {1, 10, 4, 4, 2, 7};
        nums2 = {9, 3, 5, 1, 7, 4};
        mUnorderedSet = soln.createUnorderedSet(nums1);
        mOrderedSet = soln.createOrderedSet(nums1);
        diffHeap = soln.createDiffHeap(nums1, nums2).second;
        outExpected = 7;
        outComputed = soln.findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        assert(outExpected == outComputed);
    }

    void testMinAbsoluteSumDiff() {
        Solution soln;
        vector<int> nums1, nums2;
        int outExpected, outComputed;

        nums1 = {};
        nums2 = {};
        outExpected = 0;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);

        nums1 = {2, 3};
        nums2 = {2, 3};
        outExpected = 0;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);

        nums1 = {150, 100};
        nums2 = {90, 10};
        outExpected = 100;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);

        nums1 = {1, 7, 5};
        nums2 = {2, 3, 5};
        outExpected = 3;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);

        nums1 = {2, 4, 6, 8, 10};
        nums2 = {2, 4, 6, 8, 10};
        outExpected = 0;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);

        nums1 = {1, 10, 4, 4, 2, 7};
        nums2 = {9, 3, 5, 1, 7, 4};
        outExpected = 20;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);

        // soln.debug = true;
        nums1 = {38, 48, 73, 55, 25, 47, 45, 62, 15, 34, 51, 20, 76, 78, 38, 91, 69, 69, 73, 38, 74, 75, 86, 63, 73, 12, 100, 59, 29, 28, 94, 43, 100, 2, 53, 31, 73, 82, 70, 94, 2, 38, 50, 67, 8, 40, 88, 87, 62, 90, 86, 33, 86, 26, 84, 52, 63, 80, 56, 56, 56, 47, 12, 50, 12, 59, 52, 7, 40, 16, 53, 61, 76, 22, 87, 75, 14, 63, 96, 56, 65, 16, 70, 83, 51, 44, 13, 14, 80, 28, 82, 2, 5, 57, 77, 64, 58, 85, 33, 24};
        nums2 = {90, 62, 8, 56, 33, 22, 9, 58, 29, 88, 10, 66, 48, 79, 44, 50, 71, 2, 3, 100, 88, 16, 24, 28, 50, 41, 65, 59, 83, 79, 80, 91, 1, 62, 13, 37, 86, 53, 43, 49, 17, 82, 27, 17, 10, 89, 40, 82, 41, 2, 48, 98, 16, 43, 62, 33, 72, 35, 10, 24, 80, 29, 49, 5, 14, 38, 30, 48, 93, 86, 62, 23, 17, 39, 40, 96, 10, 75, 6, 38, 1, 5, 54, 91, 29, 36, 62, 73, 51, 92, 89, 88, 74, 91, 87, 34, 49, 56, 33, 67};
        outExpected = 3285;
        outComputed = soln.minAbsoluteSumDiff(nums1, nums2);
        assert(outExpected == outComputed);
        // soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindMaxGain();
    solnTest.testMinAbsoluteSumDiff();

    return 0;
}