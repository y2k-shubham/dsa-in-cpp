// LeetCode-1015: https://leetcode.com/problems/smallest-integer-divisible-by-k/
// solved by referring to hints given on LC problem page itself

#include <unordered_set>

using namespace std;

class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (((k % 2) == 0) || ((k % 5) == 0)) {
            return -1;
        }

        int numDigits = 1;

        int crrRem = 1 % k;
        if (crrRem == 0) {
            return numDigits;
        }

        unordered_set<int> seenRems = {crrRem};
        while (true) {
            ++numDigits;

            int newRem = ((crrRem * 10) + 1) % k;
            if (newRem == 0) {
                return numDigits;
            } else if (seenRems.find(newRem) == seenRems.end()) {
                seenRems.insert(newRem);
            } else {
                return -1;
            }

            crrRem = newRem;
        }

        return -1;
    }
};
