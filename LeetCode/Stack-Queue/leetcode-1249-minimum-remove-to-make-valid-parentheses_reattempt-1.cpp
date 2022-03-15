// LeetCode-1249: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

/**
 * "lee(t(c)o)de)"
 * "a)b(c)d"
 * "))(("
 * "l(ee(t(c)o)de)"
 * "l(ee(t(c)o)de)("
 * "l(ee(t(c)o)de)()"
 * "l(ee(t(c)o)de)())("
 * "a)b(c)d("
 * "a)b((c)d("
 * "a)b()(c)d("
 * "a)b()(c)d())"
 * ")))(("
 * ")))()("
 * ")))()(()"
 * "()"
 * "(a)"
 * "()a"
 * "a()"
 * "("
 * "a("
 * "(a"
 * ")"
 * "a)"
 * ")a"
 * "a"
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    void showIllegalChars(string& str, stack<int> illegalCharIdxs) {
        cout << str << endl;

        for (int i = 0; !illegalCharIdxs.empty() && (i < str.size()); i++) {
            if (i == illegalCharIdxs.top()) {
                printf("^");
                illegalCharIdxs.pop();
            } else {
                printf(" ");
            }
        }

        cout << endl;
    }

    vector<int> determineIllegalCharIdxs(string& str) {
        vector<int> illegalCharIdxs;

        stack<int> openParenIdxs;
        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);

            if (ch == '(') {
                openParenIdxs.push(i);
            } else if (ch == ')') {
                if (openParenIdxs.empty()) {
                    illegalCharIdxs.push_back(i);
                } else {
                    openParenIdxs.pop();
                }
            } else {
                // do nothing
            }
        }

        // remove all trailing open brackets
        while (!openParenIdxs.empty()) {
            illegalCharIdxs.push_back(openParenIdxs.top());
            openParenIdxs.pop();
        }

        return illegalCharIdxs;
    }

    stack<int> convertVecToStack(vector<int>& mVec) {
        if (mVec.empty()) {
            stack<int> mStk;
            return mStk;
        }

        sort(mVec.begin(), mVec.end());
        reverse(mVec.begin(), mVec.end());

        stack<int> mStk;
        for (int i = 0; i < mVec.size(); i++) {
            mStk.push(mVec[i]);
        }

        return mStk;
    }

    string removeIllegalChars(string& str, stack<int>& illegalCharIdxs) {
        if (illegalCharIdxs.empty()) {
            return str;
        }

        ostringstream oss;
        int len = str.size();
        int i;

        for (i = 0; !illegalCharIdxs.empty() && (i < len); i++) {
            if (i == illegalCharIdxs.top()) {
                // printf("skipping i=%d\n", i);
                illegalCharIdxs.pop();
            } else {
                oss << str.at(i);
            }
        }

        while (i < len) {
            // printf("adding i=%d\n", i);
            oss << str.at(i++);
        }

        return oss.str();
    }

   public:
    string minRemoveToMakeValid(string s) {
        vector<int> illegalCharIdxsVec = determineIllegalCharIdxs(s);
        int numIllegalChars = illegalCharIdxsVec.size();

        if (numIllegalChars == 0) {
            return s;
        }
        if (numIllegalChars == s.size()) {
            return "";
        }

        stack<int> illegalCharIdxsStk = convertVecToStack(illegalCharIdxsVec);
        // showIllegalChars(s, illegalCharIdxsStk);

        return removeIllegalChars(s, illegalCharIdxsStk);
    }
};
