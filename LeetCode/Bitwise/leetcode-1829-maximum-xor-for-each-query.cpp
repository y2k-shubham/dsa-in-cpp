// LeetCode-1829: https://leetcode.com/problems/maximum-xor-for-each-query/

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int len = nums.size();
        int bitMask = pow(2, maximumBit) - 1;

        vector<int> resVec(len, 0);

        int prefixXor = 0;
        for (int i = 0; i < len; i++) {
            prefixXor ^= nums[i];

            int resXor = prefixXor ^ bitMask;
            resVec[i] = resXor;
        }

        reverse(resVec.begin(), resVec.end());

        return resVec;
    }
};

