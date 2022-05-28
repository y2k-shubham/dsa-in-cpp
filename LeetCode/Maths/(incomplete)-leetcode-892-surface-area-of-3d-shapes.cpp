// LeetCode-892: https://leetcode.com/problems/surface-area-of-3d-shapes/
// incomplete

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    int calcBaseArea(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }

        int numRows = grid.size();
        int numCols = grid[0].size();

        int baseArea = numRows * numCols;

        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numCols; c++) {
                if (grid[r][c] == 0) {
                    baseArea--;
                }
            }
        }

        return baseArea;
    }

    int calcOuterArea(vector<vector<int>>& grid, int row, int col) {
        if (grid.empty()) {
            return 0;
        }

        int numRows = grid.size();
        int numCols = grid[0].size();
        if ((row < 0) || (row >= numRows) || (col < 0) || (col >= numCols)) {
            return -1;
        }

        bool isOnTopBottomEdge = (row == 0) || (row == (numRows - 1));
        bool isOnLeftRightEdge = (col == 0) || (col == (numCols - 1));

        int outerArea;
        if (!isOnLeftRightEdge && !isOnTopBottomEdge) {
            outerArea = 0;
        } else if (isOnLeftRightEdge && isOnTopBottomEdge) {
            outerArea = grid[row][col] * 2;
        } else if (isOnLeftRightEdge || isOnTopBottomEdge) {
            outerArea = grid[row][col];
        }

        return outerArea;
    }

public:
    friend class SolutionTest;

    int surfaceArea(vector<vector<int>>& grid) {

    }
};

class SolutionTest {
public:
    void testCalcBaseArea() {
        Solution soln = Solution();
        vector<vector<int> > grid;
        int areaOutExpected, areaOutComputed;

        grid = {};
        areaOutExpected = 0;
        areaOutComputed = soln.calcBaseArea(grid);
        assert(areaOutExpected == areaOutComputed);

        grid = {{1}};
        areaOutExpected = 1;
        areaOutComputed = soln.calcBaseArea(grid);
        assert(areaOutExpected == areaOutComputed);

        grid = {{0}};
        areaOutExpected = 0;
        areaOutComputed = soln.calcBaseArea(grid);
        assert(areaOutExpected == areaOutComputed);

        grid = {{1, 0, 1}};
        areaOutExpected = 2;
        areaOutComputed = soln.calcBaseArea(grid);
        assert(areaOutExpected == areaOutComputed);

        grid = {{1, 0, 1},
                {1, 3, 2}};
        areaOutExpected = 5;
        areaOutComputed = soln.calcBaseArea(grid);
        assert(areaOutExpected == areaOutComputed);
    }

    void testCalcOuterArea() {
        Solution soln = Solution();
        vector<vector<int>> gridIn;
        int rowIn, colIn;
        int areaOutExpected, areaOutComputed;

        gridIn = {};
        rowIn = 0;
        colIn = 0;
        areaOutExpected = 0;
        areaOutComputed = soln.calcOuterArea(gridIn, rowIn, colIn);
        assert(areaOutExpected == areaOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcBaseArea();
    solnTest.testCalcOuterArea();

    return 0;
}
