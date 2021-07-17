// LeetCode-658: https://leetcode.com/problems/find-k-closest-elements/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3800/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildDiffVec(vector<int>& vec, int x) {
        int len = vec.size();

        vector<int> diffVec(len);
        for (int i = 0; i < len; i++) {
            diffVec[i] = abs(vec[i] - x);
        }

        return diffVec;
    }

    vector<int> buildPrefixSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefixSum(len);

        prefixSum[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefixSum[i] = prefixSum[i - 1] + vec[i];
        }

        return prefixSum;
    }

    vector<int> findKClosestEles(vector<int>& vec, int k, int x) {
        int len = vec.size();

        vector<int> diffVec = buildDiffVec(vec, x);
        vector<int> diffPrefixSum = buildPrefixSum(diffVec);

        int lo = 0;
        int hi = lo + k - 1;
        int crrDiffSum = diffPrefixSum[hi];

        int minDiffSum = INT_MAX;
        int minDiffStartIdx = lo;

        do {
            crrDiffSum = (lo == 0) ? diffPrefixSum[hi] : (diffPrefixSum[hi] - diffPrefixSum[lo - 1]);

            if (crrDiffSum < minDiffSum) {
                minDiffSum = crrDiffSum;
                minDiffStartIdx = lo;
            }

            lo++;
            hi++;
        } while (hi < len);

        vector<int> closestElesVec(k);
        for (int i = minDiffStartIdx, j = 0; j < k; i++, j++) {
            closestElesVec[j] = vec[i];
        }

        return closestElesVec;
    }

   public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int len = arr.size();
        if (k == len) {
            return arr;
        }

        return findKClosestEles(arr, k, x);
    }
};
