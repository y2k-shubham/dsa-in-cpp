// LeetCode-389 https://leetcode.com/problems/find-the-difference/
// too easy; better dont look

#include <iostream>

using namespace std;

class Solution {
   private:
    char calcXor(string str) {
        char _xor = '\0';

        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);
            _xor ^= ch;
        }

        return _xor;
    }

   public:
    char findTheDifference(string s, string t) {
        if (s.empty()) {
            return t.at(0);
        }

        return calcXor(s) ^ calcXor(t);
    }
};
