// LeetCode-2091: https://leetcode.com/problems/removing-minimum-and-maximum-from-array/

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
private:
    pair <int, int> findMinEle(vector<int>& vec) {
        auto it = min_element(vec.begin(), vec.end());
        int idx = static_cast<int>(it - vec.begin());
        int val = *it;

        return {idx, val};
    }

    pair <int, int> findMaxEle(vector<int>& vec) {
        auto it = max_element(vec.begin(), vec.end());
        int idx = static_cast<int>(it - vec.begin());
        int val = *it;

        return {idx, val};
    }

public:
    int minimumDeletions(vector<int>& nums) {
        int len = nums.size();
        if (len <= 2) {
            return len;
        }

        pair <int, int> minEle = findMinEle(nums);
        pair <int, int> maxEle = findMaxEle(nums);

        // delete both min & max elements from left (beginning)
        int numDels1 = max(minEle.first, maxEle.first) + 1;

        // delete both min & max elements from right (end)
        int numDels2 = len - min(minEle.first, maxEle.first);

        // delete min from left and max from right (capped at max 'len' deletions)
        int numDels3 = min(len, (minEle.first + 1) + (len - maxEle.first));

        // delete min from right and max from left (capped at max 'len' deletions)
        int numDels4 = min(len, (len - minEle.first) + (maxEle.first + 1));

        return min(
            min(numDels1, numDels2),
            min(numDels3, numDels4)
        );
    }
};
