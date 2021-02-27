// LeetCode-946: https://leetcode.com/problems/validate-stack-sequences/
// LC Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3653/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if (pushed.size() != popped.size()) {
            return false;
        }

        int len = pushed.size();
        if (len == 0) {
            return true;
        }
        if (len == 1) {
            return pushed[0] == popped[0];
        }

        stack<int> stk;

        int pushIdx = 0;
        int popIdx = 0;
        while (popIdx < len) {
            if (!stk.empty() && (stk.top() == popped[popIdx])) {
                stk.pop();
                popIdx++;
            } else if (pushIdx < len) {
                stk.push(pushed[pushIdx]);
                pushIdx++;
            } else {
                return false;
            }
        }

        return (stk.empty()) && (pushIdx == len) && (popIdx == len);
    }
};
