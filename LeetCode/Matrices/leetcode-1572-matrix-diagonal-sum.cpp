// LeetCode-1572: https://leetcode.com/problems/matrix-diagonal-sum/

#include <vector>

using namespace std;

class Solution {
private:

    // ------ separate functions to calculate sum of both diagonals ------

    int findSumOfTopLeftToBottomRightDiagonal(vector<vector<int>>& mat) {
        int sideLength = mat.size();

        int sum = 0;
        for (int i = 0; i < sideLength; i++) {
            sum += mat[i][i];
        }

        return sum;
    }

    int findSumOfTopRightToBottomLeftDiagonal(vector<vector<int>>& mat) {
        int sideLength = mat.size();

        int sum = 0;
        for (int i = 0; i < sideLength; i++) {
            sum += mat[i][sideLength - i - 1];
        }

        return sum;
    }

    // ------ single function to calculate sum of both diagonals ------

    int findSumOfDiagonal(vector<vector<int>>& mat, bool mainDiagonal) {
        int sideLength = mat.size();

        int colStartIdx;
        int colDiff;
        if (mainDiagonal) {
            colStartIdx = 0;
            colDiff = 1;
        } else {
            colStartIdx = sideLength - 1;
            colDiff = -1;
        }

        int sum = 0;
        for (int i = 0, j = colStartIdx; i < sideLength; i++, j += colDiff) {
            sum += mat[i][j];
        }

        return sum;
    }

public:
    int diagonalSum(vector<vector<int>>& mat) {
        // int sum1 = findSumOfTopLeftToBottomRightDiagonal(mat);
        // int sum2 = findSumOfTopRightToBottomLeftDiagonal(mat);

        int sum1 = findSumOfDiagonal(mat, true);
        int sum2 = findSumOfDiagonal(mat, false);
        int totalSum = sum1 + sum2;

        int sideLength = mat.size();
        if ((sideLength % 2) != 0) {
            int halfSideLength = sideLength / 2;
            totalSum -= mat[halfSideLength][halfSideLength];
        }

        return totalSum;
    }
};
