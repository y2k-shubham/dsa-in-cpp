// LeetCode-784: https://leetcode.com/problems/letter-case-permutation/
// Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3642/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void genPerms(string str, int idx, vector<string>& perms) {
        if (idx < str.size()) {
            char ch = str.at(idx);

            if ('a' <= ch && ch <= 'z') {
                // keep it as-it-is
                genPerms(str, idx + 1, perms);
                // convert to uppercase
                str[idx] = toupper(ch);
                genPerms(str, idx + 1, perms);
            } else if ('A' <= ch && ch <= 'Z') {
                // keep it as-it-is
                genPerms(str, idx + 1, perms);
                // convert to lowercase
                str[idx] = tolower(ch);
                genPerms(str, idx + 1, perms);
            } else {
                // no-op (just make recursive call without changing anything at current posn)
                genPerms(str, idx + 1, perms);
            }
        } else {
            // permutation generated -> persist it in the list
            perms.push_back(str);
        }
    }

    vector<string> letterCasePermutation(string S) {
        vector<string> perms;
        genPerms(S, 0, perms);

        return perms;
    }
};
