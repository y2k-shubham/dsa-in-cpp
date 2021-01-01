// LeetCode-1664: https://leetcode.com/problems/ways-to-make-a-fair-array/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    void showVec(vector<int> vec, string str) {
        printf("%s vector is:-\n", str.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    pair<int, vector<int> > calcEvnIndCumSum(vector<int> vec) {
        int len = vec.size();

        vector<int> evnIndCumSum(len, 0);

        int evnSum = 0;
        for (int i = 0; i < len; i++) {
            if ((i % 2) == 0) {
                evnSum = evnSum + vec[i];
            }
            evnIndCumSum[i] = evnSum;
        }

        return {evnSum, evnIndCumSum};
    }

    pair<int, vector<int> > calcOddIndCumSum(vector<int> vec) {
        int len = vec.size();

        vector<int> oddIndCumSum(len, 0);

        int oddSum = 0;
        for (int i = 0; i < len; i++) {
            if ((i % 2) == 1) {
                oddSum = oddSum + vec[i];
            }
            oddIndCumSum[i] = oddSum;
        }

        return {oddSum, oddIndCumSum};
    }

    int findNumWays(vector<int> vec, bool debug) {
        int len = vec.size();

        pair<int, vector<int> > evnRes = calcEvnIndCumSum(vec);
        int totalEvnSum = evnRes.first;
        vector<int> evnIndCumSum = evnRes.second;

        pair<int, vector<int> > oddRes = calcOddIndCumSum(vec);
        int totalOddSum = oddRes.first;
        vector<int> oddIndCumSum = oddRes.second;

        if (debug) {
            showVec(vec, "vec");
            showVec(evnIndCumSum, "evnIndCumSum");
            showVec(oddIndCumSum, "oddIndCumSum");
        }

        int numWays = 0;
        for (int i = 0; i < len; i++) {
            int evnSum = 0;
            int oddSum = 0;

            if ((i % 2) == 0) {
                if (i == 0) {
                    evnSum = totalOddSum;
                    oddSum = totalEvnSum - evnIndCumSum[0];
                } else {
                    evnSum = evnIndCumSum[i - 2] + (totalOddSum - oddIndCumSum[i - 1]);
                    oddSum = oddIndCumSum[i - 1] + (totalEvnSum - evnIndCumSum[i]);
                }
            } else {
                if (i == 1) {
                    evnSum = evnIndCumSum[0] + (totalOddSum - oddIndCumSum[1]);
                    oddSum = totalEvnSum - evnIndCumSum[0];
                } else {
                    evnSum = evnIndCumSum[i - 1] + (totalOddSum - oddIndCumSum[i]);
                    oddSum = oddIndCumSum[i - 2] + (totalEvnSum - evnIndCumSum[i - 1]);
                }
            }

            if (debug) {
                printf("\nat vec[i=%d] = %d\n", i, vec[i]);
                printf("evnSum = %d, oddSum = %d\n", evnSum, oddSum);
            }

            if (evnSum == oddSum) {
                numWays++;
            }
        }

        return numWays;
    }

   public:
    void testFindNumWays() {
        vector<int> vec;
        int outExpected;
        int outComputed;

        vec = {2, 1, 6, 4};
        outExpected = 1;
        outComputed = findNumWays(vec, false);
        assert(outExpected == outComputed);

        vec = {1, 1, 1};
        outExpected = 3;
        outComputed = findNumWays(vec, false);
        assert(outExpected == outComputed);

        vec = {1, 2, 3};
        outExpected = 0;
        outComputed = findNumWays(vec, false);
        assert(outExpected == outComputed);
    }

    int waysToMakeFair(vector<int>& nums) {
        int len = nums.size();
        switch (len) {
            case 1:
                return 1;

            case 2:
                return 0;

            default:
                return findNumWays(nums, false);
        }
    }

    void testWaysToMakeFair() {
        vector<int> vec;
        int outExpected;
        int outComputed;

        vec = {};
        outExpected = 0;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);

        vec = {4};
        outExpected = 1;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);

        vec = {9, 8};
        outExpected = 0;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);

        vec = {6, 4, 6};
        outExpected = 1;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);

        vec = {2, 1, 6, 4};
        outExpected = 1;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);

        vec = {1, 1, 1};
        outExpected = 3;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);

        vec = {1, 2, 3};
        outExpected = 0;
        outComputed = waysToMakeFair(vec);
        assert(outExpected == outComputed);
    }
};

int main() {
    Solution soln = Solution();
    soln.testFindNumWays();
    soln.testWaysToMakeFair();

    return 0;
}
