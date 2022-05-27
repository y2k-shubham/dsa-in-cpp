// LeetCode-453: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/
// quite difficult maths problem
// Soln: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/discuss/93817/it-is-a-math-question
/**
 * @file leetcode-453-minimum-moves-to-equal-array-elements.cpp
 * @author Shubham Gupta (y2k-shubham)
 * @brief 
 * 
 * here's the mathematical derivation of expression
 * sum = sum of array elements (initially)
 * k = required no of moves (this is what we need to find)
 * len = length of array
 * x = final value of all array items (once they become equal)
 * 
 * sum + k*(len - 1) = len * x
 * x = minVal + k
 * 
 * using above, we get
 * sum + k*(len - 1) = len * (minVal + k)
 * sum + k*len - k = len*minVal + k*len
 * k = sum - len*minVal
 * 
 * @date 2021-05-23
 */

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
