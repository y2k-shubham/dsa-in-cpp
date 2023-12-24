// LeetCode-1758: https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string

#include <string>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        if (s.size() <= 1) {
            return 0;
        }

        int numEvenIdx0s = 0;
        int numOddIdx0s = 0;
        int numEvenIdx1s = 0;
        int numOddIdx1s = 0;

        int idx = 0;
        for (char c: s) {
            if (c == '0') {
                if ((idx & 1) == 0) {
                    numEvenIdx0s++;
                } else {
                    numOddIdx0s++;
                }
            } else {
                if ((idx & 1) == 0) {
                    numEvenIdx1s++;
                } else {
                    numOddIdx1s++;
                }
            }

            idx++;
        }

        // no of flips required if we want 0s at even indexes (and therefore 1s at odd indexes)
        int numFlipsToHave0sAtEvenIdxs = numOddIdx0s + numEvenIdx1s;
        // no of flips required if we want 1s at even indexes (and therefore 0s at odd indexes)
        int numFlipsToHave0sAtOddIdxs = numEvenIdx0s + numOddIdx1s;

        return min(numFlipsToHave0sAtEvenIdxs, numFlipsToHave0sAtOddIdxs);
    }
};
