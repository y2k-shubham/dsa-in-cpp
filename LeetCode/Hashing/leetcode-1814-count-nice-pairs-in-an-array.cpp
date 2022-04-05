// LeetCode-1814: https://leetcode.com/problems/count-nice-pairs-in-an-array/

#include <vector>
#include <unordered_map>

using namespace std;

#define MOD 1000000007

class Solution {
private:
    int revNum(int n) {
        int revN = 0;
        while (n > 0) {
            revN = (revN * 10) + (n % 10);
            n /= 10;
        }

        return revN;
    }

public:
    int countNicePairs(vector<int>& nums) {
        unordered_map<int, int> revDiffFreqMap;
        int numPalins = 0;

        long long numPairs = 0;
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];
            int revN = revNum(n);

            // this palindrome check is not required as for palindromes, diff will be 0
            // (so they will already be counted in diff check below)
//            bool isPalin = n == revN;
//            if (isPalin) {
//                numPairs += numPalins;
//                ++numPalins;
//            }

            int diff = n - revN;
            if (revDiffFreqMap.find(diff) != revDiffFreqMap.end()) {
                numPairs += revDiffFreqMap[diff];
            }
            revDiffFreqMap[diff]++;
        }

        return (int) (numPairs % MOD);
    }
};
