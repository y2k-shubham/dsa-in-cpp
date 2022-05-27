// LeetCode-1359: https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
// Cat Racket soln: https://youtu.be/H0Yl1AlUuK8?t=250
// (very hard permutations problem)

class Solution {
    const int MOD = 1000000007;

   public:
    int countOrders(int n) {
        if (n == 1) {
            return 1;
        }

        // solution is n! * (1 * 3 * 5 * .. (2n - 1))
        long long int prod = 1;
        for (int i = 1; i <= n; i++) {
            prod *= i;
            prod %= MOD;

            prod *= (2 * i) - 1;
            prod %= MOD;
        }

        return (int)prod;
    }
};
