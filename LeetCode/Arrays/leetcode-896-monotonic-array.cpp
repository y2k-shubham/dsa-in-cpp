// LeetCode-896: https://leetcode.com/problems/monotonic-array/
// dumb question, don't bother

#include <vector>
#include <iterator>

using namespace std;

class Solution {
private:
    inline bool isNonDecreasing(vector<int>& vec) {
        int maxSoFar = INT_MIN;
        for (auto it = vec.begin(); it != vec.end(); it++) {
            if (maxSoFar <= *it) {
                maxSoFar = *it;
            } else {
                return false;
            }
        }

        return true;
    }

    inline bool isNonIncreasing(vector<int>& vec) {
        int minSoFar = INT_MAX;
        for (auto it = vec.begin(); it != vec.end(); it++) {
            if (minSoFar >= *it) {
                minSoFar = *it;
            } else {
                return false;
            }
        }

        return true;
    }

public:
    bool isMonotonic(vector<int>& nums) {
        if (nums.size() <= 1) {
            return true;
        }

        return isNonDecreasing(nums) || isNonIncreasing(nums);
    }
};
