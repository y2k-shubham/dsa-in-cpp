// LeetCode-1139: https://leetcode.com/problems/largest-1-bordered-square
// TusharRoy: https://www.youtube.com/watch?v=vi_1eHCsR9A

#include <vector>
#include <cassert>
#include <cstdio>

using namespace std;

class NumContinuous1s {
public:
    int left;
    int up;
};

class Solution {
private:
    bool debug = false;

    int rows;
    int cols;
    vector<vector<int>> grid;
    vector<vector<NumContinuous1s>> memoMat;

    void init(vector<vector<int>>& grid) {
        this->grid = grid;
        if (debug) {
            showGrid();
        }

        rows = this->grid.size();
        cols = this->grid[0].size();
        memoMat.resize(rows, vector<NumContinuous1s>(cols));

        fillMemoMatTopLeftToBottomRight();
    }

    void reset() {
        this->grid = {};
        this->memoMat = {};
    }

    void fillMemoMatTopLeftToBottomRight() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    continue;
                }

                memoMat[i][j].left = (j == 0) ? grid[i][j] : (memoMat[i][j - 1].left + 1);
                if (memoMat[i][j].left == 3 && j == 0) {
                    printf("at i=%d, j=%d filled memoMat[i][j].left=%d, grid[i][j]=%d\n", i, j, memoMat[i][j].left, grid[i][j]);
                }
                memoMat[i][j].up = (i == 0) ? grid[i][j] : (memoMat[i - 1][j].up + 1);
            }
        }
    }

    int findLargestBoundedSquareSideLength() {
        int maxSideLen = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    continue;
                }

                int sideLenHere = 1;
                int maxPossibleSideLenHere = min(memoMat[i][j].up, memoMat[i][j].left);
                for (int k = maxPossibleSideLenHere; k > maxSideLen; k--) {
                    // IMPORTANT: this +1 adjustment in following is very important,
                    // otherwise we'll end up with indices -1
                    int leftUpLen = memoMat[i][j - k + 1].up;
                    int upLeftLen = memoMat[i - k + 1][j].left;

                    if (min(leftUpLen, upLeftLen) >= k) {
                        sideLenHere = k;

//                        if (debug) {
//                            printf("at i=%d, j=%d [maxPossibleSideLenHere=%d] and k=%d found sideLenHere=%d and breaking\n", i, j, maxPossibleSideLenHere, k, sideLenHere);
//                        }

                        // we can't find a square greater than this
                        // and all subsequent squares will be smaller
                        break;
                    } else {
//                        if (debug) {
//                            printf("at i=%d, j=%d [maxPossibleSideLenHere=%d] sideLen of k=%d doesn't exist\n", i, j, maxPossibleSideLenHere, k);
//                        }
                    }
                }

                maxSideLen = max(maxSideLen, sideLenHere);
            }
        }

        return maxSideLen;
    }

    void showGrid() {
        printf("\ngrid is:-\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%d ", grid[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    void showMemoMat() {
        printf("\nmemoMat is:-\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("(%d,%d)", memoMat[i][j].left, memoMat[i][j].up);
            }
            printf("\n");
        }
        printf("\n");
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class SolutionTest;

    int largest1BorderedSquare(vector<vector<int>>& grid) {
        init(grid);
        if (debug) {
            showGrid();
            showMemoMat();
        }

        int maxSquareSideLen = findLargestBoundedSquareSideLength();

        reset();
        return maxSquareSideLen * maxSquareSideLen;
    }
};

class SolutionTest {
public:
    void testLargestBorderedSquare() {
        Solution soln = Solution();
        vector<vector<int>> gridIn;
        int maxBoundedSquareAreaOutExpected, maxBoundedSquareAreaOutComputed;

        gridIn = {{0}};
        maxBoundedSquareAreaOutExpected = 0;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{1}};
        maxBoundedSquareAreaOutExpected = 1;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{1, 1, 1},
                  {1, 0, 1},
                  {1, 1, 1}};
        maxBoundedSquareAreaOutExpected = 9;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{0, 1, 1},
                  {1, 0, 1},
                  {1, 1, 1}};
        maxBoundedSquareAreaOutExpected = 1;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{1, 1, 0, 0}};
        maxBoundedSquareAreaOutExpected = 1;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{0, 0, 0, 0, 1},
                  {1, 0, 1, 1, 1},
                  {1, 0, 1, 0, 1},
                  {1, 1, 1, 1, 1},
                  {0, 0, 1, 1, 1}};
        maxBoundedSquareAreaOutExpected = 9;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{0, 0, 0, 0, 1},
                  {1, 0, 0, 1, 1},
                  {1, 0, 1, 0, 1},
                  {1, 1, 1, 1, 1},
                  {0, 0, 1, 1, 1}};
        maxBoundedSquareAreaOutExpected = 4;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{0, 0, 0, 0, 1},
                  {1, 0, 1, 1, 1},
                  {1, 0, 0, 0, 1},
                  {1, 1, 1, 1, 1},
                  {0, 0, 1, 1, 1}};
        maxBoundedSquareAreaOutExpected = 4;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        gridIn = {{0, 0, 0, 0, 1},
                  {1, 0, 1, 0, 1},
                  {1, 0, 1, 0, 1},
                  {1, 1, 1, 1, 1},
                  {0, 0, 1, 1, 1}};
        maxBoundedSquareAreaOutExpected = 4;
        maxBoundedSquareAreaOutComputed = soln.largest1BorderedSquare(gridIn);
        assert(maxBoundedSquareAreaOutExpected == maxBoundedSquareAreaOutComputed);

        printf("[testLargestBorderedSquare] all test cases passed\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testLargestBorderedSquare();

    return 0;
}
