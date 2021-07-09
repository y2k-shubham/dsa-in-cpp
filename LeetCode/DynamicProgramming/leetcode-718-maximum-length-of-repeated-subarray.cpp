// LeetCode-718: https://leetcode.com/problems/maximum-length-of-repeated-subarray/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3807/
// GFG: https://www.geeksforgeeks.org/longest-common-subarray-in-the-given-two-arrays/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int> > buildMemoMat(int len1, int len2) {
        vector<vector<int> > memoMat(len1);

        for (int i = 0; i < len1; i++) {
            vector<int> memoMatRow(len2, 0);
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    // barely accepted; speed 5 %tile, memory 11 %tile
    // space optimization is straightforward: we only use 2 rows at a time (current & previous)
    int fillMemoMat(vector<int>& vec1, vector<int>& vec2) {
        int len1 = vec1.size();
        int len2 = vec2.size();
        int maxLen = max(len1, len2);

        vector<vector<int> > memoMat = buildMemoMat(len1, len2);

        int lcsLen = 0;
        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                if (vec1[i] == vec2[j]) {
                    int prevVal = ((i > 0) && (j > 0)) ? memoMat[i - 1][j - 1] : 0;
                    memoMat[i][j] = prevVal + 1;

                    lcsLen = max(lcsLen, memoMat[i][j]);

                    if (lcsLen == maxLen) {
                        return lcsLen;
                    }
                }
            }
        }

        return lcsLen;
    }

   public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        return fillMemoMat(nums1, nums2);
    }
};
