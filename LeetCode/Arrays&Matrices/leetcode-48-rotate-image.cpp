// LeetCode 48: https://leetcode.com/problems/rotate-image/
// https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
// extremely time consuming to implement,
// better watch video and find easier / faster way

#include <cassert>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<int> pocRingCounter(int);
void testPocRingCounter();
int pocEleQuadsToMoveCounter(int, int);
void testPocEleQuadsToMoveCounter();
vector<pair<int, int> > pocQuadIndices(int, int, int);
void testPocQuadIndices();
void showVec(vector<pair<int, int> >, string);
void showMat(vector<vector<int> > mat, string name);
void testRotate();
void rotate(vector<vector<int> >&);
void testRotateRight();
void rotateRight(vector<vector<int> >&);

int main() {
    testPocRingCounter();
    testPocEleQuadsToMoveCounter();
    testPocQuadIndices();

    testRotate();
    testRotateRight();

    return 0;
}

void showVec(vector<pair<int, int> > vec, string name) {
    printf("\n%s vec is:-\n", name.c_str());

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Pair:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("(%d, %d)\t", vec[i].first, vec[i].second);
    }
    cout << endl;
}

void showMat(vector<vector<int> > mat, string name) {
    printf("\n%s mat is:-\n", name.c_str());

    printf("\t");
    for (int i = 0; i < mat.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    for (int i = 0; i < mat.size(); i++) {
        printf("[%d]\t", i);
        for (int j = 0; j < mat.size(); j++) {
            printf("%d\t", mat[i][j]);
        }
        cout << endl;
    }
}

void testPocRingCounter() {
    vector<int> outExpected;

    outExpected = {};
    assert(pocRingCounter(0) == outExpected);

    outExpected = {};
    assert(pocRingCounter(1) == outExpected);

    outExpected = {1};
    assert(pocRingCounter(2) == outExpected);

    outExpected = {1};
    assert(pocRingCounter(3) == outExpected);

    outExpected = {1, 2};
    assert(pocRingCounter(4) == outExpected);

    outExpected = {1, 2};
    assert(pocRingCounter(5) == outExpected);

    outExpected = {1, 2, 3};
    assert(pocRingCounter(6) == outExpected);

    outExpected = {1, 2, 3};
    assert(pocRingCounter(7) == outExpected);
}

vector<int> pocRingCounter(int n) {
    vector<int> counterVals;

    for (int i = 1; i <= (n / 2); i++) {
        counterVals.push_back(i);
    }

    return counterVals;
}

void testPocEleQuadsToMoveCounter() {
    assert(pocEleQuadsToMoveCounter(0, 1) == 0);
    assert(pocEleQuadsToMoveCounter(1, 1) == 0);
    assert(pocEleQuadsToMoveCounter(2, 1) == 1);
    assert(pocEleQuadsToMoveCounter(3, 1) == 2);
    assert(pocEleQuadsToMoveCounter(4, 1) == 3);
    assert(pocEleQuadsToMoveCounter(4, 2) == 1);
    assert(pocEleQuadsToMoveCounter(5, 1) == 4);
    assert(pocEleQuadsToMoveCounter(5, 2) == 2);
    assert(pocEleQuadsToMoveCounter(6, 1) == 5);
    assert(pocEleQuadsToMoveCounter(6, 2) == 3);
    assert(pocEleQuadsToMoveCounter(6, 3) == 1);
}

int pocEleQuadsToMoveCounter(int n, int r) {
    return max(0, (n - 2 * (r - 1) - 1));
}

void testPocQuadIndices() {
    vector<pair<int, int> > outExpected;

    outExpected = {
        make_pair(0, 0),
        make_pair(1, 0),
        make_pair(1, 1),
        make_pair(0, 1)};
    // showVec(pocQuadIndices(2, 1, 1), "");
    assert(pocQuadIndices(2, 1, 1) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(2, 0),
        make_pair(2, 2),
        make_pair(0, 2)};
    assert(pocQuadIndices(3, 1, 1) == outExpected);

    outExpected = {
        make_pair(1, 0),
        make_pair(2, 1),
        make_pair(1, 2),
        make_pair(0, 1)};
    // showVec(pocQuadIndices(3, 1, 2), "");
    assert(pocQuadIndices(3, 1, 2) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(3, 0),
        make_pair(3, 3),
        make_pair(0, 3)};
    assert(pocQuadIndices(4, 1, 1) == outExpected);

    outExpected = {
        make_pair(1, 0),
        make_pair(3, 1),
        make_pair(2, 3),
        make_pair(0, 2)};
    assert(pocQuadIndices(4, 1, 2) == outExpected);

    outExpected = {
        make_pair(2, 0),
        make_pair(3, 2),
        make_pair(1, 3),
        make_pair(0, 1)};
    assert(pocQuadIndices(4, 1, 3) == outExpected);

    outExpected = {
        make_pair(1, 1),
        make_pair(2, 1),
        make_pair(2, 2),
        make_pair(1, 2)};
    // showVec(pocQuadIndices(4, 2, 1), "");
    assert(pocQuadIndices(4, 2, 1) == outExpected);
}

vector<pair<int, int> > pocQuadIndices(int n, int r, int i) {
    return {
        make_pair(r - 1 + i - 1, r - 1),
        make_pair(n - r, r - 1 + i - 1),
        make_pair(n - r - (i - 1), n - r),
        make_pair(r - 1, n - r - (i - 1))};
}

void testRotate() {
    vector<vector<int> > inp;
    vector<vector<int> > outExpected;

    inp = {};
    outExpected = {};
    rotate(inp);
    assert(inp == outExpected);

    inp = {{1}};
    outExpected = {{1}};
    rotate(inp);
    assert(inp == outExpected);

    inp = {
        {1, 2},
        {3, 4}};
    outExpected = {
        {2, 4},
        {1, 3}};
    rotate(inp);
    assert(inp == outExpected);

    inp = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    outExpected = {
        {3, 6, 9},
        {2, 5, 8},
        {1, 4, 7}};
    rotate(inp);
    assert(inp == outExpected);

    inp = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};
    outExpected = {
        {4, 8, 12, 16},
        {3, 7, 11, 15},
        {2, 6, 10, 14},
        {1, 5, 9, 13}};
    rotate(inp);
    // showMat(inp, "");
    // assert(inp == outExpected);

    inp = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}};
    outExpected = {
        {5, 10, 15, 20, 25},
        {4, 9, 14, 19, 24},
        {3, 8, 13, 18, 23},
        {2, 7, 12, 17, 22},
        {1, 6, 11, 16, 21}};
    rotate(inp);
    // showMat(inp, "");
    assert(inp == outExpected);
}

