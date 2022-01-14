// LeetCode-377: https://leetcode.com/problems/combination-sum-iv/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showMemoMat(vector<int>& nums, int target, vector<vector<int> >& memoMat) {
        int len = nums.size();

        printf("\t\t");
        for (int j = 0; j <= target; j++) {
            if (j == 0) {
                printf("\t");
            } else {
                printf("%d\t", nums[j - 1]);
            }
        }
        cout << endl;

        printf("\t\t");
        for (int j = 0; j <= target; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (int i = 0; i <= len; i++) {
            if (i == 0) {
                printf("-\t[%d]\t", i);
            } else {
                printf("%d\t[%d]\t", nums[i - 1], i);
            }

            for (int j = 0; j <= target; j++) {
                printf("%d\t", memoMat[i][j]);
            }

            cout << endl;
        }
    }

    vector<vector<int> > buildMemoMat(vector<int>& nums, int target) {
        int len = nums.size();

        vector<vector<int> > memoMat(len + 1);
        for (int i = 0; i <= len; i++) {
            vector<int> memoMatRow(target + 1);
            memoMatRow[0] = 1;
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    void fillMemoMat(vector<int>& nums, int target, vector<vector<int> >& memoMat) {
        int len = nums.size();

        for (int i = 1; i <= len; i++) {
            int crrNum = nums[i - 1];

            int j = 1;
            while (j < crrNum) {
                memoMat[i][j] = memoMat[i - 1][j];
                j++;
            }
            while (j <= target) {
                memoMat[i][j] = memoMat[i - 1][j] + memoMat[i][j - crrNum];
                j++;
            }

            if (debug) {
                printf("\n------------\n");
                printf("after nums[i=%d] = %d\n", i, crrNum);
                showMemoMat(nums, target, memoMat);
            }
        }
    }

   public:
    friend class SolutionTest;

    int combinationSum4(vector<int>& nums, int target) {
        int len = nums.size();

        sort(nums.begin(), nums.end());
        if (nums[0] > target) {
            return 0;
        }

        vector<vector<int> > memoMat = buildMemoMat(nums, target);
        fillMemoMat(nums, target, memoMat);

        return memoMat[len][target];
    }
};

class SolutionTest {
   public:
    void testCombinationSum4() {
        Solution soln = Solution();
        vector<int> inNums;
        int inTarget;
        int outExpected, outComputed;

        soln.debug = true;
        inNums = {1, 2, 3};
        inTarget = 4;
        outExpected = 7;
        outComputed = soln.combinationSum4(inNums, inTarget);
        assert(outExpected == outComputed);
        soln.debug = false;

        inNums = {9};
        inTarget = 3;
        outExpected = 0;
        outComputed = soln.combinationSum4(inNums, inTarget);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testCombinationSum4();
    return 0;
}
