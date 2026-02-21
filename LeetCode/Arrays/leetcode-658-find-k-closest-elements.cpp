// LeetCode-658: https://leetcode.com/problems/find-k-closest-elements/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3800/
// Clever approach using sliding window and prefix sum

/*
Approach: Sliding Window with Prefix Sum

Key Insight:
The k closest elements must form a contiguous subarray in the sorted input.
We find this subarray by minimizing the sum of absolute differences.

Algorithm:
1. Build diffVec: Store |arr[i] - x| for each element
2. Build prefix sum of diffVec for O(1) range sum queries
3. Slide a window of size k across the array
4. Track the window with minimum sum of differences
5. Return elements from that window

Example:
arr = [1,2,3,4,5], k = 3, x = 3

diffVec = [2,1,0,1,2]  (absolute differences from x=3)
diffPrefixSum = [2,3,3,4,6]

Sliding windows of size 3:
- [1,2,3]: sum = 2+1+0 = 3
- [2,3,4]: sum = 1+0+1 = 2  ← minimum
- [3,4,5]: sum = 0+1+2 = 3

Result: [2,3,4]

Time: O(n), Space: O(n)
*/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    // Build vector of absolute differences |arr[i] - x| for each element
    vector<int> buildDiffVec(vector<int>& vec, int x) {
        int len = vec.size();

        vector<int> diffVec(len);
        for (int i = 0; i < len; i++) {
            diffVec[i] = abs(vec[i] - x);
        }

        return diffVec;
    }

    // Build prefix sum array for O(1) range sum queries
    vector<int> buildPrefixSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefixSum(len);

        prefixSum[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefixSum[i] = prefixSum[i - 1] + vec[i];
        }

        return prefixSum;
    }

    // Find k closest elements using sliding window approach
    vector<int> findKClosestEles(vector<int>& vec, int k, int x) {
        int len = vec.size();

        // Build difference vector and its prefix sum
        vector<int> diffVec = buildDiffVec(vec, x);
        vector<int> diffPrefixSum = buildPrefixSum(diffVec);

        // Initialize sliding window [lo..hi] of size k
        int lo = 0;
        int hi = lo + k - 1;
        int crrDiffSum = diffPrefixSum[hi];

        int minDiffSum = INT_MAX;
        int minDiffStartIdx = lo;

        // Slide window across array, tracking minimum sum
        do {
            // Calculate sum of differences in current window using prefix sum
            crrDiffSum = (lo == 0) ? diffPrefixSum[hi] : (diffPrefixSum[hi] - diffPrefixSum[lo - 1]);

            // Update minimum if current window has smaller sum
            if (crrDiffSum < minDiffSum) {
                minDiffSum = crrDiffSum;
                minDiffStartIdx = lo;
            }

            lo++;
            hi++;
        } while (hi < len);

        // Extract k elements from the window with minimum sum
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
