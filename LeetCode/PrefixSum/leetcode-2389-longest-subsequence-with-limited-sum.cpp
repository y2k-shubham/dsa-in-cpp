// LeetCode-2389: https://leetcode.com/problems/longest-subsequence-with-limited-sum/

#include <vector>

using namespace std;

class Solution {
private:
    vector<int> buildPrefixSumVec(vector<int> &vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector<int> prefSumVec(len, 0);
        prefSumVec[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefSumVec[i] = prefSumVec[i - 1] + vec[i];
        }

        return prefSumVec;
    }

    int binSearchUpperBoundIdx(vector<int> &vec, int val, int loIdx, int hiIdx) {
        int len = hiIdx - loIdx + 1;
        if (len <= 0) {
            return -1;
        }

        int midIdx = (loIdx + hiIdx) / 2;
        int midVal = vec[midIdx];

        if (midVal < val) {
            int rRes = binSearchUpperBoundIdx(vec, val, midIdx + 1, hiIdx);
            return (rRes >= 0) ? rRes : midIdx;
        } else if (midVal == val) {
            return midIdx;
        } else {
            return binSearchUpperBoundIdx(vec, val, loIdx, midIdx - 1);
        }
    }

public:
    vector<int> answerQueries(vector<int> &nums, vector<int> &queries) {
        sort(nums.begin(), nums.end());
        vector<int> prefSum = buildPrefixSumVec(nums);

        int len = nums.size();
        int numQueries = queries.size();
        vector<int> answers(numQueries);
        for (int i = 0; i < numQueries; i++) {
            answers[i] = binSearchUpperBoundIdx(prefSum, queries[i], 0, len - 1) + 1;
        }

        return answers;
    }
};
