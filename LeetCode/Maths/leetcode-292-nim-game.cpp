// LeetCode-292: https://leetcode.com/problems/nim-game/

class Solution {
public:
    // create a table to understand the logic
    bool canWinNim(int n) {
        return (n % 4) != 0;
    }
};
