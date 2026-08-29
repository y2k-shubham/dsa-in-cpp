// LeetCode-2177: https://leetcode.com/problems/find-three-consecutive-integers-that-sum-to-a-given-number/
// simple arithmetic progression sum
// Dumb

#include <vector>

using namespace std;

class Solution {
public:
    vector<long long> sumOfThree(long long num) {
        long long numMinus3 = num - 3;

        bool isDivisibleBy3 = (numMinus3 % 3) == 0;
        if (!isDivisibleBy3) {
            return {};
        }

        long long n = numMinus3 / 3;
        return {n, n+1, n+2};
    }
};
