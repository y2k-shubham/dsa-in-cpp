// LeetCode-2971: https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/
// solved after reading editorial

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<long long int> createPrefixSumVec(vector<int>& vec) {
        int len = vec.size();

        vector<long long int> prefixSumVec(len);
        prefixSumVec[0] = vec[0];

        for (int i = 1; i < len; i++) {
            prefixSumVec[i] = prefixSumVec[i - 1] + vec[i];
        }

        return prefixSumVec;
    }

    long long calculateLargestPerimeterOfPolygon(vector<int>& nums, vector<long long int>& prefixSumVec) {
        int len = nums.size();
        for (int i = len - 1; i >= 2; i--) {
            if (prefixSumVec[i - 1] > nums[i]) {
                return prefixSumVec[i - 1] + nums[i];
            }
        }

        return -1;
    }

public:
    long long largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<long long int> prefixSumVec = createPrefixSumVec(nums);

        return calculateLargestPerimeterOfPolygon(nums, prefixSumVec);
    }
};
