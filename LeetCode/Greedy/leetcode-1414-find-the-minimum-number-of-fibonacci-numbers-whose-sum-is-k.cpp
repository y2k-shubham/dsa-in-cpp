// LeetCode-1414: https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/
// solved by looking at LC hints

#include <vector>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    vector<int> buildFibsVec(int k) {
        vector<int> fibNums = {1, 1};

        int idx = 2;
        while (true) {
            int crrEle = fibNums[idx - 1] + fibNums[idx - 2];
            if (crrEle > k) {
                break;
            }

            fibNums.push_back(crrEle);
            idx++;
        }

        return fibNums;
    }

    void showVec(vector<int> vec) {
        printf("\nElements of array are:-\n");

        cout << "Ind:\t";
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        cout << "Val:\t";
        for (vector<int>::iterator i = vec.begin(); i != vec.end(); i++) {
            printf("%d\t", (*i));
        }
        cout << endl;
    }

public:
    friend class SolutionTest;

    int findMinFibonacciNumbers(int k) {
        vector<int> fibsVec = buildFibsVec(k);
        if (debug) {
            showVec(fibsVec);
        }

        int ctr = 0;
        auto endIt = fibsVec.end();
        while (k > 0) {
            ++ctr;

            auto it = lower_bound(fibsVec.begin(), endIt, k);
            if ((it == fibsVec.end()) || (*it > k)) {
                it--;
            }
            if (debug) {
                printf("searching %d b/w %d and %s, found %d\n", k, *(fibsVec.begin()),
                       (endIt == fibsVec.end() ? "end" : to_string(*(endIt)).c_str()), *it);
            }

            endIt = it;
            k -= *it;
        }

        return ctr;
    }
};

class SolutionTest {
public:
    void testBuildFibsVec() {
        Solution soln = Solution();
        int kIn;
        vector<int> fibsVecOutExpected;
        vector<int> fibsVecOutComputed;

        kIn = 1;
        fibsVecOutExpected = {1, 1};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 2;
        fibsVecOutExpected = {1, 1, 2};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 3;
        fibsVecOutExpected = {1, 1, 2, 3};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 4;
        fibsVecOutExpected = {1, 1, 2, 3};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 5;
        fibsVecOutExpected = {1, 1, 2, 3, 5};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 6;
        fibsVecOutExpected = {1, 1, 2, 3, 5};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 7;
        fibsVecOutExpected = {1, 1, 2, 3, 5};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);

        kIn = 8;
        fibsVecOutExpected = {1, 1, 2, 3, 5, 8};
        fibsVecOutComputed = soln.buildFibsVec(kIn);
//        soln.showVec(fibsVecOutComputed);
        assert(fibsVecOutComputed == fibsVecOutExpected);
    }

    void testFindMinFibonacciNumbers() {
        Solution s = Solution();

        int k = 1;
        int expected = 1;
        int actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);

//        s.debug = true;
        k = 2;
        expected = 1;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);
//        s.debug = true;

        k = 3;
        expected = 1;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);

//        s.debug = true;
        k = 4;
        expected = 2;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);
//        s.debug = false;

        k = 5;
        expected = 1;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);

        k = 6;
        expected = 2;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);

        k = 7;
        expected = 2;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);

        k = 10;
        expected = 2;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);

        k = 19;
        expected = 3;
        actual = s.findMinFibonacciNumbers(k);
        assert(actual == expected);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildFibsVec();
    solnTest.testFindMinFibonacciNumbers();

    return 0;
}
