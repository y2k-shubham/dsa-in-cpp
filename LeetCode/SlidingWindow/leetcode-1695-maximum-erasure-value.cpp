// LeetCode-1695: https://leetcode.com/problems/maximum-erasure-value/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return nums[0];
        }

        unordered_map<int, int> freqMap;
        int iLo = 0;
        int iHi = 0;
        int maxSum = 0;
        int crrSum = 0;
        while ((iLo <= iHi) && (iHi < len)) {
            // expand window till we have only unique elements
            while (iHi < len) {
                int crrVal = nums[iHi];

                freqMap[crrVal]++;
                crrSum += crrVal;

                iHi++;

                if (freqMap[crrVal] > 1) {
                    break;
                } else {
                    maxSum = max(maxSum, crrSum);
                }
            }

            // shrink window till we have non-unique elements
            while (iLo < iHi) {
                int crrVal = nums[iLo];

                freqMap[crrVal]--;
                crrSum -= crrVal;

                iLo++;

                if (freqMap[crrVal] == 1) {
                    break;
                }
            }
        }

        return maxSum;
    }
};
