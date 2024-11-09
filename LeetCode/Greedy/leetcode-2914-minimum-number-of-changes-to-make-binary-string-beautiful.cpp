// LeetCode-2914: https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/

// Solution is super simple, intuition is not
// Implemented after looking at hint + NeetCode: https://www.youtube.com/watch?v=qhxhrTA4HJw

#include <string>

using namespace std;

class Solution {
public:
    int minChanges(string s) {
        int len = s.size();
        if ((len & 1) == 1) {
            // odd length string
            return false;
        }

        int numSwaps = 0;
        for (int i = 1; i < len; i += 2) {
            if (s.at(i - 1) != s.at(i)) {
                ++numSwaps;
            }
        }

        return numSwaps;
    }
};
