// LeetCode-162: https://leetcode.com/problems/find-peak-element/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3812/
// IDeserve soln: https://www.youtube.com/watch?v=a7D77DdhlFc

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findPeakElement(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return 0;
        }

        int lo = 0;
        int hi = len - 1;
        int mid;
        while (lo < hi) {
            mid = (lo + hi) / 2;
            int midEle = nums[mid];

            int leftEle = (0 <= (mid - 1)) ? nums[mid - 1] : INT_MIN;
            int rightEle = ((mid + 1) < len) ? nums[mid + 1] : INT_MIN;

            bool leftEleSmaller = leftEle < midEle;
            bool leftEleBigger = leftEle > midEle;
            bool rightEleSmaller = midEle > rightEle;
            bool rightEleBigger = midEle < rightEle;

            if (leftEleSmaller && rightEleSmaller) {
                return mid;
            } else if (leftEleSmaller || rightEleBigger) {
                lo = (lo == mid) ? (mid + 1) : mid;
            } else if (rightEleSmaller || leftEleBigger) {
                hi = (hi == mid) ? (mid - 1) : mid;
            }
        }

        return lo;
    }
};
