// LeetCode-611: https://leetcode.com/problems/valid-triangle-number/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3815/
// Soln by 'Coding Decoded': https://www.youtube.com/watch?v=pmsex9gj1PI

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
   private:
   public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int len = nums.size();
        int numTriplets = 0;

        for (int k = 2; k < len; k++) {
            int eK = nums[k];

            int j = k - 1;
            int i = 0;
            while (i < j) {
                int eI = nums[i];
                int eJ = nums[j];

                if ((eI + eJ) > eK) {
                    numTriplets += j - i;
                    j--;
                } else {
                    i++;
                }
            }
        }

        return numTriplets;
    }
};
