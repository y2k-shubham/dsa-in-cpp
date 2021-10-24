// LeetCode-1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
// Solution by NareshGupta: https://www.youtube.com/watch?v=muDlIlVE1q4

// identical to LeetCode-316: https://leetcode.com/problems/remove-duplicate-letters/
// LeetCode-316 (more) complex implementation: https://github.com/y2k-shubham/dsa-in-cpp/blob/master/LeetCode/Greedy/leetcode-316-remove-duplicate-letters.cpp

#include <cstdio>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<char, int> buildLastIdxMap(string& str) {
        unordered_map<char, int> lastIdxMap;

        for (int i = 0; i < str.size(); i++) {
            lastIdxMap[str.at(i)] = i;
        }

        return lastIdxMap;
    }

    unordered_map<char, bool> buildIncludedMap() {
        unordered_map<char, bool> includedMap;

        for (char ch = 'a'; ch <= 'z'; ch++) {
            includedMap[ch] = false;
        }

        return includedMap;
    }

    stack<char> buildSubseqStack(string& str) {
        int len = str.size();

        unordered_map<char, int> lastIdxMap = buildLastIdxMap(str);
        unordered_map<char, bool> includedMap = buildIncludedMap();

        stack<char> subseqStack;
        for (int i = 0; i < len; i++) {
            char crrCh = str.at(i);
            if (includedMap[crrCh]) {
                // char already picked; skip
                continue;
            }

            while (!subseqStack.empty() && (crrCh < subseqStack.top()) && (lastIdxMap[subseqStack.top()] > i)) {
                // pop out all 'popp-able' chars from stack that are greater than crrCh
                includedMap[subseqStack.top()] = false;
                subseqStack.pop();
            }

            // put crrCh in stack & update in inclusion map
            subseqStack.push(crrCh);
            includedMap[crrCh] = true;
        }

        return subseqStack;
    }

    string convertToRevStr(stack<char>& stk) {
        string str = "";

        while (!stk.empty()) {
            str = stk.top() + str;
            stk.pop();
        }

        return str;
    }

   public:
    string smallestSubsequence(string text) {
        int len = text.size();
        if (len <= 1) {
            return text;
        }

        stack<char> subseqStack = buildSubseqStack(text);
        return convertToRevStr(subseqStack);
    }
};
