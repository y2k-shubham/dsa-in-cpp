// LeetCode-1793: https://leetcode.com/problems/maximum-score-of-a-good-subarray/

// CherryCoding: https://www.youtube.com/watch?v=P0SA8NCKY3w
// based on (almost identical to) 'largest rectangle in a histogram' leetcode-84: https://leetcode.com/problems/largest-rectangle-in-histogram/

/**
 * input
 * [1,4,3,7,4,5]
 * 3
 * output
 * 15
 *
 * input
 * [5,5,4,5,4,1,1,1]
 * 0
 * output
 * 20
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 2
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 3
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 4
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 5
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 6
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3]
 * 3
 * output
 * 117
 *
 * input
 * [5868,4839,3608,4826,2829,2871,3224,3579,9860,6453,458,1617,2201,2906,8334,8410,3104,1385,5462,4287,2960,5417,2640,2287,6331,4494,773,1178,1426,5271,3221,7606,1091,9043,7008,7218,6004,4636,6253,5628,9533,2204,6903,6912,9736,793,8529,190,1302,4140,3212,2589,2735,109,9090,8351,332,8693,2461,6274,7233,2689,7255,3894,3855,1037,7385,3874]
 * 38
 * output
 * 37088
 */

#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> findNleLeft(vector<int>& heights) {
        int len = heights.size();
        vector<int> nleLeft(len, -1);
        stack<int> stk;

        stk.push(0);
        for (int i = 1; i < len; i++) {
            int crrEle = heights[i];
            while (!stk.empty() && heights[stk.top()] >= crrEle) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleLeft[i] = stk.top();
            }
            stk.push(i);
        }

        return nleLeft;
    }

    vector<int> findNleRight(vector<int>& heights) {
        int len = heights.size();
        vector<int> nleRight(len, len);
        stack<int> stk;

        stk.push(len - 1);
        for (int i = len - 2; i >= 0; i--) {
            int crrEle = heights[i];
            while (!stk.empty() && heights[stk.top()] >= crrEle) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleRight[i] = stk.top();
            }
            stk.push(i);
        }

        return nleRight;
    }

    int largestRectangleAreaIncK(vector<int>& heights, int k) {
        if (heights.empty()) {
            return 0;
        } else if (heights.size() == 1) {
            return heights[0];
        } else {
            int len = heights.size();
            vector<int> nleLeft = findNleLeft(heights);
            vector<int> nleRight = findNleRight(heights);

            int maxArea = -1;
            for (int i = 0; i < len; i++) {
                int lLimit = nleLeft[i];
                int rLimit = nleRight[i];
                if (!(((lLimit + 1) <= k) && (k <= (rLimit - 1)))) {
                    // current rect wont include k, so skip
                    continue;
                }

                int crrArea = ((rLimit - 1) - (lLimit + 1) + 1) * heights[i];
                if (crrArea > maxArea) {
                    maxArea = crrArea;
                }
            }

            return maxArea;
        }
    }

   public:
    int maximumScore(vector<int>& nums, int k) {
        int len = nums.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return nums[0];
        }

        return largestRectangleAreaIncK(nums, k);
    }
};
