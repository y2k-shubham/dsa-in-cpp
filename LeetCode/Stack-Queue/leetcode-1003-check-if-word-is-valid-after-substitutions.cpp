// LeetCode-1003: https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

class Solution {
   private:
    bool debug = false;

    bool isABC(string& str) {
        return str == "abc";
    }

    bool isPrefixOfABC(string& str) {
        return (str == "") || (str == "a") || (str == "ab") || isABC(str);
    }

   public:
    friend class SolutionTest;

    bool isValid(string str) {
        stack<string> stk;

        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);
            string strTop = stk.empty() ? "" : stk.top();

            string concatStr = strTop + ch;
            if (debug) {
                printf("\n---------\n");
                printf("at str[i=%d] = %c, stk.top() = %s, concat = %s\n", i, ch, (stk.empty() ? "null" : strTop).c_str(), concatStr.c_str());
            }

            if (isABC(concatStr)) {
                if (debug) {
                    printf("concat is ABC, popping stk.top() = %s\n", strTop.c_str());
                }
                stk.pop();
            } else if (isPrefixOfABC(concatStr)) {
                if (!stk.empty()) {
                    stk.pop();
                    if (debug) {
                        printf("concat is prefix of ABC, popping stk.top() = %s and pushing concat = %s\n", strTop.c_str(), concatStr.c_str());
                    }
                } else {
                    if (debug) {
                        printf("concat is prefix of ABC, but stack is empty, pushing concat = %s\n", concatStr.c_str());
                    }
                }
                stk.push(concatStr);
            } else {
                if (ch == 'a') {
                    if (debug) {
                        printf("concat is niether and ch is 'a', pushing 'a'\n");
                    }
                    // char to string: https://stackoverflow.com/a/17201751/3679900
                    string chStr(1, ch);
                    stk.push(chStr);
                } else {
                    if (debug) {
                        printf("concat is niether and ch is NOT 'a', returning false\n");
                    }
                    return false;
                }
            }
        }

        return stk.empty();
    }
};

class SolutionTest {
   public:
    void testIsValid() {
        Solution soln = Solution();
        string strIn;
        bool outExpected, outComputed;

        cout << 1 << endl;
        strIn = "";
        outExpected = true;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);

        cout << 2 << endl;
        // soln.debug = true;
        strIn = "a";
        outExpected = false;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);
        // soln.debug = false;

        cout << 3 << endl;
        strIn = "ab";
        outExpected = false;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);

        cout << 4 << endl;
        strIn = "bc";
        outExpected = false;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);

        cout << 5 << endl;
        strIn = "abc";
        outExpected = true;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);

        cout << 6 << endl;
        strIn = "aabcbc";
        outExpected = true;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);

        strIn = "aababccbc";
        outExpected = true;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);

        strIn = "aababcacbc";
        outExpected = false;
        outComputed = soln.isValid(strIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testIsValid();
    return 0;
}
