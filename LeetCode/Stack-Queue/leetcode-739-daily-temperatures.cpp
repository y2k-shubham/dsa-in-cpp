// LeetCode-739: https://leetcode.com/problems/daily-temperatures/

#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildNgeRight(vector<int>& vec) {
        int len = vec.size();

        vector<int> ngeRight(len, INT_MAX);
        stack<int> stk;
        for (int i = len - 1; i >= 0; i--) {
            int ele = vec[i];

            while (!stk.empty() && (vec[stk.top()] <= ele)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeRight[i] = stk.top();
            }

            stk.push(i);
        }

        return ngeRight;
    }

    vector<int> buildIdxDiffArr(vector<int>& ngeRight) {
        int len = ngeRight.size();

        vector<int> idxDiffArr(len, 0);
        for (int i = 0; i < len; i++) {
            if (ngeRight[i] != INT_MAX) {
                idxDiffArr[i] = ngeRight[i] - i;
            }
        }

        return idxDiffArr;
    }

   public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int len = temperatures.size();
        if (len == 1) {
            return {0};
        }

        vector<int> ngeRight = buildNgeRight(temperatures);
        vector<int> idxDiffArr = buildIdxDiffArr(ngeRight);

        return idxDiffArr;
    }
};
