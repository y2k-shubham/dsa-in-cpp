// LeetCode-204: https://leetcode.com/problems/count-primes/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3738/

#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    void deleteMultiples(int upperBound, unordered_set<int>& deletedNums, int num) {
        int multiple = num * 2;

        while (multiple <= upperBound) {
            deletedNums.insert(multiple);

            multiple += num;
        }
    }

    // unordered_set : times-out
    int runSieveSet(int upperBound) {
        int num = 2;
        int ctr = 0;
        unordered_set<int> deletedNums;

        while (num <= upperBound) {
            if (deletedNums.find(num) == deletedNums.end()) {
                // 'num' is a prime number

                // increment counter of no of primes
                ctr++;

                // delete multiples of num
                deleteMultiples(upperBound, deletedNums, num);
            }

            num++;
        }

        return ctr;
    }

    // LC-submission - speed 49 %tile, memory 59 %tile
    int runSieveVector(int upperBound) {
        vector<bool> vec(upperBound + 1, true);

        int ctr = 0;
        for (int i = 2; i <= upperBound; i++) {
            if (vec[i]) {
                // i is a prime
                ctr++;

                // remove all multiples of i
                for (int j = i * 2; j <= upperBound; j += i) {
                    vec[j] = false;
                }
            }
        }

        return ctr;
    }

   public:
    int countPrimes(int n) {
        if (n <= 2) {
            return 0;
        }

        return runSieveVector(n - 1);
    }
};
