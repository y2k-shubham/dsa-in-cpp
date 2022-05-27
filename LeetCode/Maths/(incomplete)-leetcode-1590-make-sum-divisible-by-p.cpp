// LeetCode-1590: https://leetcode.com/problems/make-sum-divisible-by-p/
// incomplete / wrong answer (copied solution, couldn't really understand)
// difficult modulo arithmetic (i still cant reason)

#include <climits>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    long long int calcSum(vector<int>& vec) {
        long long int sum = 0;

        for (int i = 0; i < vec.size(); i++) {
            sum += vec[i];
        }

        return sum;
    }

   public:
    int minSubarray(vector<int>& nums, int p) {
        long long int sum = calcSum(nums);

        int finalRem = (int)(sum % p);
        if (finalRem == 0) {
            return 0;
        }

        int minSubArrLen = INT_MAX;
        int len = nums.size();

        int crrRem = 0;
        unordered_map<int, int> remLastIdxMap;
        for (int i = 0; i < len; i++) {
            crrRem = (crrRem + nums[i]) % p;

            int deltaRem = (((crrRem - finalRem) % p) + p) % p;
            if (remLastIdxMap.find(deltaRem) != remLastIdxMap.end()) {
                int crrSubArrLen = i - remLastIdxMap[deltaRem];
                minSubArrLen = min(minSubArrLen, crrSubArrLen);
            }

            remLastIdxMap[crrRem] = i;
        }

        return (minSubArrLen >= len) ? -1 : minSubArrLen;
    }
};
