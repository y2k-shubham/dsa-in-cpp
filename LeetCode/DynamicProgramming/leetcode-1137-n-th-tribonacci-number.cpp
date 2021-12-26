// LeetCode-1137: https://leetcode.com/problems/n-th-tribonacci-number/
// pretty dumb problem; look away

#include <vector>

using namespace std;

class Solution {
   public:
    int tribonacci(int n) {
        vector<int> vec(50, 0);
        vec[0] = 0;
        vec[1] = 1;
        vec[2] = 1;

        for (int i = 3; i <= 37; i++) {
            vec[i] = vec[i - 1] + vec[i - 2] + vec[i - 3];
        }

        return vec[n];
    }
};
