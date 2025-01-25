// LeetCode-1413: https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/

#include <vector>

using namespace std;

class Solution {
public:
    int minStartValue(vector <int>& nums) {
        int minPrefixSum = INT_MAX;
        int prefixSum = 0;

        for (int num : nums) {
            prefixSum += num;
            minPrefixSum = min(minPrefixSum, prefixSum);
        }

        if (minPrefixSum >= 1) {
            return 1;
        } else {
            return 1 - minPrefixSum;
        }
    }
};
