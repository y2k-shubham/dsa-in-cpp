// LeetCode-238: https://leetcode.com/problems/product-of-array-except-self

#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildPrefixProd(vector<int>& vec) {
        int len = vec.size();
        vector<int> prefProd(len, 1);

        int prod = 1;
        for (int i = 0; i < len; i++) {
            prod *= vec[i];
            prefProd[i] = prod;
        }

        return prefProd;
    }

    vector<int> buildSuffixProd(vector<int>& vec) {
        int len = vec.size();
        vector<int> suffProd(len, 1);

        int prod = 1;
        for (int i = len - 1; i >= 0; i--) {
            prod *= vec[i];
            suffProd[i] = prod;
        }

        return suffProd;
    }

    vector<int> buildExceptItselfProd1(vector<int>& vec) {
        int len = vec.size();
        vector<int> exceptItselfProd(len, 1);

        // technically we could've just built suffix prod array
        // and used a prod variable for holding prefix prod on the fly
        vector<int> prefixProd = buildPrefixProd(vec);
        vector<int> suffixProd = buildSuffixProd(vec);

        for (int i = 0; i < len; i++) {
            int prefProd = (i == 0) ? 1 : prefixProd[i - 1];
            int suffProd = (i == (len - 1)) ? 1 : suffixProd[i + 1];
            exceptItselfProd[i] = prefProd * suffProd;
        }

        return exceptItselfProd;
    }

    vector<int> buildExceptItselfProd2(vector<int>& vec) {
        int len = vec.size();

        vector<int> exceptItselfProd = buildSuffixProd(vec);
        int prefixProd = 1;

        for (int i = 0; i < len; i++) {
            prefixProd *= (i == 0) ? 1 : vec[i - 1];
            int suffixProd = (i == (len - 1)) ? 1 : exceptItselfProd[i + 1];
            exceptItselfProd[i] = prefixProd * suffixProd;
        }

        return exceptItselfProd;
    }

   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        return buildExceptItselfProd2(nums);
    }
};