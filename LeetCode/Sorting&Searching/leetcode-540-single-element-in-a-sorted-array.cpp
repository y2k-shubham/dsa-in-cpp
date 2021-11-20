// LeetCode-540: https://leetcode.com/problems/single-element-in-a-sorted-array/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int singleNonDupRec(vector<int>& vec, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }
        if (len == 1) {
            return vec[lo];
        }
        if (len == 2) {
            // single occuring element will always have an even index
            return ((lo % 2) == 0) ? vec[lo] : vec[hi];
        }

        int mid = (lo + hi) / 2;
        if (len == 3) {
            if (vec[lo] == vec[mid]) {
                return vec[hi];
            } else if (vec[mid] == vec[hi]) {
                return vec[lo];
            } else {
                return vec[mid];
            }
        }

        if (vec[mid] == vec[mid + 1]) {
            if ((mid % 2) == 0) {
                return singleNonDupRec(vec, mid + 2, hi);
            } else {
                return singleNonDupRec(vec, lo, mid - 1);
            }
        } else if (vec[mid - 1] == vec[mid]) {
            if ((mid % 2) == 0) {
                return singleNonDupRec(vec, lo, mid - 2);
            } else {
                return singleNonDupRec(vec, mid + 1, hi);
            }
        } else {
            return vec[mid];
        }
    }

   public:
    int singleNonDuplicate(vector<int>& nums) {
        int len = nums.size();
        if (len < 1) {
            return -1;
        }
        if (len == 1) {
            return nums[0];
        }

        return singleNonDupRec(nums, 0, len - 1);
    }
};