void rotate(vector<vector<int> >& matrix) {
    int n = matrix.size();

    for (int r = 1; r <= (n / 2); r++) {
        int eleQuadsToMove = max(0, (n - 2 * (r - 1) - 1));
        for (int i = 1; i <= eleQuadsToMove; i++) {
            int tl = matrix[r - 1 + i - 1][r - 1];
            int bl = matrix[n - r][r - 1 + i - 1];
            int br = matrix[n - r - (i - 1)][n - r];
            int tr = matrix[r - 1][n - r - (i - 1)];

            matrix[n - r][r - 1 + i - 1] = tl;
            matrix[n - r - (i - 1)][n - r] = bl;
            matrix[r - 1][n - r - (i - 1)] = br;
            matrix[r - 1 + i - 1][r - 1] = tr;
        }
    }
}

void testRotateRight() {
    vector<vector<int> > inp;
    vector<vector<int> > outExpected;

    inp = {
        {1, 2},
        {3, 4}};
    outExpected = {
        {3, 1},
        {4, 2}};
    rotateRight(inp);
    assert(inp == outExpected);

    inp = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    outExpected = {
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3}};
    rotateRight(inp);
    assert(inp == outExpected);
}

void rotateRight(vector<vector<int> >& matrix) {
    int n = matrix.size();

    for (int r = 1; r <= (n / 2); r++) {
        int eleQuadsToMove = max(0, (n - 2 * (r - 1) - 1));
        for (int i = 1; i <= eleQuadsToMove; i++) {
            int tl = matrix[r - 1 + i - 1][r - 1];
            int bl = matrix[n - r][r - 1 + i - 1];
            int br = matrix[n - r - (i - 1)][n - r];
            int tr = matrix[r - 1][n - r - (i - 1)];

            matrix[r - 1][n - r - (i - 1)] = tl;
            matrix[n - r - (i - 1)][n - r] = tr;
            matrix[n - r][r - 1 + i - 1] = br;
            matrix[r - 1 + i - 1][r - 1] = bl;
        }
    }
}
