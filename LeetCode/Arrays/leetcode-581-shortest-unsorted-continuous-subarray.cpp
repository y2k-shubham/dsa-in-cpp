// LeetCode-581: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
// LC Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3652/
// GFG: https://www.geeksforgeeks.org/minimum-length-unsorted-subarray-sorting-which-makes-the-complete-array-sorted/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> findBiggestEleIndOnLeft(vector<int>& vec) {
        int len = vec.size();

        vector<int> biggestEleIndOnLeft(len);
        biggestEleIndOnLeft[0] = -1;

        int biggestEleInd = 0;
        for (int i = 1; i < len; i++) {
            biggestEleIndOnLeft[i] = biggestEleInd;

            if (vec[i] >= vec[biggestEleInd]) {
                biggestEleInd = i;
            }
        }

        return biggestEleIndOnLeft;
    }

    vector<int> findSmallestEleIndOnRight(vector<int>& vec) {
        int len = vec.size();

        vector<int> smallestEleIndOnRight(len);
        smallestEleIndOnRight[len - 1] = len;

        int smallestEleInd = len - 1;
        for (int i = len - 2; i >= 0; i--) {
            smallestEleIndOnRight[i] = smallestEleInd;

            if (vec[i] <= vec[smallestEleInd]) {
                smallestEleInd = i;
            }
        }

        return smallestEleIndOnRight;
    }

    int findUnsortedSubArrLeftBoundaryIdx(vector<int> vec) {
        int len = vec.size();

        vector<int> smallestEleIndOnRight = findSmallestEleIndOnRight(vec);

        int idx = 0;
        while (idx < len) {
            if ((smallestEleIndOnRight[idx] < len) && (vec[smallestEleIndOnRight[idx]] < vec[idx])) {
                break;
            }

            idx++;
        }

        return idx;
    }

    int findUnsortedSubArrRightBoundaryIdx(vector<int> vec) {
        int len = vec.size();

        vector<int> biggestEleIndOnLeft = findBiggestEleIndOnLeft(vec);

        int idx = len - 1;
        while (idx >= 0) {
            if ((biggestEleIndOnLeft[idx] >= 0) && (vec[biggestEleIndOnLeft[idx]] > vec[idx])) {
                break;
            }

            idx--;
        }

        return idx;
    }

   public:
   // LC-submission: speed 59 %tile, memory 5 %tile
    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        int leftBoundary = findUnsortedSubArrLeftBoundaryIdx(nums);
        int rightBoundary = findUnsortedSubArrRightBoundaryIdx(nums);

        if (leftBoundary < rightBoundary) {
            return (rightBoundary - leftBoundary + 1);
        } else {
            return 0;
        }
    }
};
