// LeetCode-665: https://leetcode.com/problems/non-decreasing-array/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3731/

/**
 * @file leetcode-665-non-decreasing-array.cpp
 * @author Shubham Gupta(y2k-shubham)
 * @brief certainly trickier than it seems.
 *        the point to keep in mind is that even with single element to remove,
 *        there could be two distinct cases (requiring very different treatment)
 *        - 1 2 3 4 (3) 5 6 7 : the element to remove (3) is smaller [there's a dip]
 *        - 1 2 3 4 (9) 5 6 7 : the element to remove (9) is bigger  [there's a bump]
 * @date 2021-05-10
 */

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int findDipIdxLeft(vector<int>& vec, int lo, int hi) {
        for (int i = lo + 1; i <= hi; i++) {
            if (vec[i - 1] > vec[i]) {
                return i;
            }
        }

        return -1;
    }

    bool isSorted(vector<int>& vec, int lo, int hi) {
        return findDipIdxLeft(vec, lo, hi) == -1;
    }

   public:
    bool checkPossibility(vector<int>& vec) {
        vec.insert(vec.begin(), INT_MIN);  // insert -inf at the beginning
        vec.push_back(INT_MAX);            // insert +inf at the end

        int len = vec.size();

        int dipIdxLeft = findDipIdxLeft(vec, 0, len - 1);
        if (dipIdxLeft == -1) {
            return true;
        }

        if (vec[dipIdxLeft - 2] <= vec[dipIdxLeft]) {
            // bump
            return isSorted(vec, dipIdxLeft, len - 1);
        } else {
            // dip
            return (vec[dipIdxLeft - 1] <= vec[dipIdxLeft + 1]) && isSorted(vec, dipIdxLeft + 1, len - 1);
        }
    }
};
