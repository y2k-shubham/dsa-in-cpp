// LeetCode-20: https://leetcode.com/problems/valid-parentheses/

#include <cstdio>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
   private:
    unordered_map<char, char> brackPairs;
    unordered_map<char, char> revBrackPairs;

    void createBrackPairsMap() {
        brackPairs['('] = ')';
        brackPairs['{'] = '}';
        brackPairs['['] = ']';
    }

    void createRevBrackPairsMap() {
        revBrackPairs[')'] = '(';
        revBrackPairs['}'] = '{';
        revBrackPairs[']'] = '[';
    }

   public:
    bool isValid(string s) {
        int len = s.size();
        if ((len % 2) == 1) {
            return false;
        }

        createBrackPairsMap();
        createRevBrackPairsMap();

        stack<char> stk;

        for (int i = 0; i < len; i++) {
            char ch = s.at(i);

            bool isOpenBrack = brackPairs.find(ch) != brackPairs.end();
            if (isOpenBrack) {
                stk.push(ch);
            } else {
                char oppCh = revBrackPairs[ch];
                if (!stk.empty() && (stk.top() == oppCh)) {
                    stk.pop();
                } else {
                    return false;
                }
            }
        }

        return stk.empty();
    }
};
