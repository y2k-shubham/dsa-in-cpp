// LeetCode-368: https://leetcode.com/problems/largest-divisible-subset/

#include <vector>
#include <utility>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    bool debug = false;

    void showVec(vector<pair<int, int> >& vec) {
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i].first);
        }
        cout << endl;

        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i].second);
        }
        cout << endl;
    }

    void showVec(vector<int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    vector<pair<int, int>> buildChainVec(vector<int>& nums) {
        int len = nums.size();

        vector<pair<int, int> > chainVec(len, {1, -1});
        sort(nums.begin(), nums.end());

        for (int i = 1; i < len; i++) {
            int crrMult = nums[i];
            pair<int, int> crrChain = {1, -1};

            for (int j = 0; j < i; j++) {
                if ((crrMult % nums[j]) == 0) {
                    int newChainLen = chainVec[j].first + 1;
                    if (newChainLen > crrChain.first) {
                        crrChain = {newChainLen, j};
                    }
                }
            }

            chainVec[i] = crrChain;
        }

        return chainVec;
    }

    pair<int, int> getLongestChainItem(vector<pair<int, int> >& chainVec) {
        pair<int, int> longestChain = {1, 0};

        for (int i = 0; i < chainVec.size(); i++) {
            if (chainVec[i].first > longestChain.first) {
                longestChain = {chainVec[i].first, i};
            }
        }

        return longestChain;
    }

    vector<int> buildLongestChainVec(vector<int>& nums, vector<pair<int, int> >& chainVec) {
        pair<int, int> longestChainItem = getLongestChainItem(chainVec);
        if (debug) {
            printf("longestChainItem: %d, %d\n", longestChainItem.first, longestChainItem.second);
        }

        vector<int> longestChainVec(longestChainItem.first, -1);
        int crrVecIdx = longestChainItem.first - 1;
        int crrEleIdx = longestChainItem.second;

        while (crrEleIdx != -1) {
            longestChainVec[crrVecIdx--] = nums[crrEleIdx];
            crrEleIdx = chainVec[crrEleIdx].second;
        }

        return longestChainVec;
    }

public:
    friend class SolutionTest;

    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return nums;
        }

        vector<pair<int, int> > chainVec = buildChainVec(nums);
        if (debug) {
            showVec(chainVec);
        }

        vector<int> longestChainVec = buildLongestChainVec(nums, chainVec);
        if (debug) {
            showVec(longestChainVec);
        }

        return longestChainVec;
    }
};

class SolutionTest {
public:
    void testLargestDivisibleSubset() {
        Solution soln = Solution();
        vector<int> numsIn;
        vector<int> subsetOutExpected;
        vector<int> subsetOutComputed;

//        soln.debug = true;
        numsIn = {1, 2, 3};
        subsetOutExpected = {1, 2};
        subsetOutComputed = soln.largestDivisibleSubset(numsIn);
        assert(subsetOutExpected == subsetOutComputed);
//        soln.debug = false;

//        soln.debug = true;
        numsIn = {1, 2, 4, 8};
        subsetOutExpected = {1, 2, 4, 8};
        subsetOutComputed = soln.largestDivisibleSubset(numsIn);
        assert(subsetOutExpected == subsetOutComputed);
//        soln.debug = false;

        numsIn = {1, 2, 3, 4, 8, 9, 18, 27, 36};
        subsetOutExpected = {1, 3, 9, 18, 36};
        subsetOutComputed = soln.largestDivisibleSubset(numsIn);
        assert(subsetOutExpected == subsetOutComputed);

        numsIn = {1, 2, 3, 4, 8, 9, 18, 27, 32, 36};
        subsetOutExpected = {1, 2, 4, 8, 32};
        subsetOutComputed = soln.largestDivisibleSubset(numsIn);
        assert(subsetOutExpected == subsetOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testLargestDivisibleSubset();

    return 0;
}
