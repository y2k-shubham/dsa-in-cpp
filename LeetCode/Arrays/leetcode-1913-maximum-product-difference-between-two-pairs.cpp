// LeetCode-1913: https://leetcode.com/problems/maximum-product-difference-between-two-pairs
// trivial question

#include <vector>
#include <utility>
#include <climits>

using namespace std;

class Solution {
private:
    pair<int, int> findMin2Eles(vector<int>& vec) {
        int min1 = INT_MAX;
        int min2 = INT_MAX;

        for (int i = 0; i < vec.size(); i++) {
            int ele = vec[i];
            if (ele <= min1) {
                min2 = min1;
                min1 = ele;
            } else if (ele < min2) {
                min2 = ele;
            }
        }

        return {min1, min2};
    }

    pair<int, int> findMax2Eles(vector<int>& vec) {
        int max1 = INT_MIN;
        int max2 = INT_MIN;

        for (int i = 0; i < vec.size(); i++) {
            int ele = vec[i];
            if (ele >= max1) {
                max2 = max1;
                max1 = ele;
            } else if (ele > max2) {
                max2 = ele;
            }
        }

        return {max1, max2};
    }

public:
    int maxProductDifference(vector<int>& nums) {
        pair<int, int> min2Eles = findMin2Eles(nums);
        pair<int, int> max2Eles = findMax2Eles(nums);

        return (max2Eles.first * max2Eles.second) - (min2Eles.first * min2Eles.second);
    }
};
