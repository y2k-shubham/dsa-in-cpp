// LeetCode-974: https://leetcode.com/problems/subarray-sums-divisible-by-k/
// incomplete (giving wrong answers for 'some' cases when mod becomes negative)

/**

failing test-case
[2,-2,2,-4]
6

passing test-cases
[-1,2,9]
2
[4,5,0,-2,-3,1]
5
[-4,-5,0,2,3,-1]
5
[-4,-5,0,-2,-3,-1]
5
[4,5,0,2,3,1]
5
[4,5,0,-2,-3,1]
4
[-4,-5,0,2,3,-1]
4
[-4,-5,0,-2,-3,-1]
4
[4,5,0,2,3,1]
4
[4,5,0,-2,-3,1]
3
[-4,-5,0,2,3,-1]
3
[-4,-5,0,-2,-3,-1]
3
[4,5,0,2,3,1]
3
[4,5,0,-2,-3,1]
2
[-4,-5,0,2,3,-1]
2
[-4,-5,0,-2,-3,-1]
2
[4,5,0,2,3,1]
2
[4,5,0,-2,-3,1]
6
[-4,-5,0,2,3,-1]
6
[-4,-5,0,-2,-3,-1]
6
[4,5,0,2,3,1]
6
[4,5,0,-2,-3,1]
7
[-4,-5,0,2,3,-1]
7
[-4,-5,0,-2,-3,-1]
7
[4,5,0,2,3,1]
7
[4,5,0,-2,-3,1]
8
[-4,-5,0,2,3,-1]
8
[-4,-5,0,-2,-3,-1]
8
[4,5,0,2,3,1]
8
[5]
9

 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    bool debug = true;

    void showMap(unordered_map<int, int> &mMap, string name) {
        printf("%s map is:-\n", name.c_str());
        for (
                unordered_map<int, int>::iterator it = mMap.begin();
                it != mMap.end();
                it++
                ) {
            printf("%d (%d)\n", it->first, it->second);
        }
    }

    unordered_map<int, int> buildModFreqMap(vector<int> &vec, int k) {
        unordered_map<int, int> modFreqMap;
        modFreqMap[0] = 1; // before picking any element (at idx=-1), sum is 0 -> modulo is 0

        int sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            sum += vec[i];
            int modSum = abs(sum) % k;

            modFreqMap[modSum]++;
        }

        return modFreqMap;
    }

    int hcf(int dividend, int divisor) {
        int mod = dividend % divisor;

        if (mod == 0) {
            return divisor;
        } else {
            return hcf(divisor, mod);
        }
    }

    int nCr(int n, int r) {
        int nMinusR = n - r;
        r = min(r, nMinusR);

        if (r == 0) {
            return 1;
        }

        int nr = 1;
        int dr = 1;
        while (r >= 1) {
            nr *= n;
            dr *= r;

            int gcd = hcf(nr, dr);
            nr /= gcd;
            dr /= gcd;

            n--;
            r--;
        }

        return nr / dr;
    }

    int calcNumSubarrs(unordered_map<int, int> &modFreqMap, int k) {
        int numSubarrs = 0;
        for (
                unordered_map<int, int>::iterator it = modFreqMap.begin();
                it != modFreqMap.end();
                it++
                ) {
            if (it->second > 1) {
                int numCombs = nCr(it->second, 2);
                if (debug) {
                    printf("nCr(%d, %d) = %d\n", it->second, 2, numCombs);
                }
                numSubarrs += numCombs;
            }
        }

        return numSubarrs;
    }

public:
    int subarraysDivByK(vector<int> &nums, int k) {
        unordered_map<int, int> modFreqMap = buildModFreqMap(nums, k);
        if (debug) {
            showMap(modFreqMap, "modFreqMap");
        }
        return calcNumSubarrs(modFreqMap, k);
    }
};

