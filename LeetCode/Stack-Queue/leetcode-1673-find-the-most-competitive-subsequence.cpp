// LeetCode-1673: https://leetcode.com/problems/find-the-most-competitive-subsequence/
// O(n) soln using 'monotonic stack': https://www.youtube.com/watch?v=Ol7yz0XKKLw

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    stack<int> buildMonoIncStack(vector<int>& vec, int k) {
        int len = vec.size();

        stack<int> stk;
        int elesToRemove = len - k;

        for (int i = 0; i < len; i++) {
            int crrEle = vec[i];

            if (stk.empty() || (stk.top() <= crrEle)) {
                stk.push(crrEle);
            } else {
                while (!stk.empty() && (elesToRemove >= 1) && (stk.top() > crrEle)) {
                    stk.pop();
                    elesToRemove--;
                }
                stk.push(crrEle);
            }
        }

        while (elesToRemove > 0) {
            stk.pop();
            elesToRemove--;
        }

        return stk;
    }

    vector<int> convertToVec(stack<int> stk) {
        int len = stk.size();
        vector<int> vec(len);

        for (int i = 0; i < len; i++) {
            vec[i] = stk.top();
            stk.pop();
        }

        reverse(vec.begin(), vec.end());

        return vec;
    }

   public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int len = nums.size();
        if (len == k) {
            return nums;
        }

        stack<int> stk = buildMonoIncStack(nums, k);
        return convertToVec(stk);
    }
};
