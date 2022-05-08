// LeetCode-202: https://leetcode.com/problems/happy-number/
// dumb problem; please overlook

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
private:
    vector<int> digSquares = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

    int calcDigSquaresSum(int n) {
        int sum = 0;

        while (n > 0) {
            int dig = n % 10;
            n /= 10;

            sum += digSquares[dig];
        }

        return sum;
    }

public:
    bool isHappy(int n) {
        unordered_set<int> seenNums;
        seenNums.insert(n);

        while (n > 1) {
            // printf("for n=%d, digSqrsSum=%d\n", n, calcDigSquaresSum(n));
            n = calcDigSquaresSum(n);
            if (seenNums.find(n) != seenNums.end()) {
                return false;
            }

            seenNums.insert(n);
        }

        return true;
    }
};

