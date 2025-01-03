// LeetCode-1144: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag

#include <vector>

using namespace std;

class Solution {
private:
    inline int calcNumRequiredDecrements(vector <int>& vec, int idx) {
        if (vec.size() <= 1) {
            return 0;
        }

        int len = vec.size();

        int leftDecrements = 0;
        if ((idx > 0) && (vec[idx - 1] <= vec[idx])) {
            leftDecrements = vec[idx] - vec[idx - 1] + 1;
        }

        int rightDecrements = 0;
        if ((idx < len - 1) && (vec[idx] >= vec[idx + 1])) {
            rightDecrements = vec[idx] - vec[idx + 1] + 1;
        }

        return max(leftDecrements, rightDecrements);
    }

    int calcNumRequiredDecrementsStartingFromIdx(vector <int>& vec, int beginIdx) {
        int numDecrements = 0;
        for (int i = beginIdx; i < vec.size(); i += 2) {
            numDecrements += calcNumRequiredDecrements(vec, i);
        }

        return numDecrements;
    }

public:
    int movesToMakeZigzag(vector <int>& nums) {
        int numDecrements1 = calcNumRequiredDecrementsStartingFromIdx(nums, 0);
        int numDecrements2 = calcNumRequiredDecrementsStartingFromIdx(nums, 1);

        return min(numDecrements1, numDecrements2);
    }
};
