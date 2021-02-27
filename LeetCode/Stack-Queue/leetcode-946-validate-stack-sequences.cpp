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
        /**
         * note that here the check is only for popIdx & not pushIdx because
         * 'pushed' sequence will be run-through earlier than 'popped' sequence
         * (if that doesn't happen, then it will be an invalid sequence-pair
         * & we'll end up in last 'else' clase thereby returning false)
         */
        while (popIdx < len) {
            /**
              * note that even in case of duplicates (where there is ambiguity whether
              * to pop an item first or push an item first), this approach (of trying to pop first
              * before trying to push) would still work since
              * here we dont have to arrive at any specific order of pushes & pops; rather
              * we only have to establish that there is some order that can result in given sequences
              */
            if (!stk.empty() && (stk.top() == popped[popIdx])) {
                //first we try to pop items from stack
                stk.pop();
                popIdx++;
            } else if (pushIdx < len) {
                // if pop noo possible, then we try to push to stack
                stk.push(pushed[pushIdx]);
                pushIdx++;
            } else {
                // if neither is possible, we've found an invalid pair of sequnces
                return false;
            }
        }

        // all pre-requisites should have been met
        return (stk.empty()) && (pushIdx == len) && (popIdx == len);
    }
};
