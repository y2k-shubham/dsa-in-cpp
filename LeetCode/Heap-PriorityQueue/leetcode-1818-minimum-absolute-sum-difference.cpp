// LeetCode-1818: https://leetcode.com/problems/minimum-absolute-sum-difference/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
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
        int dipMax = INT_MAX;
        while (!diffHeap.empty() && ((dipMax == INT_MAX) || (diffHeap.top().first > dipMax))) {
            int diffOrg = diffHeap.top().first;
            int idx = diffHeap.top().second;
            diffHeap.pop();

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

            // find element smaller than val2
            it--;
            int diffLo = abs(val2 - *it);
            if (diffLo < diffOrg) {
                gain = max(gain, diffOrg - diffLo);
            }

            // find element greater than val2
            it++;
            if (it != mOrderedSet.end()) {
                int diffHi = abs(val2 - *it);
                if (diffHi < diffOrg) {
                    gain = max(gain, diffOrg - diffHi);
                }
            }

            if ((gain != INT_MIN) && (gain > dipMax)) {
                dipMax = gain;
            }
        }

        return dipMax;
    }

   public:
    friend class SolutionTest;
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> mUnorderedSet = createUnorderedSet(nums1);
        set<int> mOrderedSet = createOrderedSet(nums1);

        pair<int, priority_queue<pair<int, int>>> diffsResponse = createDiffHeap(nums1, nums2);
        int orgDiffSum = diffsResponse.first;
        priority_queue<pair<int, int>> diffHeap = diffsResponse.second;

        int dipMax = findMaxGain(nums1, nums2, mUnorderedSet, mOrderedSet, diffHeap);
        int reducedDiffSum = (orgDiffSum - dipMax) % MOD;

        return reducedDiffSum;
    }
};

class SolutionTest {
   public:
    void testFindMaxGain() {
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testFindMaxGain();

    return 0;
}