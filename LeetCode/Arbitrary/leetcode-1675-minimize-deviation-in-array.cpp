// Hard LeetCode-1675: https://leetcode.com/problems/minimize-deviation-in-array/
// GFG: https://www.geeksforgeeks.org/minimize-deviation-of-an-array-by-given-operations/
// Algorithms Made Easy: https://www.youtube.com/watch?v=u0n-6zBnohY

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
   public:
    void doubleOddVals(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int crrVal = nums[i];
            if ((crrVal % 2) == 1) {
                nums[i] = crrVal * 2;
            }
        }
    }

    set<int> convertToOrderedSet(vector<int>& nums) {
        set<int> oSet(nums.begin(), nums.end());
        return oSet;
    }

    int getDev(vector<int>& vec) {
        int maxVal = INT_MIN;
        int minVal = INT_MAX;
        for (int i = 0; i < vec.size(); i++) {
            minVal = min(minVal, vec[i]);
            maxVal = max(maxVal, vec[i]);
        }

        return maxVal - minVal;
    }

    int getMinDev(set<int>& oSet) {
        int minVal = *(oSet.begin());
        int maxVal = *(oSet.rbegin());
        return (maxVal - minVal);
    }

    int minimizeEvenVals(set<int>& oSet) {
        int minDev = getMinDev(oSet);

        int crrMaxVal = *(oSet.rbegin());
        while ((crrMaxVal % 2) == 0) {
            oSet.erase(crrMaxVal);
            oSet.insert(crrMaxVal / 2);

            minDev = min(minDev, getMinDev(oSet));

            crrMaxVal = *(oSet.rbegin());
        }

        return minDev;
    }

    int minimumDeviation(vector<int>& nums) {
      // not sure if taking original deviation is required or not
        int orgDev = getDev(nums);

        doubleOddVals(nums);

        set<int> oSet = convertToOrderedSet(nums);
        int newDev = minimizeEvenVals(oSet);

        return min(orgDev, newDev);
    }
};
