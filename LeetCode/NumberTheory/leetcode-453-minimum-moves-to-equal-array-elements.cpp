// LeetCode-453: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/
// quite difficult maths problem
// Soln: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/discuss/93817/it-is-a-math-question

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    int findCurrentSum(vector<int>& vec) {
        return accumulate(vec.begin(), vec.end(), 0);
    }

    int findMinEle(vector<int>& vec) {
        return *min_element(vec.begin(), vec.end());
    }

   public:
    int minMoves(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return 0;
        }

        int crrSum = findCurrentSum(nums);
        int minEle = findMinEle(nums);

        if (crrSum == (minEle * len)) {
            return 0;
        }

        int numMoves = crrSum - (minEle * len);
        return numMoves;
    }
};
