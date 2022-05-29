// LeetCode-650: https://leetcode.com/problems/2-keys-keyboard/

#include <vector>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int minSteps(int n) {
        if (n == 1) {
            return 0;
        } else if (n == 2) {
            return 2;
        }

        vector<int> memoVec(n + 1, INT_MAX);
        memoVec[0] = 0;
        memoVec[1] = 0;
        memoVec[2] = 2;

        for (int i = 3; i <= n; i++) {
            int crrVal = i;
            int uLimit = crrVal / 2;

            int crrValMinSteps = INT_MAX;
            for (int fact = 1; fact <= uLimit; fact++) {
                if ((crrVal % fact) != 0) {
                    continue;
                }

                int crrFactSteps = memoVec[fact] + 1 + ((crrVal - fact) / fact);
                crrValMinSteps = min(crrValMinSteps, crrFactSteps);
            }

            memoVec[i] = crrValMinSteps;
        }

        return memoVec[n];
    }
};

class SolutionTest {
public:
    void testMinSteps() {
        Solution solution;
        assert(solution.minSteps(0) == 0);
        assert(solution.minSteps(1) == 0);
        assert(solution.minSteps(2) == 2);
        assert(solution.minSteps(3) == 3);
        assert(solution.minSteps(4) == 4);
        assert(solution.minSteps(5) == 5);
        assert(solution.minSteps(6) == 5);
        assert(solution.minSteps(7) == 7);
        assert(solution.minSteps(10) == 7);
        assert(solution.minSteps(11) == 11);
        assert(solution.minSteps(12) == 7);
        assert(solution.minSteps(13) == 13);
        assert(solution.minSteps(24) == 9);
        assert(solution.minSteps(23) == 23);
        assert(solution.minSteps(28) == 11);
        assert(solution.minSteps(29) == 29);
        assert(solution.minSteps(36) == 10);
        assert(solution.minSteps(37) == 37);
        assert(solution.minSteps(999) == 46);
        assert(solution.minSteps(1000) == 21);
    }
};

int main() {
    SolutionTest solutionTest;
    solutionTest.testMinSteps();
    return 0;
}
