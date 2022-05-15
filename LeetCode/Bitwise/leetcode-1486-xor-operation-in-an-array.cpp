// LeetCode-1486: https://leetcode.com/problems/xor-operation-in-an-array/
// why? [hint: dont even read the problem description]

class Solution {
public:
    int xorOperation(int n, int start) {
        int _xor = 0;

        for (int i = 0; i < n; i++) {
            _xor ^= start + (2 * i);
        }

        return _xor;
    }
};
