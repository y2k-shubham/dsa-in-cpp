// LeetCode-498: https://leetcode.com/problems/diagonal-traverse/
// LeetCode Monthly Challenge: https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3580/
// GFG: https://www.geeksforgeeks.org/print-matrix-diagonal-pattern/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

bool reachedEdge(int rows, int cols, int i, int j, bool upwards) {
    ostringstream oss;

    if (rows <= 0 || cols <= 0) {
        oss << "invalid dimensions: rows = " << rows << ", cols = " << cols;
        throw invalid_argument(oss.str());
    } else if ((i < 0) || (i >= rows) || (j < 0) || (j >= cols)) {
        oss << "invalid indices: for rows = " << rows << ", cols = " << cols << ", i = " << i << ", j = " << j;
        throw invalid_argument(oss.str());
    }

    if (upwards) {
        return (i == 0 || j == (cols - 1));
    } else {
        return (i == (rows - 1) || j == 0);
    }
}

void testReachedEdge() {
    int rows, cols;
    int i, j;
    bool upwards;
    bool exceptionThrown;

    // rows / cols <= 0
    rows = -1, cols = 0;
    i = 0, j = 0;
    upwards = true;
    exceptionThrown = false;
    try {
        reachedEdge(rows, cols, i, j, upwards);
    } catch (invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // i / j exceeds dimensions of matrices
    rows = 1, cols = 1;
    i = 0, j = 2;
    upwards = true;
    exceptionThrown = false;
    try {
        reachedEdge(rows, cols, i, j, upwards);
    } catch (invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // normal 1x1 - 1
    rows = 1, cols = 1;
    i = 0, j = 0;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 2x2 - 1
    rows = 2, cols = 2;
    i = 0, j = 0;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 2x2 - 2
    rows = 2, cols = 2;
    i = 0, j = 1;
    upwards = false;
    assert(reachedEdge(rows, cols, i, j, upwards) == false);

    // normal 2x2 - 3
    rows = 2, cols = 2;
    i = 1, j = 0;
    upwards = false;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 2x2 - 4
    rows = 2, cols = 2;
    i = 1, j = 1;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 3x3 - 1
    rows = 3, cols = 3;
    i = 0, j = 0;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 3x3 - 2
    rows = 3, cols = 3;
    i = 0, j = 1;
    upwards = false;
    assert(reachedEdge(rows, cols, i, j, upwards) == false);

    // normal 3x3 - 3
    rows = 3, cols = 3;
    i = 1, j = 0;
    upwards = false;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 3x3 - 4
    rows = 3, cols = 3;
    i = 2, j = 0;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == false);

    // normal 3x3 - 4
    rows = 3, cols = 3;
    i = 1, j = 1;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == false);

    // normal 3x3 - 5
    rows = 3, cols = 3;
    i = 0, j = 2;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 3x3 - 6
    rows = 3, cols = 3;
    i = 1, j = 2;
    upwards = false;
    assert(reachedEdge(rows, cols, i, j, upwards) == false);

    // normal 3x3 - 7
    rows = 3, cols = 3;
    i = 2, j = 1;
    upwards = false;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);

    // normal 3x3 - 8
    rows = 3, cols = 3;
    i = 2, j = 2;
    upwards = true;
    assert(reachedEdge(rows, cols, i, j, upwards) == true);
}

vector<int> findDiagonalOrder(vector<vector<int>>& matrix, bool debug) {
    vector<int> diagOrderTraversal;

    int rows = matrix.size();
    if (rows == 0) {
        return {};
    }
    int cols = matrix[0].size();

    int numElesSeen = 0;

    int rBegin = 0;
    int cBegin = 0;
    bool upwards = true;
    while (numElesSeen < (rows * cols)) {
        int i = rBegin;
        int j = cBegin;

        if (debug) {
            printf("\n----------\n");
            printf("rBegin=%d, cBegin=%d, dir=%s\n", rBegin, cBegin, (upwards ? "upwards" : "downwards"));
        }

        if (upwards) {
            while (!reachedEdge(rows, cols, i, j, upwards)) {
                if (debug) {
                    printf("in    loop, at matrix[i=%d][j=%d] = %d\n", i, j, matrix[i][j]);
                }
                diagOrderTraversal.push_back(matrix[i][j]);
                numElesSeen++;
                i--;
                j++;
            }
        } else {
            while (!reachedEdge(rows, cols, i, j, upwards)) {
                if (debug) {
                    printf("in    loop, at matrix[i=%d][j=%d] = %d\n", i, j, matrix[i][j]);
                }
                diagOrderTraversal.push_back(matrix[i][j]);
                numElesSeen++;
                i++;
                j--;
            }
        }
        diagOrderTraversal.push_back(matrix[i][j]);
        if (debug) {
            printf("after loop, at matrix[i=%d][j=%d] = %d\n", i, j, matrix[i][j]);
        }
        numElesSeen++;

        if (upwards) {
            if (j < (cols - 1)) {
                rBegin = 0;
                cBegin = min(j + 1, cols - 1);
            } else {
                rBegin = min(i + 1, rows - 1);
                cBegin = (cols - 1);
            }
        } else {
            if (i < (rows - 1)) {
                rBegin = min(i + 1, rows - 1);
                cBegin = 0;
            } else {
                if (debug) {
                    printf("here-4,\nsetting rBegin = (rows=%d - 1) = %d\nsetting cBegin = min(j=%d + 1, cols=%d - 1) = %d\n", rows, (rows - 1), j, cols, min(j + 1, cols - 1));
                }
                rBegin = rows - 1;
                cBegin = min(j + 1, cols - 1);
            }
        }
        upwards = !upwards;
    }

    return diagOrderTraversal;
}

void testFindDiagonalOrder() {
    vector<vector<int>> matrix;
    vector<int> diagOrderTraversalOutExpected;
    vector<int> diagOrderTraversalOutComputed;

    // printf("\ntest-case-1\n");
    matrix = {{9}};
    diagOrderTraversalOutExpected = {9};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-2\n");
    matrix = {
        {9},
        {6}};
    diagOrderTraversalOutExpected = {9, 6};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-3\n");
    matrix = {
        {9, 6}};
    diagOrderTraversalOutExpected = {9, 6};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-4\n");
    matrix = {
        {9, 1},
        {8, 7}};
    diagOrderTraversalOutExpected = {9, 1, 8, 7};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-5\n");
    matrix = {
        {9, 1, 5},
        {8, 7, 4}};
    diagOrderTraversalOutExpected = {9, 1, 8, 7, 5, 4};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-6\n");
    matrix = {
        {9, 1, 5},
        {8, 7, 4},
        {18, 11, 6}};
    diagOrderTraversalOutExpected = {9, 1, 8, 18, 7, 5, 4, 11, 6};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-7\n");
    matrix = {
        {9, 1, 5, -1},
        {8, 7, 4, 14},
        {18, 11, 6, 7}};
    diagOrderTraversalOutExpected = {9, 1, 8, 18, 7, 5, -1, 4, 11, 6, 14, 7};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);

    // printf("\ntest-case-8\n");
    matrix = {
        {9, 1, 5, -1, 12},
        {8, 7, 4, 14, 19},
        {18, 11, 6, 7, 10}};
    diagOrderTraversalOutExpected = {9, 1, 8, 18, 7, 5, -1, 4, 11, 6, 14, 12, 19, 7, 10};
    diagOrderTraversalOutComputed = findDiagonalOrder(matrix, false);
    assert(diagOrderTraversalOutExpected == diagOrderTraversalOutComputed);
}

int main() {
    testReachedEdge();
    testFindDiagonalOrder();

    return 0;
}
