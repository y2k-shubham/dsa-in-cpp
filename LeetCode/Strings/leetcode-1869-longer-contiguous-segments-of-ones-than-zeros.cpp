// LeetCode-1869: https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/

#include <string>
#include <cassert>

using namespace std;

class Solution {
private:
    int swallowChars(string& str, int startIdx) {
        int len = str.size();
        char startChar = str[startIdx];

        int idx = startIdx;
        while ((idx < len) && (str[idx] == startChar)) {
            idx++;
        }

        return idx;
    }

public:
    bool checkZeroOnes(string s) {
        int len = s.size();
        if (len <= 0) {
            return false;
        }

        int longest1sSegmentLen = 0;
        int longest0sSegmentLen = 0;

        int crrDig = s.at(0) - '0';
        int i = 0;
        while (i < len) {
            int iNext = swallowChars(s, i);
            int crrSegmentLen = iNext - i;

            if (crrDig == 1) {
                longest1sSegmentLen = max(longest1sSegmentLen, crrSegmentLen);
            } else {
                longest0sSegmentLen = max(longest0sSegmentLen, crrSegmentLen);
            }

            crrDig = 1 - crrDig;
            i = iNext;
        }

        return longest1sSegmentLen > longest0sSegmentLen;
    }
};
