// LeetCode-1295: https://leetcode.com/problems/find-numbers-with-even-number-of-digits/

#include <vector>

using namespace std;

class Solution {
private:
    int countNumDigits(int n) {
        int numDigits = 0;

        while (n > 0) {
            n /= 10;
            numDigits++;
        }

        return numDigits;
    }

    bool isEven(int n) {
        return (n & 1) == 0;
    }

    bool hasEvenNumOfDigits(int n) {
        int numDigits = countNumDigits(n);
        return isEven(numDigits);
    }

public:
    int findNumbers(vector<int>& nums) {
        int numValsMatchingCriteria = 0;

        for (int num: nums) {
            if (hasEvenNumOfDigits(num)) {
                numValsMatchingCriteria++;
            }
        }

        return numValsMatchingCriteria;
    }
};
