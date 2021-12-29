// LeetCode-20: https://leetcode.com/problems/valid-parentheses/
// GFG: https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>

using namespace std;

map<char, char> buildBracketMap();
bool isValid(string s);

int main() {
    assert(isValid("()"));
    assert(isValid("()[]{}"));
    assert(isValid("(]") == false);
    assert(isValid("([)]") == false);
    assert(isValid("{[]}"));

    return 0;
}

map<char, char> buildBracketMap() {
    // g++ -std=c++11 LeetCode/Stack-Queue/valid-parentheses.cpp
    map<char, char> bracketMap = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'}};
    return bracketMap;
}

bool isValid(string s) {
    if (s.empty()) {
        return true;
    } else {
        bool debug = false;

        map<char, char> bracketMap = buildBracketMap();
        stack<char> stk;

        for (int i = 0; i < s.size(); i++) {
            char c = s.at(i);
            if (debug) {
                printf("\n-------\n");
                printf("at s[%d] = %c\n", i, c);
            }

            if (bracketMap.find(c) != bracketMap.end()) {
                if (debug) {
                    printf("pushing opening bracked to stack\n");
                }
                stk.push(c);
            } else {
                if (debug) {
                    if (stk.empty()) {
                        printf("stack empty\n");
                    } else {
                        printf("stack top = %c\n", stk.top());
                    }
                }
                if (!stk.empty() && c == bracketMap[stk.top()]) {
                    if (debug) {
                        printf("match, popping %c from stack\n", stk.top());
                    }
                    stk.pop();
                } else {
                    if (debug) {
                        printf("stack-empty / mis-match, return false\n");
                    }
                    return false;
                }
            }
        }

        // this is important
        return stk.empty();
    }
}
