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

        vector<int> prefixProd = buildPrefixProd(vec);
        vector<int> suffixProd = buildSuffixProd(vec);

        for (int i = 0; i < len; i++) {
            int prefProd = (i == 0) ? 1 : prefixProd[i - 1];
            int suffProd = (i == (len - 1)) ? 1 : suffixProd[i + 1];
            exceptItselfProd[i] = prefProd * suffProd;
        }

        return exceptItselfProd;
    }

   public:
    vector<int> productExceptSelf(vector<int>& nums) {
        return buildExceptItselfProd1(nums);
    }
};
