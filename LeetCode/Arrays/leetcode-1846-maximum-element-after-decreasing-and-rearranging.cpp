// LeetCode-1846: https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging
// code Explainer: https://www.youtube.com/watch?v=RwMi8FJjbfo

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int len = arr.size();
        if (len == 1) {
            return 1;
        }

        sort(arr.begin(), arr.end());

        arr[0] = 1;
        for (int i = 1; i < len; i++) {
            arr[i] = min(arr[i - 1] + 1, arr[i]);
        }

        return arr[len - 1];
    }
};
