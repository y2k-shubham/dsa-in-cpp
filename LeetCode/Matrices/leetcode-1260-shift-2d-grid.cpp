// LeetCode-1260: https://leetcode.com/problems/shift-2d-grid/
// certainly not as easy as it may appear on the first sight

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
private:

    pair <int, int> calcShiftedCoords(pair <int, int> dimen, int k, pair <int, int> orgCoord) {
        int numRows = dimen.first;
        int numCols = dimen.second;
        int numCells = numRows * numCols;

        int orgI = orgCoord.first;
        int orgJ = orgCoord.second;
        int orgPosn = (orgI * numCols) + orgJ;

        int shiftedPosn = (orgPosn + k) % numCells;
        int shiftedI = shiftedPosn / numCols;
        int shiftedJ = shiftedPosn % numCols;

        return {shiftedI, shiftedJ};
    }

    vector<vector<int> > createMat(int m, int n) {
        vector<vector<int> > mat(m);
        for (int i = 0; i < m; i++) {
            vector<int> matRow(n);
            mat[i] = matRow;
        }

        return mat;
    }

public:
    friend class SolutionTest;

    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        pair <int, int> dimens = {m, n};

        vector<vector<int> > shiftedGrid = createMat(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pair <int, int> shiftedCoords = calcShiftedCoords(dimens, k, {i, j});
                int shiftedI = shiftedCoords.first;
                int shiftedJ = shiftedCoords.second;

                // printf("for [%d][%d], shifted posn is [%d][%d]\n", i, j, shiftedI, shiftedJ);
                shiftedGrid[shiftedI][shiftedJ] = grid[i][j];
            }
        }

        return shiftedGrid;
    }
};

class SolutionTest {
public:
    void testCalcShiftedCoords() {
        Solution soln = Solution();
        pair <int, int> dimenIn;
        int kIn;
        pair <int, int> orgCoordIn;
        pair <int, int> shiftedCoordOutExpected;
        pair <int, int> shiftedCoordOutComputed;

        dimenIn = {1, 1};
        kIn = 0;
        orgCoordIn = {0, 0};
        shiftedCoordOutExpected = {0, 0};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {1, 1};
        kIn = 1;
        orgCoordIn = {0, 0};
        shiftedCoordOutExpected = {0, 0};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {1, 1};
        kIn = 5;
        orgCoordIn = {0, 0};
        shiftedCoordOutExpected = {0, 0};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 1;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {0, 2};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 2;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {1, 0};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 4;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {1, 2};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 5;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {2, 0};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 7;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {2, 2};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 8;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {0, 0};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);

        dimenIn = {3, 3};
        kIn = 9;
        orgCoordIn = {0, 1};
        shiftedCoordOutExpected = {0, 1};
        shiftedCoordOutComputed = soln.calcShiftedCoords(dimenIn, kIn, orgCoordIn);
        assert(shiftedCoordOutExpected == shiftedCoordOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcShiftedCoords();

    return 0;
}
