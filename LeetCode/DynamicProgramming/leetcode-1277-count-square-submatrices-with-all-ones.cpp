// LeetCode-1277: https://leetcode.com/problems/count-square-submatrices-with-all-ones/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void showMat(vector<vector<int>>& mat, string msg) {
    int rows = mat.size();
    int cols = mat[0].size();

    printf("\n%s:-\n", msg.c_str());

    printf("\t");
    for (int j = 0; j < cols; j++) {
        printf("[%d]\t", j);
    }
    cout << endl;

    for (int i = 0; i < rows; i++) {
        printf("[%d]\t", i);
        for (int j = 0; j < cols; j++) {
            printf("%d\t", mat[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> createMat(vector<vector<int>>& mat) {
    int rows = mat.size();
    int cols = mat[0].size();

    vector<vector<int>> newMat(rows);
    for (int i = 0; i < rows; i++) {
        vector<int> newMatRow(cols);
        newMat[i] = newMatRow;
    }

    return newMat;
}

// LC submission => speed: 98 %tile, memory: 5 %tile
int fillMatCountSqrs(vector<vector<int>>& mat, vector<vector<int>>& sqrSizeMemoMat, bool debug) {
    int rows = mat.size();
    int cols = mat[0].size();

    int totalSqrs = 0;
    int crrSqrSize;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || j == 0) {
                crrSqrSize = mat[i][j];
            } else if (mat[i][j] == 1) {
                crrSqrSize = min(sqrSizeMemoMat[i - 1][j - 1], min(sqrSizeMemoMat[i][j - 1], sqrSizeMemoMat[i - 1][j])) + 1;
            } else {
                crrSqrSize = 0;
            }

            sqrSizeMemoMat[i][j] = crrSqrSize;
            totalSqrs = totalSqrs + crrSqrSize;
        }
    }

    return totalSqrs;
}

void testFillMatCountSqrs() {
    vector<vector<int>> mat;
    vector<vector<int>> sqrSizeMemoMat;
    vector<vector<int>> sqrSizeMemoMatExpected;
    int result;

    mat = {
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 1}};
    sqrSizeMemoMat = createMat(mat);
    result = fillMatCountSqrs(mat, sqrSizeMemoMat, false);
    // showMat(sqrSizeMemoMat, "after filling, sqrSizeMemoMat is:-");
    sqrSizeMemoMatExpected = {
        {0, 1, 1, 1},
        {1, 1, 2, 2},
        {0, 1, 2, 3}};
    assert(sqrSizeMemoMatExpected == sqrSizeMemoMat);
    assert(15 == result);

    mat = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 0}};
    sqrSizeMemoMat = createMat(mat);
    result = fillMatCountSqrs(mat, sqrSizeMemoMat, false);
    // showMat(sqrSizeMemoMat, "after filling, sqrSizeMemoMat is:-");
    sqrSizeMemoMatExpected = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 2, 0}};
    assert(sqrSizeMemoMatExpected == sqrSizeMemoMat);
    assert(7 == result);
}

int countSquares(vector<vector<int>>& matrix) {
    vector<vector<int>> sqrSizeMemoMat = createMat(matrix);
    return fillMatCountSqrs(matrix, sqrSizeMemoMat, false);
}

int main() {
    testFillMatCountSqrs();

    return 0;
}
