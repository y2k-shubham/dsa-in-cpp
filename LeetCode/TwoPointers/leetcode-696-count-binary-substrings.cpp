// LeetCode-696: https://leetcode.com/problems/count-binary-substrings/

#include <iostream>

using namespace std;

class Solution {
private:
    int findNextJnIdx(string& str, int afterIdx) {
        int len = str.size();

        for (int i = (afterIdx + 1); i < (len - 1); i++) {
            if (str.at(i) != str.at(i + 1)) {
                return i;
            }
        }

        return len;
    }

    int countBinarySubstrsAtJn(string& str, int lCenterIdx) {
        int len = str.size();

        int iLo = lCenterIdx;
        int iHi = lCenterIdx + 1;

        char chLo = str.at(iLo);
        char chHi = str.at(iHi);

        int numSubstrs = 0;
        while ((iLo >= 0) && (iHi < len)) {
            if ((str.at(iLo) == chLo) && (str.at(iHi) == chHi)) {
                ++numSubstrs;
                iLo--;
                iHi++;
            } else {
                break;
            }
        }

        return numSubstrs;
    }

public:
    int countBinarySubstrings(string s) {
        int len = s.size();
        int totalNumSubstrs = 0;

        int i = -1;
        while (i < len) {
            i = findNextJnIdx(s, i);
            if (i >= len) {
                break;
            }

            int crrNumSubstrs = countBinarySubstrsAtJn(s, i);
            totalNumSubstrs += crrNumSubstrs;

            // still not sure why we had to add -1 here;
            // although this is merely an optimization step,
            // even doing a i += 1 would've sufficed
            i += crrNumSubstrs - 1;
        }

        return totalNumSubstrs;
    }
};
