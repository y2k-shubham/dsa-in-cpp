// LeetCode-704: https://leetcode.com/problems/binary-search/
// please skip checking this [too lame a problem to be put up on LeetCode]

#include <vector>

using namespace std;

class Solution {
private:
    int binSearchRec(vector<int> &vec, int target, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midVal = vec[mid];

        if (target < midVal) {
            return binSearchRec(vec, target, lo, mid - 1);
        } else if (target == midVal) {
            return mid;
        } else {
            return binSearchRec(vec, target, mid + 1, hi);
        }
    }

public:
    int search(vector<int> &nums, int target) {
        int len = nums.size();
        return binSearchRec(nums, target, 0, len - 1);
    }
};
