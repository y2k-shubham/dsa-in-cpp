// LeetCode-1688: https://leetcode.com/problems/count-of-matches-in-tournament/
// do-as-directed (dumb problem; don't bother looking)

class Solution {
private:
    inline bool isEven(int n) {
        return (n & 1) == 0;
    }

public:
    int numberOfMatches(int n) {
        if (n < 2) {
            return 0;
        } else if (n == 2) {
            return 1;
        } else {
            if (isEven(n)) {
                return (n / 2) + numberOfMatches(n / 2);
            } else {
                return ((n - 1) / 2) + numberOfMatches(1 + ((n - 1) / 2));
            }
        }
    }
};
