// LeetCode-762: https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/

using namespace std;

class Solution {
private:
    bool isPrime(int num) {
        if (num <= 1) {
            return false;
        }

        int halfNum = num / 2;
        for (int i = 2; i <= halfNum; i++) {
            if ((num % i) == 0) {
                return false;
            }
        }

        return true;
    }

public:
    int countPrimeSetBits(int left, int right) {
        int numIntegersWithNoOfSetBitsBeingPrime = 0;

        for (int i = left; i <= right; i++) {
            // library utility suggested by Microsoft Copilot
            int numSetBits = __builtin_popcount(i);

            if (isPrime(numSetBits)) {
                numIntegersWithNoOfSetBitsBeingPrime++;
            }
        }

        return numIntegersWithNoOfSetBitsBeingPrime;
    }
};
