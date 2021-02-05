// LeetCode-71: https://leetcode.com/problems/simplify-path/
// Feb-2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3629/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

class Solution {
   public:
    bool isSlash(string path, int idx) {
        return path.at(idx) == '/';
    }

    bool isSingleDot(string path, int idx) {
        int len = path.size();

        bool is1Dot = (path.at(idx) == '.');
        bool areNotMoreThan1Dot = ((idx + 1 >= len) || (path.at(idx + 1) == '/'));

        return is1Dot && areNotMoreThan1Dot;
    }

    bool areDoubleDots(string path, int idx) {
        int len = path.size();

        bool are2Dots = (path.at(idx) == '.') && ((idx + 1) < len) && (path.at(idx + 1) == '.');
        bool areNotMoreThan2Dots = ((idx + 2) >= len) || (path.at(idx + 2) == '/');

        return are2Dots && areNotMoreThan2Dots;
    }

    int eatAllSlashes(string path, int idx) {
        int i;
        for (i = idx; i < path.size() && path.at(i) == '/'; i++) {
            // do nothing
        }

        return i;
    }

    pair<string, int> eatUntilSlash(string path, int idx) {
        ostringstream oss;
        int i;
        for (i = idx; i < path.size() && path.at(i) != '/'; i++) {
            oss << path.at(i);
        }

        return {oss.str(), i};
    }

    stack<string> buildStack(string path) {
        stack<string> stk;

        for (int i = 0; i < path.size();) {
            if (isSlash(path, i)) {
                i = eatAllSlashes(path, i);
            } else if (isSingleDot(path, i)) {
                // do nothing
                i++;
            } else if (areDoubleDots(path, i)) {
                if (stk.empty()) {
                    // invalid pattern
                } else {
                    // move up one directory
                    stk.pop();
                }
                i += 2;
            } else {
                pair<string, int> eatResult = eatUntilSlash(path, i);
                stk.push(eatResult.first);
                i = eatResult.second;
            }
        }

        return stk;
    }

    stack<string> reverseStack(stack<string> stk) {
        stack<string> revStack;

        while (!stk.empty()) {
            revStack.push(stk.top());
            stk.pop();
        }

        return revStack;
    }

    string convertToPath(stack<string> stk) {
        if (stk.empty()) {
            return "/";
        }

        ostringstream oss;
        while (!stk.empty()) {
            oss << "/" << stk.top();
            stk.pop();
        }

        return oss.str();
    }

    // LC-submission: speed 9 %tile, memory 5 %tile
    string simplifyPath(string path) {
        stack<string> stk = buildStack(path);
        stack<string> revStk = reverseStack(stk);
        return convertToPath(revStk);
    }
};
