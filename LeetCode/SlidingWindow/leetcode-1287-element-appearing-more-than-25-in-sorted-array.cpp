// LeetCode-1287: https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array

#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int len = arr.size();
        int quarterLen = ((len % 4) == 0) ? ((len / 4) + 1) : ceil(len * 0.25f);

        int iLo = 0;
        int iHi = iLo + quarterLen - 1;
        while (iHi < len) {
            if (arr[iLo] == arr[iHi]) {
                return arr[iLo];
            }

            iLo++;
            iHi++;
        }

        return INT_MIN;
    }
};
