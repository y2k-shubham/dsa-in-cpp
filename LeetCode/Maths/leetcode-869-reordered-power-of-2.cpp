// LeetCode-869: https://leetcode.com/problems/reordered-power-of-2/
// LC Mar-2021 challenge: https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/590/week-3-march-15th-march-21st/3679/
// GFG (similar not identical): https://www.geeksforgeeks.org/reorder-digits-of-a-given-number-to-make-it-a-power-of-2/

#include <cstdio>
#include <iostream>
#include <map>
#include <set>

using namespace std;

class Solution {
   public:
    bool isPowOf2(int n) {
        if (n == 1) {
            return true;
        } else if ((n % 2) == 0) {
            return isPowOf2(n / 2);
        } else {
            return false;
        }
    }

    int findNumDigs(int n) {
        if (n == 0) {
            return 0;
        } else {
            return 1 + findNumDigs(n / 10);
        }
    }

    set<int> findPowsOf2WithDigs(int d) {
        set<int> powsOf2;

        int p = 1;
        int numDigs = 1;
        do {
            if (numDigs == d) {
                powsOf2.insert(p);
            }

            p = p * 2;
            numDigs = findNumDigs(p);
        } while (numDigs <= d);

        return powsOf2;
    }

    map<int, int> buildDigFreqMap(int n) {
        map<int, int> digFreqMap;

        while (n > 0) {
            int dig = n % 10;
            n = n / 10;

            digFreqMap[dig]++;
        }

        return digFreqMap;
    }

    bool reorderedPowerOf2(int n) {
        if (isPowOf2(n)) {
            return true;
        }

        int numDigs = findNumDigs(n);
        set<int> powsOf2 = findPowsOf2WithDigs(numDigs);

        map<int, int> numDigFreqMap = buildDigFreqMap(n);
        for (set<int>::iterator it = powsOf2.begin(); it != powsOf2.end(); it++) {
            map<int, int> powDigFreqMap = buildDigFreqMap(*it);

            if (numDigFreqMap == powDigFreqMap) {
                return true;
            }
        }

        return false;
    }
};
