// https://leetcode.com/problems/spiral-matrix/
// https://www.interviewbit.com/problems/spiral-order-matrix-i/
// https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/

// solution taken from GFG video (quite intuitive approach)
// hard problem: just because a problem doesn't involve
// data-structures, does't mean it is easy

#include <cassert>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> mockIndicesTraversed(int, int, bool);
void testMockIndicesTraversed();
void showVec(vector<pair<int, int>> vec, string name);
void testSpiralOrder();
vector<int> spiralOrder(vector<vector<int>>& matrix);

int main() {
    testMockIndicesTraversed();
    testSpiralOrder();

    return 0;
}

void showVec(vector<pair<int, int>> vec, string name) {
    printf("\n%s vec is:-\n", name.c_str());

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("(%d, %d)\t", vec[i].first, vec[i].second);
    }
    cout << endl;
}

void testMockIndicesTraversed() {
    vector<pair<int, int>> outExpected;

    outExpected = {};
    assert(mockIndicesTraversed(0, 0, false) == outExpected);

    outExpected = {make_pair(0, 0)};
    assert(mockIndicesTraversed(1, 1, false) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(0, 1)};
    // showVec(mockIndicesTraversed(1, 2, false), "");
    assert(mockIndicesTraversed(1, 2, false) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(1, 0)};
    assert(mockIndicesTraversed(2, 1, false) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(0, 1),
        make_pair(1, 1),
        make_pair(1, 0)};
    // showVec(mockIndicesTraversed(2, 2, false), "");
    assert(mockIndicesTraversed(2, 2, false) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(0, 1),
        make_pair(1, 1),
        make_pair(2, 1),
        make_pair(2, 0),
        make_pair(1, 0),
    };
    assert(mockIndicesTraversed(3, 2, false) == outExpected);

    outExpected = {
        make_pair(0, 0),
        make_pair(0, 1),
        make_pair(0, 2),
        make_pair(0, 3),
        make_pair(0, 4),
        make_pair(1, 4),
        make_pair(2, 4),
        make_pair(2, 3),
        make_pair(2, 2),
        make_pair(2, 1),
        make_pair(2, 0),
        make_pair(1, 0),
        make_pair(1, 1),
        make_pair(1, 2),
        make_pair(1, 3),
    };
    assert(mockIndicesTraversed(3, 5, false) == outExpected);
}

vector<pair<int, int>> mockIndicesTraversed(int m, int n, bool debug) {
    vector<pair<int, int>> indicesTraversed;

    int rLo = 0, rHi = m - 1;
    int cLo = 0, cHi = n - 1;
    for (int elesTraversed = 1; elesTraversed <= (m * n); elesTraversed++) {
        for (int j = cLo; j <= cHi; j++) {
            indicesTraversed.push_back(make_pair(rLo, j));
            if (debug) {
                printf("loop-1: pushing (%d, %d)\n", rLo, j);
            }
            elesTraversed++;
        }
        rLo++;
        if (debug) {
            printf("after loop-1, rLo=%d, rHi=%d, cLo=%d, cHi=%d\n", rLo, rHi, cLo, cHi);
        }

        for (int i = rLo; i <= rHi; i++) {
            indicesTraversed.push_back(make_pair(i, cHi));
            if (debug) {
                printf("loop-2: pushing (%d, %d)\n", i, cHi);
            }
            elesTraversed++;
        }
        cHi--;
        if (debug) {
            printf("after loop-2, rLo=%d, rHi=%d, cLo=%d, cHi=%d\n", rLo, rHi, cLo, cHi);
        }

        // this condition is very important
        if (rLo <= rHi) {
            for (int j = cHi; j >= cLo; j--) {
                indicesTraversed.push_back(make_pair(rHi, j));
                if (debug) {
                    printf("loop-3: pushing (%d, %d)\n", rHi, j);
                }
                elesTraversed++;
            }
            rHi--;
            if (debug) {
                printf("after loop-3, rLo=%d, rHi=%d, cLo=%d, cHi=%d\n", rLo, rHi, cLo, cHi);
            }
        } else if (debug) {
            printf("loop-3 skipped: rLo=%d, rHi=%d, cLo=%d, cHi=%d\n", rLo, rHi, cLo, cHi);
        }

        // this condition is very important
        if (cLo <= cHi) {
            for (int i = rHi; i >= rLo; i--) {
                indicesTraversed.push_back(make_pair(i, cLo));
                if (debug) {
                    printf("loop-4: pushing (%d, %d)\n", i, cLo);
                }
                elesTraversed++;
            }
            cLo++;
            if (debug) {
                printf("after loop-4, rLo=%d, rHi=%d, cLo=%d, cHi=%d\n", rLo, rHi, cLo, cHi);
            }
        } else if (debug) {
            printf("loop-4 skipped: rLo=%d, rHi=%d, cLo=%d, cHi=%d\n", rLo, rHi, cLo, cHi);
        }
    }

    return indicesTraversed;
}

void testSpiralOrder() {
    vector<int> outExpected;
    vector<vector<int>> inp;

    inp = {};
    outExpected = {};
    assert(spiralOrder(inp) == outExpected);

    inp = {{1}};
    outExpected = {1};
    assert(spiralOrder(inp) == outExpected);

    inp = {{1, 2}};
    outExpected = {1, 2};
    assert(spiralOrder(inp) == outExpected);

    inp = {
        {1},
        {2}};
    outExpected = {1, 2};
    assert(spiralOrder(inp) == outExpected);

    inp = {
        {1, 2},
        {4, 3}};
    outExpected = {1, 2, 3, 4};
    assert(spiralOrder(inp) == outExpected);

    inp = {
        {1, 2, 3},
        {6, 5, 4}};
    outExpected = {1, 2, 3, 4, 5, 6};
    assert(spiralOrder(inp) == outExpected);

    inp = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {13, 14, 15}};
    outExpected = {1, 2, 3, 6, 9, 12, 15, 14, 13, 10, 7, 4, 5, 8, 11};
    assert(spiralOrder(inp) == outExpected);

    inp = {
        {1},
        {2},
        {3},
        {4}};
    outExpected = {1, 2, 3, 4};
    assert(spiralOrder(inp) == outExpected);

    inp = {{1, 2, 3, 4}};
    outExpected = {1, 2, 3, 4};
    assert(spiralOrder(inp) == outExpected);
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return {};
    } else {
        vector<int> spiralEles;
        int rLo = 0, rHi = ((int)matrix.size() - 1);
        int cLo = 0, cHi = ((int)matrix[0].size() - 1);

        while (rLo <= rHi && cLo <= cHi) {
            for (int j = cLo; j <= cHi; j++) {
                spiralEles.push_back(matrix[rLo][j]);
            }
            rLo++;

            for (int i = rLo; i <= rHi; i++) {
                spiralEles.push_back(matrix[i][cHi]);
            }
            cHi--;

            if (rLo <= rHi) {
                for (int j = cHi; j >= cLo; j--) {
                    spiralEles.push_back(matrix[rHi][j]);
                }
                rHi--;
            }

            if (cLo <= cHi) {
                for (int i = rHi; i >= rLo; i--) {
                    spiralEles.push_back(matrix[i][cLo]);
                }
                cLo++;
            }
        }
        return spiralEles;
    }
}
