// LeetCode-344: https://leetcode.com/problems/reverse-string/
// who creates such dumb problems?

#include <vector>

using namespace std;

class Solution {
public:
    void reverseString(vector<char> &s) {
        int len = s.size();
        if (len <= 1) {
            return;
        }

        for (int i = 0; i < (len / 2); i++) {
            char tmpCh = s[i];
            s[i] = s[len - i - 1];
            s[len - i - 1] = tmpCh;
        }
    }
};
