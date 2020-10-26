// LeetCode-844: https://leetcode.com/problems/backspace-string-compare/

#include <cstdio>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

stack<char> getProcessedStringStack(string str) {
    stack<char> stk;

    for (int i = 0; i < str.size(); i++) {
        char ch = str.at(i);
        if (ch == '#') {
            if (!stk.empty()) {
                stk.pop();
            }
        } else {
            stk.push(ch);
        }
    }

    return stk;
}

string convertStackToString(stack<char> stk) {
    string str;

    while (!stk.empty()) {
        str = str + stk.top();
        stk.pop();
    }

    reverse(str.begin(), str.end());

    return str;
}

string getProcessedString(string str) {
    stack<char> strStk = getProcessedStringStack(str);
    return convertStackToString(strStk);
}

bool backspaceCompare(string S, string T) {
    return getProcessedString(S) == getProcessedString(T);
}
