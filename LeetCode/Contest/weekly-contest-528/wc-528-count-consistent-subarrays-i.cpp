// LeetCode WeeklyContest-528: https://leetcode.com/contest/weekly-contest-528/problems/count-consistent-subarrays-i/

#include <cassert>
#include <vector>
#include <utility>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    void showVec(vector<int>& vec, string name) {
        printf("\n%s vec is:-\n", name.c_str());
        int len = vec.size();

        printf("Ind\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    void showMat(vector <vector<pair<int, int>>> mat, string name) {
        printf("\n%s vec is:-\n", name.c_str());
        int len = mat.size();

        printf("Ind\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < len; j++) {
                int minVal = mat[i][j].first;
                string minValStr = (minVal == INT_MAX) ? "-" : to_string(minVal);

                int ANDVal = mat[i][j].second;
                string ANDValStr = (ANDVal == INT_MAX) ? "-" : to_string(ANDVal);

                printf("%s, %s\t", minValStr.c_str(), ANDValStr.c_str());
            }
            cout << endl;
        }
    }

    vector <vector<pair<int, int>>> createMat(vector <int>& nums) {
        int len = nums.size();
        vector <vector<pair <int, int> >> mat(len);
        for (int i = 0; i < len; i++) {
            vector <pair <int, int> > row(len, {INT_MAX, INT_MAX});

            int crrVal = nums[i];
            row[i] = {crrVal, crrVal}; // {min, AND}

            mat[i] = row;
        }

        return mat;
    }

    int fillMatAndCountConsistentSubArrsOfLen(
        vector <int>& nums,
        vector <vector<pair<int, int>>>& mat,
        int subArrLen) {
        int len = nums.size();

        int iLo = 0;
        int jLo = subArrLen - 1;
        int jHi = len - 1;
        // diagonal traversal
        int numConsistentSubArrs = 0;
        for (int i = iLo, j = jLo; j <= jHi; i++, j++) {
            int newVal = nums[j];

            int newMin = min(mat[i][j - 1].first, newVal);
            int newAND = mat[i][j - 1].second & newVal;

            if (newMin == newAND) {
                numConsistentSubArrs++;
            }

            mat[i][j] = {newMin, newAND};
        }

        return numConsistentSubArrs;
    }

public:
    friend class SolutionTest;

    int countConsistent(vector<int>& nums) {
        vector <vector<pair<int, int>>> mat = createMat(nums);

        int len = nums.size();
        int numConsistentSubArrsTotal = len;
        for (int subArrLen = 2; subArrLen <= len; subArrLen++) {
            int numConsistentSubArrsCrrLen = fillMatAndCountConsistentSubArrsOfLen(nums, mat, subArrLen);

            // printf("\n-----subArrLen=%d---\n", subArrLen);
            // showVec(nums, "nums");
            // printf("for subArrLen=%d, calculated numConsistentSubArrsCrrLen=%d\n", subArrLen, numConsistentSubArrsCrrLen);
            // showMat(mat, "mat");

            numConsistentSubArrsTotal += numConsistentSubArrsCrrLen;
        }

        return numConsistentSubArrsTotal;
    }
};

class SolutionTest {
public:
    void testCountConsistent() {
        Solution soln = Solution();
        vector <int> numsIn;
        int outExpected, outComputed;

        numsIn = {5, 3, 1, 2};
        outExpected = 6;
        outComputed = soln.countConsistent(numsIn);
        // printf("outComputed=%d\n", outComputed);
        assert(outExpected == outComputed);

        numsIn = {1, 1, 1};
        outExpected = 6;
        outComputed = soln.countConsistent(numsIn);
        // printf("outComputed=%d\n", outComputed);
        assert(outExpected == outComputed);

        numsIn = {0};
        outExpected = 1;
        outComputed = soln.countConsistent(numsIn);
        // printf("outComputed=%d\n", outComputed);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCountConsistent();

    return 0;
}
