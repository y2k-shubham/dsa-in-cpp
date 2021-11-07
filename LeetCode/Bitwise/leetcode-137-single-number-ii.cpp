// LeetCode-137: https://leetcode.com/problems/single-number-ii/
// TechDose: https://www.youtube.com/watch?v=cOFAmaMBVps

#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
/**
 * time: O(32n); technically sorting the array performs better than this in avg case
 * space: O(1)
 */
    int method1CountSetBits(vector <int>& vec) {
      int ans = 0;
      for (int bitPos = 0; bitPos <= 31; bitPos++) {
        unsigned int bitMask = 1 << bitPos; // unsigned is IMPORTANT; or else we get wrong answer whenever result is negative

        int numSetVals = 0;
        for (int i = 0; i < vec.size(); i++) {
          int val = vec[i];
          bool isSet = (val & bitMask) > 0;
          if (isSet) {
            numSetVals++;
          }
        }

        if ((numSetVals % 3) > 0) {
          ans |= bitMask;
        }
      }

      return ans;
    }

public:
    int singleNumber(vector<int>& nums) {
        return method1CountSetBits(nums);
    }
};
