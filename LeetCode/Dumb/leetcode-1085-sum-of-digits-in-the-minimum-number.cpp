// LeetCode-1085: https://leetcode.com/problems/sum-of-digits-in-the-minimum-number/
// Premium
// Dumb

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int calcSumOfDigits(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }

        return sum;
    }

public:
    int sumOfDigits(vector<int>& nums) {
        // Find smallest element
        auto it = min_element(nums.begin(), nums.end());
        // calculate sum of digits
        int minEleSumOfDigits = calcSumOfDigits(*it);

        return (minEleSumOfDigits & 1) ? 0 : 1;
    }
};
