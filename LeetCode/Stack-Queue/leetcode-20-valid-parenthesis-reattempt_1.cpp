// LeetCode-20: https://leetcode.com/problems/valid-parentheses/
// GFG: https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>

using namespace std;

class Solution {
public:
    map<char, char> buildBracketMap() {
        // g++ -std=c++11 LeetCode/Stack-Queue/valid-parentheses.cpp
        map<char, char> bracketMap = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'}};
        return bracketMap;
    }

    bool isValidAtmpt1(string s) {
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

            return stk.empty();
        }
    }

    bool isValidAtmpt2(string str) {
        if (str.empty()) {
            return true;
        }
        
        int len = str.size();
        if ((len % 2) == 1) {
            return false;
        }
        
        map <char, char> bracketMap = buildBracketMap();
        
        stack <char> bracketStack;
        for (int i = 0; i < len; i++) {
            char ch = str.at(i);
            
            if (bracketMap.find(ch) != bracketMap.end()) {
                // some opening bracket found
                bracketStack.push(ch);
            } else {
                // some closing bracket found
                
                if (!bracketStack.empty() && (bracketMap[bracketStack.top()] == ch)) {
                    bracketStack.pop();
                } else {
                    return false;
                }
            }
        }
        
        return bracketStack.empty();
    }
    
    bool isValid(string s) {
        return isValidAtmpt2(s);
    }
    
};
