// LeetCode-941: https://leetcode.com/problems/valid-mountain-array/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    bool validMountainArray(vector<int>& arr) {
        int len = arr.size();
        if (len < 3) {
            return false;
        }

        int i = 0;

        // strictly increasing part
        for (i = 1; i < (len - 1); i++) {
            if (arr[i - 1] >= arr[i]) {
                break;
            }
        }
        if (i == 1) {
            // no strictly increasing part
            return false;
        }

        // strictly decreasing part
        for (; i < len; i++) {
            if (arr[i - 1] <= arr[i]) {
                return false;
            }
        }
        if (i < len) {
            // no strictly decreasing part
            return false;
        }

        return true;
    }
};
