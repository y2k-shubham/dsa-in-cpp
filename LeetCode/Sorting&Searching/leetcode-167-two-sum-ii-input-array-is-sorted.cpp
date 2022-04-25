// LeetCode-167: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
// complete waste of time (you've probably done this 10 times before)

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int len = numbers.size();

        int iLo = 0;
        int iHi = len - 1;
        while (iLo < iHi) {
            int crrSum = numbers[iLo] + numbers[iHi];

            if (crrSum < target) {
                iLo++;
            } else if (crrSum == target) {
                return {iLo + 1, iHi + 1};
            } else {
                iHi--;
            }
        }

        return {};
    }
};
