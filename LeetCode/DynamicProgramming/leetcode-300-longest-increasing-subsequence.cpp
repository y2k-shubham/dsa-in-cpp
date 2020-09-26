// LeetCode-300: https://leetcode.com/problems/longest-increasing-subsequence/submissions/
// TusharRoy: https://www.youtube.com/watch?v=CE2b_-XfVDk
// IDeserve: https://www.youtube.com/watch?v=1RpMc3fv0y4&t=212s
// HackerRank: (requires nlogn soln) https://www.hackerrank.com/challenges/longest-increasing-subsequent
// InterviewBit: https://www.interviewbit.com/problems/longest-increasing-subsequence/

/**
 * @file leetcode-300-longest-increasing-subsequence.cpp
 * @author y2k-shubham (Shubham Gupta)
 * @brief in addition to the classical dynamic-programming approach, in the IDeserve
 *        video, they've told another ingenious / clever way to solve it via Dynamic
 *        Programming by leveraging solution of LongestCommonSubsequence (LCS)
 *        - sort the array
 *        - then take LCS of original (unsorted) array & sorted array
 *        the above will give longest increasing subsequence
 * @date 2020-09-27
 */

#include <cmath>
#include <vector>

using namespace std;

int lengthOfLIS(vector<int>& nums) {
    int len = nums.size();

    if (len == 0) {
        return 0;
    } else if (len == 1) {
        return 1;
    } else {
        vector<int> lis(len, 1);

        int maxLis = 1;
        for (int j = 1; j < len; j++) {
            for (int i = 0; i < j; i++) {
                if (nums[i] < nums[j]) {
                    lis[j] = max(lis[j], lis[i] + 1);
                    maxLis = max(maxLis, lis[j]);
                }
            }
        }

        return maxLis;
    }
}
