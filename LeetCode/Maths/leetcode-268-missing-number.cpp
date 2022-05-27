// LeetCode-268: https://leetcode.com/problems/missing-number/

#include <vector>
#include <numeric>

using namespace std;

class Solution {
private:
    int calcSigmaN(int n) {
        if (n <= 1) {
            return n;
        }

        return (n * (n + 1)) / 2;
    }

public:
    int missingNumber(vector<int>& nums) {
        int len = nums.size();

        int n = len;
        int sigmaN = calcSigmaN(n);

        int sum = accumulate(nums.begin(), nums.end(), 0);

        return (sigmaN - sum);
    }
};
