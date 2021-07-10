// LeetCode-300: https://leetcode.com/problems/longest-increasing-subsequence/submissions/
// TusharRoy: https://www.youtube.com/watch?v=CE2b_-XfVDk
// IDeserve: https://www.youtube.com/watch?v=1RpMc3fv0y4&t=212s
// HackerRank: (requires nlogn soln) https://www.hackerrank.com/challenges/longest-increasing-subsequent
// InterviewBit: https://www.interviewbit.com/problems/longest-increasing-subsequence/

/**
 * @file leetcode-300-longest-increasing-subsequence.cpp
 * @author y2k-shubham (Shubham Gupta)
 * @brief in addition to the classical dynamic-programming approach (implemented here as lis1Classic),
 *        in the IDeserve video, they've told another ingenious / clever way to solve it via Dynamic
 *        Programming by leveraging solution of LongestCommonSubsequence (LCS)
 *        - sort the array
 *        - then take LCS of original (unsorted) array & sorted array
 *        the above will give longest increasing subsequence (attempted implemented / broken in lis2Lcs)
 * @date 2020-09-27
 */

#include <algorithm>
#include <cmath>
#include <vector>
// for std::move() https://stackoverflow.com/a/27026280/3679900
#include <utility>

using namespace std;

class Solution {
   private:
    int lis1Classic(vector<int>& nums) {
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

    // this is the IDeserve's ingenious approach
    // it needs debugging; but first impressions are that it is much more difficult than it sounds
    // (particularly handling duplicates is problematic)
    int lis2Lcs(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        vector<int> numsSorted = nums;
        sort(numsSorted.begin(), numsSorted.end());

        vector<vector<int> > residMat(2);
        vector<int> matRow1(len + 1, 0);
        vector<int> matRow2(len + 1, 0);
        residMat[0] = matRow1;
        residMat[1] = matRow2;

        // std::move() https://stackoverflow.com/a/27026280/3679900
        vector<int> matRowPrev = move(matRow1);
        vector<int> matRowCrr = move(matRow2);
        vector<int> matRowTmp;

        for (int i = 1; i <= len; i++) {
            int v1 = nums[i - 1];
            for (int j = 1; j <= len; j++) {
                int v2 = numsSorted[j - 1];

                if (v1 == v2) {
                    if ((i > 1) && (j > 1) && (matRowCrr[i - 1] == matRowCrr[i - 2]) && (matRowPrev[j - 1] == matRowPrev[j - 2])) {
                        matRowCrr[j] = max(matRowPrev[j], matRowCrr[j - 1]);
                    } else {
                        matRowCrr[j] = matRowPrev[j - 1] + 1;
                    }
                } else {
                    matRowCrr[j] = max(matRowPrev[j], matRowCrr[j - 1]);
                }
            }

            matRowTmp = move(matRowCrr);
            matRowCrr = move(matRowPrev);
            matRowPrev = move(matRowTmp);
        }

        return matRowCrr[len];
    }

   public:
    int lengthOfLIS(vector<int>& nums) {
        return lis2Lcs(nums);
    }
};
