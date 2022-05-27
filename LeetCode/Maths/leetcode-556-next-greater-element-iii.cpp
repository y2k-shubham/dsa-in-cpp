// LeetCode-556: https://leetcode.com/problems/next-greater-element-iii/
// LeetCode Dec-2020: https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3578/

// almost same problems
// GFG: https://www.geeksforgeeks.org/find-next-greater-number-set-digits/
// InterviewBit: https://www.interviewbit.com/problems/next-permutation/

/**
 * @file leetcode-556-next-greater-element-iii.cpp
 * @author Shubham Gupta (y2k-shubham)
 * @brief The problematic bit in LeetCode is this line
 * "Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1."
 * @date 2020-12-26
 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void showVec(vector<int> vec, string msg) {
    printf("\n%s, vec is:-\n", msg.c_str());

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

class Solution {
   private:
    vector<int> convertIntToRevDigVec(int n) {
        vector<int> revDigVec;

        while (n > 0) {
            int dig = n % 10;
            revDigVec.push_back(dig);

            n = n / 10;
        }

        return revDigVec;
    }

    int convertRevDigVecToInt(vector<int> revDigVec) {
        long long int n = -1;

        // cout << endl;
        int numDigs = revDigVec.size();
        for (int i = numDigs - 1; i >= 0; i--) {
            if (n < 0) {
                n = 0;
            }
            int newVal = (n * 10) + revDigVec[i];
            if (newVal >= n) {
                n = newVal;
            } else {
                // INT_MAX overflow case -> LeetCode rejects without this check
                return -1;
            }

            // printf("after processing vec[%d] = %d, n = %d\n", i, revDigVec[i], n);
        }

        return (int) n;
    }

    pair<bool, vector<int>> findNextGreaterNum(vector<int> revDigVecOrg) {
        vector<int> revDigVecNew = revDigVecOrg;
        bool found = false;

        int numDigs = revDigVecNew.size();
        for (int i = 0; i < (numDigs - 1); i++) {
            if (revDigVecNew[i + 1] < revDigVecNew[i]) {
                // important: go back and find the smallest dig bigger than [i + 1]th can replace it
                int smallestBiggerDig = revDigVecNew[i];
                int smallestBiggerDigInd = i;
                for (int j = i - 1; j >= 0; j--) {
                  if (revDigVecNew[i + 1] < revDigVecNew[j] && revDigVecNew[j] < smallestBiggerDig) {
                    smallestBiggerDig = revDigVecNew[j];
                    smallestBiggerDigInd = j;
                  }
                }

                // printf("revDigVecNew[%d + 1] = %d & smallesBiggerDig = vec[%d] = %d\n", i, revDigVecNew[i + 1], smallestBiggerDigInd, smallestBiggerDig);

                int temp = revDigVecNew[i + 1];
                revDigVecNew[i + 1] = revDigVecNew[smallestBiggerDigInd];
                revDigVecNew[smallestBiggerDigInd] = temp;

                // important: now sort lower order digits from here in ascending order
                // printf("\nsorting vec from begin to begin + vec[i=%d] = %d\n", i, revDigVecNew[i]);
                // showVec(revDigVecNew, "before sorting");
                sort(revDigVecNew.begin(), revDigVecNew.begin() + (i + 1), std::greater<int>());
                // showVec(revDigVecNew, "after  sorting");

                found = true;
                break;
            }
        }

        return {found, revDigVecNew};
    }

   public:
    friend class TestSolution;

    int nextGreaterElement(int n) {
        vector<int> revDigVec = convertIntToRevDigVec(n);
        pair<bool, vector<int>> nextGreaterNumRes = findNextGreaterNum(revDigVec);

        if (nextGreaterNumRes.first) {
            return convertRevDigVecToInt(nextGreaterNumRes.second);
        } else {
            return -1;
        }
    }

};

class TestSolution {
   public:
    void testConvertIntToRevDig() {
        Solution soln = Solution();
        int n;
        vector<int> vecOutExpected;
        vector<int> vecOutComputed;

        n = 0;
        vecOutExpected = {};
        vecOutComputed = soln.convertIntToRevDigVec(n);
        assert(vecOutExpected == vecOutComputed);

        n = 5;
        vecOutExpected = {5};
        vecOutComputed = soln.convertIntToRevDigVec(n);
        assert(vecOutExpected == vecOutComputed);

        n = 50;
        vecOutExpected = {0, 5};
        vecOutComputed = soln.convertIntToRevDigVec(n);
        assert(vecOutExpected == vecOutComputed);

        n = 199;
        vecOutExpected = {9, 9, 1};
        vecOutComputed = soln.convertIntToRevDigVec(n);
        assert(vecOutExpected == vecOutComputed);
    }

    void testConvertRevDigVecToInt() {
        Solution soln = Solution();
        vector<int> revDigVec;
        int nOutExpected;
        int nOutComputed;

        revDigVec = {};
        nOutExpected = -1;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {0};
        nOutExpected = 0;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {0, 0};
        nOutExpected = 0;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {0, 0, 5};
        nOutExpected = 500;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {9};
        nOutExpected = 9;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {6, 7};
        nOutExpected = 76;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {8, 1, 7};
        nOutExpected = 718;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        assert(nOutExpected == nOutComputed);

        revDigVec = {9, 9, 9, 9, 9, 9, 9, 9, 1, 9};
        nOutExpected = -1;
        nOutComputed = soln.convertRevDigVecToInt(revDigVec);
        // cout << nOutComputed << endl;
        assert(nOutExpected == nOutComputed);
    }

    void testFindNextGreaterNum() {
        Solution soln = Solution();

        vector<int> revDifVecIn;
        pair<bool, vector<int>> resOutExpected;
        pair<bool, vector<int>> resOutComputed;

        revDifVecIn = {};
        resOutExpected = {false, {}};
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        assert(resOutExpected == resOutComputed);

        revDifVecIn = {0};
        resOutExpected = {false, {0}};
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        assert(resOutExpected == resOutComputed);

        revDifVecIn = {5};
        resOutExpected = {false, {5}};
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        assert(resOutExpected == resOutComputed);

        revDifVecIn = {0, 5};
        resOutExpected = {false, {0, 5}};
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        assert(resOutExpected == resOutComputed);

        revDifVecIn = {8, 1, 3};
        resOutExpected = {true, {1, 8, 3}};
        // showVec(resOutExpected.second, "tc-5 required output");
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        // showVec(resOutComputed.second, "tc-5");
        // printf("bool = %s\n", (resOutComputed.first ? "true" : "false"));
        assert(resOutExpected == resOutComputed);

        revDifVecIn = {1, 4, 2, 0, 3, 2};
        resOutExpected = {true, {2, 1, 4, 0, 3, 2}};
        // showVec(resOutExpected.second, "tc-6 required output");
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        // showVec(resOutComputed.second, "tc-6");
        // printf("bool = %s\n", (resOutComputed.first ? "true" : "false"));
        assert(resOutExpected == resOutComputed);

        // 12443322
        revDifVecIn = {2, 2, 3, 3, 4, 4, 2, 1};
        // 13222344
        resOutExpected = {true, {4, 4, 3, 2, 2, 2, 3, 1}};
        // showVec(resOutExpected.second, "tc-7 required output");
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        // showVec(resOutComputed.second, "tc-7");
        // printf("bool = %s\n", (resOutComputed.first ? "true" : "false"));
        assert(resOutExpected == resOutComputed);

        // 1999999999
        revDifVecIn = {9, 9, 9, 9, 9, 9, 9, 9, 9, 1};
        // 9199999999
        resOutExpected = {true, {9, 9, 9, 9, 9, 9, 9, 9, 1, 9}};
        // showVec(resOutExpected.second, "tc-8 required output");
        resOutComputed = soln.findNextGreaterNum(revDifVecIn);
        // showVec(resOutComputed.second, "tc-8");
        // printf("bool = %s\n", (resOutComputed.first ? "true" : "false"));
        assert(resOutExpected == resOutComputed);
    }

};

int main() {
    TestSolution testSoln = TestSolution();

    testSoln.testConvertIntToRevDig();
    testSoln.testConvertRevDigVecToInt();
    testSoln.testFindNextGreaterNum();

    return 0;
}
