// LeetCode-259: https://leetcode.com/problems/3sum-smaller/
// Premium
// Companies: [Google][Paypal][Meta][Oracle]

#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#define MIN_LEN 3

class Solution {
private:
    bool hasNoSuchTriplets(vector<int>& sortedVec, int target) {
        int smallestTripletSum = sortedVec[0] + sortedVec[1] + sortedVec[2];
        return (smallestTripletSum >= target);
    }

    bool hasAllSuchTriplets(vector <int>& sortedVec, int target) {
        int len = sortedVec.size();
        int biggestTripletSum = sortedVec[len - 3] + sortedVec[len - 2] + sortedVec[len - 1];
        return (biggestTripletSum < target);
    }

    long long nCr(int n, int r) {
        int diff = n - r;
        if (diff < r) {
            return nCr(n, diff);
        }

        long long prod = 1;
        int i = 1;
        while (i <= r) {
            prod *= n;
            prod /= i;

            n--;
            i++;
        }

        return prod;
    }

public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int len = nums.size();
        if (len < MIN_LEN) {
            return 0;
        }

        sort(nums.begin(), nums.end());

        if (hasNoSuchTriplets(nums, target)) {
            return 0;
        }
        if (hasAllSuchTriplets(nums, target)) {
            return nCr(len, 3);
        }

        int numTripletsTotal = 0;
        for (auto iIt = nums.begin(); iIt + 2 < nums.end(); iIt++) {
            int iVal = *iIt;
            for (auto jIt = iIt + 1; jIt + 1 < nums.end(); jIt++) {
                int jVal = *jIt;

                auto kLoIt = jIt + 1;
                int kLoVal = *kLoIt;

                int kHiVal = target - (iVal + jVal);
                if (kLoVal >= kHiVal) {
                    // since even the smallest kVal doesn't work, no further jVals would work either
                    // - however trying with next iVal might still work, so we can't do an early return here
                    // - above pitfall (to just break instead of return) was pointed out by KiroCLI
                    break;
                }

                auto kHiIt = lower_bound(jIt + 1, nums.end(), kHiVal);
                int numTripletsCrr = distance(kLoIt, kHiIt);

                numTripletsTotal += numTripletsCrr;
            }
        }

        return numTripletsTotal;
    }
};