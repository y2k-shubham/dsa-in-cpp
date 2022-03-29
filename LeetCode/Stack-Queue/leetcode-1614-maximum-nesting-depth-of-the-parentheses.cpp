// LeetCode-1614: https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/

#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    int maxDepth(string s) {
        stack<int> stk;

        int maxNestingDepth = 0;

        int i = 0;
        while (i < s.size()) {
            char ch = s.at(i);

            switch (ch) {
                case '(':
                    stk.push(i);
                    maxNestingDepth = max(maxNestingDepth, (int) stk.size());
                    break;

                case ')':
                    stk.pop();
                    break;

                default:
                    break;
            }

            i++;
        }

        return maxNestingDepth;
    }
};
