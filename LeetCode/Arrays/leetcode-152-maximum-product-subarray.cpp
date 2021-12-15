// LeetCode-152: https://leetcode.com/problems/maximum-product-subarray/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
   public:
    int maxProduct(vector<int>& nums) {
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
};