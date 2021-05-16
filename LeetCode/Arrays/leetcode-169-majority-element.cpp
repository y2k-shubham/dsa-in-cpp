// LeetCode-169: https://leetcode.com/problems/majority-element/
// Tech-Dose explanation: https://www.youtube.com/watch?v=bg6r_fgtpMQ

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int majorityElement(vector<int>& nums) {
        int majEle = nums[0];
        int majEleCtr = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == majEle) {
                majEleCtr++;
            } else {
                majEleCtr--;

                if (majEleCtr == 0) {
                    majEle = nums[i];
                    majEleCtr = 1;
                }
            }
        }

        return majEle;
    }
};
