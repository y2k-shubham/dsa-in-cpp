// LeetCode-509: https://leetcode.com/problems/fibonacci-number/
// your'e really gonna read solution to this question? utterly shameless

class Solution {
   public:
    int fib(int n) {
        if (n == 0) {
            return 0;
        }
        if (n <= 2) {
            return 1;
        }

        int prev2 = 1;
        int prev1 = 1;
        for (int i = 3; i <= n; i++) {
            int crr = prev2 + prev1;

            prev2 = prev1;
            prev1 = crr;
        }

        return prev1;
    }
};
