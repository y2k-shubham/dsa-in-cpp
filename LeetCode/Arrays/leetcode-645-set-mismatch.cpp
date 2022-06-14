// LeetCode-645: https://leetcode.com/problems/set-mismatch/

#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class Solution {
private:
    int findRepeatedNum(vector <int>& nums) {
        // 1st pass, mark values as negative
        for (int i = 0; i < nums.size(); i++) {
            int crrVal = nums[i];
            if (nums[abs(crrVal) - 1] < 0) {
                return abs(crrVal);
            }

            nums[abs(crrVal) - 1] *= -1;
        }

        return -1;
    }

    int calcSigmaN(int n) {
        return (n * (n + 1)) / 2;
    }

    int calcSum(vector <int>& nums) {
        return accumulate(nums.begin(), nums.end(), 0);
    }

public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();

        int expectedSum = calcSigmaN(n);
        int actualSum = calcSum(nums);

        int repeatedNum = findRepeatedNum(nums);
        int missingNum = abs(expectedSum - (actualSum - repeatedNum));

        return {repeatedNum, missingNum};
    }
};

