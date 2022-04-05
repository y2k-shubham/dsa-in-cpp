// LeetCode-11: https://leetcode.com/problems/container-with-most-water/

#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int len = height.size();
        int maxWaterArea = 0;

        int iLeft = 0;
        int iRight = len - 1;
        while (iLeft < iRight) {
            int iLeftHeight = height[iLeft];
            int iRightHeight = height[iRight];

            int crrContainerHeight = min(iLeftHeight, iRightHeight);
            int crrContainerWidth = iRight - iLeft;

            int crrWaterArea = crrContainerHeight * crrContainerWidth;
            maxWaterArea = max(maxWaterArea, crrWaterArea);

            if (iLeftHeight < iRightHeight) {
                iLeft++;
            } else {
                iRight--;
            }
        }

        return maxWaterArea;
    }
};
