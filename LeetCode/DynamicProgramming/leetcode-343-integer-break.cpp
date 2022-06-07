// LeetCode-343: https://leetcode.com/problems/integer-break/

#include <unordered_map>

using namespace std;

class Solution {
private:
    int integerBreakRec(int n, unordered_map<int, int>& memoMap) {
        if (memoMap.find(n) != memoMap.end()) {
            return memoMap[n];
        }

        int maxProd = n - 1;
        for (int i = 2; i < n; i++) {
            int crrProd1 = i * integerBreakRec(n - i, memoMap);
            int crrProd2 = i * (n - i);

            maxProd = max(maxProd, max(crrProd1, crrProd2));
        }

        memoMap[n] = maxProd;
        return maxProd;
    }

    // top-down; runtime 7 ms (5 %tile)
    int integerBreakTopDown(int n) {
        unordered_map<int, int> memoMap = {
                {1, 1},
                {2, 1}
        };
        return integerBreakRec(n, memoMap);
    }

    // bottom-up runtime 0 ms (100 %tile)
    int integerBreakBottomUp(int n) {
        unordered_map<int, int> memoMap = {
                {1, 1},
                {2, 1}
        };
        for (int i = 3; i <= n; i++) {
            memoMap[i] = integerBreakRec(i, memoMap);
        }

        return memoMap[n];
    }

public:
    int integerBreak(int n) {
        // return integerBreakTopDown(n);
        return integerBreakBottomUp(n);
    }
};
