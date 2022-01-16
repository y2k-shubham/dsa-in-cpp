// LeetCode-915: https://leetcode.com/problems/partition-array-into-disjoint-intervals/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildMaxElePrefixVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> maxElePrefixVec(len, INT_MIN);

        maxElePrefixVec[0] = vec[0];
        for (int i = 1; i < len; i++) {
            maxElePrefixVec[i] = max(maxElePrefixVec[i - 1], vec[i]);
        }

        return maxElePrefixVec;
    }

    vector<int> buildMinEleSuffixVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> minEleSuffixVec(len, INT_MAX);

        minEleSuffixVec[len - 1] = vec[len - 1];
        for (int i = len - 2; i >= 0; i--) {
            minEleSuffixVec[i] = min(minEleSuffixVec[i + 1], vec[i]);
        }

        return minEleSuffixVec;
    }

    int partition(
        vector<int>& vec,
        vector<int>& maxElePrefixVec,
        vector<int>& minEleSuffixVec) {
        int len = vec.size();

        for (int i = 0; i < (len - 1); i++) {
            if (maxElePrefixVec[i] <= minEleSuffixVec[i + 1]) {
                return (i + 1);
            }
        }

        return -1;
    }

   public:
    int partitionDisjoint(vector<int>& nums) {
        vector<int> maxElePrefixVec = buildMaxElePrefixVec(nums);
        vector<int> minEleSuffixVec = buildMinEleSuffixVec(nums);

        return partition(nums, maxElePrefixVec, minEleSuffixVec);
    }
};
