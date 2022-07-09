// LeetCode-1769: https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/

#include <cstdio>
#include <vector>
#include <climits>
#include <cmath>
#include <string>
#include <cassert>

using namespace std;

class Solution {
private:
    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");
    }

    vector<int> getMovesLeftToRight(string& boxes) {
        int len = boxes.size();
        vector<int> numMovesLeftToRight(len, 0);

        int numBalls = 0;
        for (int i = 0; i < len; i++) {
            numMovesLeftToRight[i] = (i == 0) ? 0 : (numMovesLeftToRight[i - 1] + numBalls);

            if (boxes[i] == '1') {
                numBalls++;
            }
        }

        return numMovesLeftToRight;
    }

    vector<int> getMovesRightToLeft(string& boxes) {
        int len = boxes.size();
        vector<int> numMovesRightToLeft(len, 0);

        int numBalls = 0;
        for (int i = len - 1; i >= 0; i--) {
            numMovesRightToLeft[i] = (i == (len - 1)) ? 0 : (numMovesRightToLeft[i + 1] + numBalls);

            if (boxes[i] == '1') {
                numBalls++;
            }
        }

        return numMovesRightToLeft;
    }

    vector<int> getSumVec(vector<int>& vec1, vector<int>& vec2) {
        int len = vec1.size();

        vector<int> vecSum(len, 0);
        for (int i = 0; i < len; i++) {
            vecSum[i] = vec1[i] + vec2[i];
        }

        return vecSum;
    }

public:
    friend class SolutionTest;

    vector<int> minOperations(string boxes) {
        int len = boxes.size();

        vector<int> numMovesLeftToRight = getMovesLeftToRight(boxes);
        vector<int> numMovesRightToLeft = getMovesRightToLeft(boxes);

        vector<int> numMovesTotal = getSumVec(numMovesLeftToRight, numMovesRightToLeft);
        return numMovesTotal;
    }
};

class SolutionTest {
public:
    void testMinOperations() {
        Solution soln = Solution();
        string boxesIn;
        vector<int> movesOutExpected;
        vector<int> movesOutComputed;

        boxesIn = "110";
        movesOutExpected = {1, 1, 3};
        movesOutComputed = soln.minOperations(boxesIn);
//        soln.showVec(movesOutComputed, "movesOutComputed");
        assert(movesOutComputed == movesOutExpected);

        boxesIn = "001011";
        movesOutExpected = {11, 8, 5, 4, 3, 4};
        movesOutComputed = soln.minOperations(boxesIn);
//        soln.showVec(movesOutComputed, "movesOutComputed");
        assert(movesOutComputed == movesOutExpected);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinOperations();

    return 0;
}
