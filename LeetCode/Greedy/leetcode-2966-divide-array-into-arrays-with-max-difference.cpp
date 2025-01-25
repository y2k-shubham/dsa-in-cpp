// LeetCode-2966: https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector <vector <int>> divideArray(vector <int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int len = nums.size();

        vector <vector <int>> groupedNums(len / 3);
        for (int i = 0; i < len; i += 3) {
            int minVal = nums[i];
            int maxVal = nums[i + 2];
            if ((maxVal - minVal) > k) {
                return {};
            }

            int midVal = nums[i + 1];

            vector <int> group = {minVal, midVal, maxVal};
            groupedNums[i / 3] = group;
        }

        return groupedNums;
    }
};
