// LeetCode-1362: https://leetcode.com/problems/closest-divisors/
// https://poitevinpm.medium.com/leetcode-1362-closest-divisors-50ea4ab37619

// harder than it looks

#include <vector>
#include <utility>
#include <cmath>

using namespace std;

class Solution {
private:
    int findDivisorClosestToSqrt(int n) {
        int nSqrt = (int) ceil(sqrt(n));
        bool nIsOdd = (n % 2) == 1;

        int delta = 1;
        if (nIsOdd) {
            delta = 2;
            nSqrt = ((nSqrt % 2) == 0) ? (nSqrt - 1) : nSqrt;
        }

        int closestDiv = 1;
        for (int div1 = nSqrt; div1 >= 2; div1 -= delta) {
            if ((n % div1) == 0) {
                closestDiv = div1;
                break;
            }
        }

        return closestDiv;
    }

    pair<int, int> findDivisorPairsClosestToSqrt(int n) {
        int div1 = findDivisorClosestToSqrt(n);
        int div2 = n / div1;

        return {min(div1, div2), max(div1, div2)};
    }

    vector<int> findCloserPair(pair<int, int> p1, pair<int, int> p2) {
        if (abs(p1.first - p1.second) <= abs(p2.first - p2.second)) {
            return {p1.first, p1.second};
        } else {
            return {p2.first, p2.second};
        }
    }

public:
    vector<int> closestDivisors(int num) {
        pair<int, int> divsPair1 = findDivisorPairsClosestToSqrt(num + 1);
        pair<int, int> divsPair2 = findDivisorPairsClosestToSqrt(num + 2);

        return findCloserPair(divsPair1, divsPair2);
    }
};
