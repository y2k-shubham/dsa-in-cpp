// LeetCode-463: https://leetcode.com/problems/island-perimeter

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    inline int findPerimeterContribution(vector<vector<int>>& grid, int r, int c) {
        int contribution = 0;

        if (r == 0 || grid[r - 1][c] == 0) {
            contribution++;
        }

        if (r == grid.size() - 1 || grid[r + 1][c] == 0) {
            contribution++;
        }

        if (c == 0 || grid[r][c - 1] == 0) {
            contribution++;
        }

        if (c == grid[0].size() - 1 || grid[r][c + 1] == 0) {
            contribution++;
        }

        return contribution;
    }

public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;

        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == 1) {
                    perimeter += findPerimeterContribution(grid, r, c);
                }
            }
        }

        return perimeter;
    }
};

class SolutionTest {
public:
    void testIslandPerimeter() {
        Solution soln = Solution();
        vector<vector<int>> grid;
        int perimeterOutExpected, perimeterOutComputed;

        grid = {{0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 1, 0, 0},
                {1, 1, 0, 0}};
        perimeterOutExpected = 16;
        perimeterOutComputed = soln.islandPerimeter(grid);
        assert(perimeterOutExpected == perimeterOutComputed);

        grid = {{1}};
        perimeterOutExpected = 4;
        perimeterOutComputed = soln.islandPerimeter(grid);
        assert(perimeterOutExpected == perimeterOutComputed);

        grid = {{1, 0}};
        perimeterOutExpected = 4;
        perimeterOutComputed = soln.islandPerimeter(grid);
        assert(perimeterOutExpected == perimeterOutComputed);

        grid = {{0, 0}};
        perimeterOutExpected = 0;
        perimeterOutComputed = soln.islandPerimeter(grid);
        assert(perimeterOutExpected == perimeterOutComputed);

        grid = {{1, 1}};
        perimeterOutExpected = 6;
        perimeterOutComputed = soln.islandPerimeter(grid);
        assert(perimeterOutExpected == perimeterOutComputed);

        grid = {{1, 0, 1}};
        perimeterOutExpected = 8;
        perimeterOutComputed = soln.islandPerimeter(grid);
        assert(perimeterOutExpected == perimeterOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testIslandPerimeter();

    return 0;
}
