// LeetCode-34: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
private:
    int findFirstIdx(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return INT_MAX;
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        if (ele < midEle) {
            return findFirstIdx(vec, ele, lo, mid - 1);
        } else if (ele == midEle) {
            return min(mid, findFirstIdx(vec, ele, lo, mid - 1));
        } else {
            return findFirstIdx(vec, ele, mid + 1, hi);
        }
    }

    int findLastIdx(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return INT_MIN;
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        if (ele < midEle) {
            return findLastIdx(vec, ele, lo, mid - 1);
        } else if (ele == midEle) {
            return max(findLastIdx(vec, ele, mid + 1, hi), mid);
        } else {
            return findLastIdx(vec, ele, mid + 1, hi);
        }
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        if (len <= 0) {
            return {-1, -1};
        }

        int firstIdx = findFirstIdx(nums, target, 0, len - 1);
        if (firstIdx == INT_MAX) {
            return {-1, -1};
        }

        int lastIdx = findLastIdx(nums, target, 0, len - 1);
        return {firstIdx, lastIdx};
    }
};
