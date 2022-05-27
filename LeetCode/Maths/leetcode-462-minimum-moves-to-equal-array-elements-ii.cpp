// LeetCode-462: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    float findMedian(vector<int>& vec) {
        sort(vec.begin(), vec.end());
        int n = vec.size();

        if ((n % 2) == 0) {
            return (vec[(n / 2) - 1] + vec[n / 2]) / 2.0f;
        } else {
            return vec[n / 2];
        }
    }

    int findMoves(vector<int>& vec, int target) {
        int moves = 0;

        for (int i = 0; i < vec.size(); i++) {
            moves += abs(vec[i] - target);
        }

        return moves;
    }

   public:
    int minMoves2(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        float median = findMedian(nums);
        if ((len % 2) == 0) {
            return min(findMoves(nums, floor(median)), findMoves(nums, ceil(median)));
        } else {
            return findMoves(nums, (int)median);
        }
    }
};
