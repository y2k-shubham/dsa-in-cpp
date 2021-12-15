// LeetCode-152: https://leetcode.com/problems/maximum-product-subarray/

/**
 * test cases
 * [2,3,-2,4]
 * [-2,0,-1]
 * [0]
 * [0,0,0]
 * [9]
 * [6,1,9,5]
 * [6,1,0,9,5]
 * [-3]
 * [-3,-4,-1,-9]
 * [-3,-4,0,-1,-9]
 * [-1,3,-9,5,-2,1]
 * [-1,3,0,-9,5,-2,0,1]
 * [-3,0,-4,0,-6,0,-8,8]
 */

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    // original soln: intuituve but difficult to implement
    // time=O(n), space=O(1); yet speed %tile = 15
    int maxProduct1(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return nums[0];
        }

        int maxProd = INT_MIN;
        int maxEle = INT_MIN;

        int numNegs = 0;
        int crrProdTillFirstNeg = 1;
        int crrProd = 1;
        int crrProdFromLastNeg = 1;
        int crrWinStartIdx = 0;
        for (int i = 0; i < len; i++) {
            int crrEle = nums[i];
            maxEle = max(maxEle, crrEle);

            if (crrEle == 0) {
                numNegs = 0;
                crrProdTillFirstNeg = 1;
                crrProd = 1;
                crrProdFromLastNeg = 1;
                crrWinStartIdx = i + 1;
            } else {
                crrProd *= crrEle;
                int crrWinLen = i - crrWinStartIdx + 1;

                if (crrEle < 0) {
                    numNegs++;
                    if (numNegs == 1) {
                        crrProdTillFirstNeg = crrProd;
                    }
                    crrProdFromLastNeg = crrEle;
                } else {
                    if (numNegs >= 1) {
                        crrProdFromLastNeg *= crrEle;
                    }
                }

                if ((numNegs % 2) == 0) {
                    maxProd = max(maxProd, crrProd);
                } else {
                    if (crrWinLen == 1) {
                        // single neg element seent -> do nothing
                    } else {
                        maxProd = max(
                            maxProd,
                            max(
                                (crrProd / crrProdTillFirstNeg),
                                (crrProd / crrProdFromLastNeg)));
                    }
                }
            }
        }

        return max(maxProd, maxEle);
    }

    // web soln: unintuituve but easy to implement
    // NareshGupta: https://www.youtube.com/watch?v=IDeyPqApnX0
    // time=O(n), space=O(1); speed %tile = 84
    int maxProduct2(vector<int>& nums) {
        int maxProd = nums[0];
        int crrMaxProd = nums[0];
        int crrMinProd = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int crrEle = nums[i];
            int crrMaxProdCopy = crrMaxProd;

            crrMaxProd = max(crrEle, max(crrMaxProdCopy * crrEle, crrMinProd * crrEle));
            crrMinProd = min(crrEle, min(crrMaxProdCopy * crrEle, crrMinProd * crrEle));

            maxProd = max(maxProd, max(crrMaxProd, crrMinProd));
        }

        return maxProd;
    }

    int maxProduct(vector<int>& nums) {
    }
};