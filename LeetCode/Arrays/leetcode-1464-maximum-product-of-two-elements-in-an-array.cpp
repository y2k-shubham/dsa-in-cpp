// LeetCode-1464: https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/
// dont bother; pretty dumb question (why did i even read this question)

#include <climits>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    pair<int, int> findMax2Eles(vector<int>& vec) {
        int max1 = INT_MIN;
        int max2 = INT_MIN;

        for (int i = 0; i < vec.size(); i++) {
            int ele = vec[i];

            if (ele > max1) {
                max2 = max1;
                max1 = ele;
            } else if (ele > max2) {
                max2 = ele;
            }
        }

        return {max1, max2};
    }

   public:
    int maxProduct(vector<int>& nums) {
        pair<int, int> max2Eles = findMax2Eles(nums);
        return (max2Eles.first - 1) * (max2Eles.second - 1);
    }
};
