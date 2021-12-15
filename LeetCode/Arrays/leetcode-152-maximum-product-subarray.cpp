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

        // current window will always include all nums since last zero
        int numNegs = 0;              // no of neg nos in current window
        int crrProdTillFirstNeg = 1;  // (in current window) prod of all numbers till (and including) first neg no
        int crrProd = 1;              // (in current window) prod of all numbers
        int crrProdFromLastNeg = 1;   // (in current window) prod of all numbers from (and including) last neg no
        int crrWinStartIdx = 0;       // starting index of current window (equals 1 + index of last zero)
        for (int i = 0; i < len; i++) {
            int crrEle = nums[i];
            maxEle = max(maxEle, crrEle);

            if (crrEle == 0) {
                // when zero is encountered, we reset all running metrics that we are keeping track of
                numNegs = 0;
                crrProdTillFirstNeg = 1;
                crrProd = 1;
                crrProdFromLastNeg = 1;
                crrWinStartIdx = i + 1;
            } else {
                crrProd *= crrEle;                       // update current window running product
                int crrWinLen = i - crrWinStartIdx + 1;  // determine current window length

                if (crrEle < 0) {
                    // increment neg numbers counter
                    numNegs++;
                    if (numNegs == 1) {
                        // if this was first neg no seen, capture the value (done only once in every window)
                        crrProdTillFirstNeg = crrProd;
                    }
                    // 'reset' product from last negative (will be done every time a new negative no is seen)
                    crrProdFromLastNeg = crrEle;
                } else {
                    if (numNegs >= 1) {
                        // update product from last negative
                        crrProdFromLastNeg *= crrEle;
                    }
                }

                if ((numNegs % 2) == 0) {
                    // if we have even no of negative nos in current window, then product will be positive;
                    // so simply update the maxProd
                    maxProd = max(maxProd, crrProd);
                } else {
                    if (crrWinLen == 1) {
                        // single neg element seent -> do nothing
                    } else {
                        maxProd = max(
                            maxProd,
                            max(
                                (crrProd / crrProdTillFirstNeg),  // product of nums after first neg until this point
                                (crrProd / crrProdFromLastNeg)    // product of nums from beginning of window till last neg
                                ));
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