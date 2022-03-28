// LeetCode-921: https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/

#include <stack>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<int> openParens;
        stack<int> closeParens;

        for (int i = 0; i < s.size(); i++) {
            char ch = s.at(i);

            switch (ch) {
                case '(':
                    openParens.push(i);
                    break;

                case ')':
                    if (!openParens.empty()) {
                        openParens.pop();
                    } else {
                        closeParens.push(i);
                    }
                    break;

                default:
                    return INT_MIN;
            }
        }

        return ((int) openParens.size()) + ((int) closeParens.size());
    }
};
