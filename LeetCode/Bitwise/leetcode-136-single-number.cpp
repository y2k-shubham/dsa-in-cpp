// LeetCode-136: https://leetcode.com/problems/single-number/

#include <vector>

using namespace std;

class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        int _xor = 0;
        for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
            _xor ^= *it;
        }
        return _xor;
    }
};
