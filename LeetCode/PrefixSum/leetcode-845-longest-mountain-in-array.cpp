// LeetCode-845: https://leetcode.com/problems/longest-mountain-in-array/

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
public:
    friend class SolutionTest;

    int longestMountain(vector<int>& arr) {
        int len = arr.size();
        if (len < 3) {
            return 0;
        }

        vector<int> leftClimbStepsVec = buildLeftClimbStepsVec(arr);
        vector<int> rightClimbStepsVec = buildRightClimbStepsVec(arr);

        int maxMountainLen = 0;
        for (int i = 1; i < len - 1; i++) {
            if ((1 < leftClimbStepsVec[i]) && (rightClimbStepsVec[i] > 1)) {
                int mountainLen = leftClimbStepsVec[i] + rightClimbStepsVec[i] - 1;
                maxMountainLen = max(maxMountainLen, mountainLen);
            }
        }

        return maxMountainLen;
    }

private:
    vector<int> buildLeftClimbStepsVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> leftClimbStepsVec(len, 1);
        leftClimbStepsVec[0] = 1;

        for (int i = 1; i < len; i++) {
            if (vec[i - 1] < vec[i]) {
                leftClimbStepsVec[i] = leftClimbStepsVec[i - 1] + 1;
            }
        }

        return leftClimbStepsVec;
    }

    vector<int> buildRightClimbStepsVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> rightClimbStepsVec(len, 1);
        rightClimbStepsVec[len - 1] = 1;

        for (int i = len - 2; i >= 0; i--) {
            if (vec[i] > vec[i + 1]) {
                rightClimbStepsVec[i] = rightClimbStepsVec[i + 1] + 1;
            }
        }

        return rightClimbStepsVec;
    }
};

class SolutionTest {
public:
    void testLongestMountain() {
        Solution solution;
        vector<int> vec;
        int expectedLen;
        int actualLen;

        vec = {2, 1, 4, 7, 3, 2, 5};
        expectedLen = 5;
        actualLen = solution.longestMountain(vec);
        assert(actualLen == expectedLen);

        vec = {2, 2, 2};
        expectedLen = 0;
        actualLen = solution.longestMountain(vec);
        assert(actualLen == expectedLen);

        vec = {2, 1, 4, 7, 3, 2, 5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        expectedLen = 5;
        actualLen = solution.longestMountain(vec);
        assert(actualLen == expectedLen);

        printf("testLongestMountain passed.\n");
    }

    void testBuildLeftClimbStepsVec() {
        Solution solution;
        vector<int> vec;
        vector<int> expectedLeftClimbStepsVec;
        vector<int> actualLeftClimbStepsVec;

        vec = {2, 1, 4, 7, 3, 2, 5};
        expectedLeftClimbStepsVec = {1, 1, 2, 3, 1, 1, 2};
        actualLeftClimbStepsVec = solution.buildLeftClimbStepsVec(vec);
        assert(actualLeftClimbStepsVec == expectedLeftClimbStepsVec);

        vec = {2, 2, 2};
        expectedLeftClimbStepsVec = {1, 1, 1};
        actualLeftClimbStepsVec = solution.buildLeftClimbStepsVec(vec);
        assert(actualLeftClimbStepsVec == expectedLeftClimbStepsVec);

        printf("testBuildLeftClimbStepsVec passed.\n");
    }

    void testBuildRightClimbStepsVec() {
        Solution solution;
        vector<int> vec;
        vector<int> expectedRightClimbStepsVec;
        vector<int> actualRightClimbStepsVec;

        vec = {2, 1, 4, 7, 3, 2, 5};
        expectedRightClimbStepsVec = {2, 1, 1, 3, 2, 1, 1};
        actualRightClimbStepsVec = solution.buildRightClimbStepsVec(vec);
        assert(actualRightClimbStepsVec == expectedRightClimbStepsVec);

        vec = {2, 2, 2};
        expectedRightClimbStepsVec = {1, 1, 1};
        actualRightClimbStepsVec = solution.buildRightClimbStepsVec(vec);
        assert(actualRightClimbStepsVec == expectedRightClimbStepsVec);

        printf("testBuildRightClimbStepsVec passed.\n");
    }
};

int main() {
    SolutionTest solutionTest;

    solutionTest.testLongestMountain();
    solutionTest.testBuildLeftClimbStepsVec();
    solutionTest.testBuildRightClimbStepsVec();

    return 0;
}
