// LeetCode-1784: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/
// Easy

#include <string>

using namespace std;

class Solution {
private:
    int findNextIdxForChar(string& str, const char ch, int beginIdx) {
        int len = str.size();

        int i = beginIdx;
        while ((i < len) && (str.at(i) != ch)) {
            i++;
        }

        return i;
    }

public:
    bool checkOnesSegment(string s) {
        int len = s.size();
        if (len <= 0) {
            return false;
        }

        int first1Idx = findNextIdxForChar(s, '1', 0);
        if (first1Idx >= len) {
            return true;
        }

        int next0Idx = findNextIdxForChar(s, '0', first1Idx);
        if (next0Idx >= len) {
            return true;
        }

        int next1Idx = findNextIdxForChar(s, '1', next0Idx);
        if (next1Idx >= len) {
            return true;
        }

        return false;
    }
};
