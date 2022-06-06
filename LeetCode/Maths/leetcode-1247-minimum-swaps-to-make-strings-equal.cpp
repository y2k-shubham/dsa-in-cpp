// LeetCode-1247: https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/

// definitely NOT a medium difficulty problem (identifying the pattern is pretty hard)
// Algorithm Casts: https://www.youtube.com/watch?v=iplciPpgL2A

#include <string>

using namespace std;

class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int numXYPairs = 0;
        int numYXPairs = 0;

        for (int i = 0; i < s1.size(); i++) {
            char ch1 = s1.at(i);
            char ch2 = s2.at(i);

            if (ch1 == ch2) {
                continue;
            } else if (ch1 == 'x') {
                numXYPairs++;
            } else {
                numYXPairs++;
            }
        }

        bool hasEvenXYPairs = (numXYPairs % 2) == 0;
        bool hasEvenYXPairs = (numYXPairs % 2) == 0;

        int ans;
        if (hasEvenXYPairs && hasEvenYXPairs) {
            ans = (numXYPairs / 2) + (numYXPairs / 2);
        } else if (!hasEvenXYPairs && !hasEvenYXPairs) {
            ans = (numXYPairs / 2) + (numYXPairs / 2) + 2;
        } else {
            ans = -1;
        }

        return ans;
    }
};
