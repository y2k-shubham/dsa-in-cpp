// LeetCode-2482: https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    void showVecRow(vector<int>& vec, const char* name) {
        printf("%s vector is:-\n", name);

        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");
    }

    void showVecCol(vector<int>& vec, const char* name) {
        printf("%s vector is:-\n", name);

        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t%d\n", i, vec[i]);
        }
    }

    void showMat(vector<vector<int> >& mat, const char* name) {
        printf("%s matrix is:-\n", name);

        int numRows = mat.size();
        int numCols = mat[0].size();

        printf("\t");
        for (int j = 0; j < numCols; j++) {
            printf("[%d]\t", j);
        }
        printf("\n");

        for (int i = 0; i < numRows; i++) {
            printf("[%d]\t", i);

            for (int j = 0; j < numCols; j++) {
                printf("%d\t", mat[i][j]);
            }
            printf("\n");
        }
    }

    vector<vector<int> > createMat(int numRows, int numCols, int defaultValue) {
        vector<vector<int> > mat(numRows);
        for (int i = 0; i < numRows; i++) {
            vector<int> row(numCols, defaultValue);
            mat[i] = row;
        }

        return mat;
    }

    inline int countNumsInRow(vector<vector<int> >& mat, int row, int num) {
        int numCols = mat[0].size();
        int count = 0;
        for (int j = 0; j < numCols; j++) {
            if (mat[row][j] == num) {
                count++;
            }
        }

        return count;
    }

    inline int countNumsInCol(vector<vector<int> >& mat, int col, int num) {
        int numRows = mat.size();
        int count = 0;
        for (int i = 0; i < numRows; i++) {
            if (mat[i][col] == num) {
                count++;
            }
        }

        return count;
    }

    vector<int> createNumsFreqInRowsVec(vector<vector<int> >& mat, int num) {
        int numRows = mat.size();
        int numCols = mat[0].size();

        vector<int> freqVec(numRows, 0);
        for (int i = 0; i < numRows; i++) {
            freqVec[i] = countNumsInRow(mat, i, num);
        }

        return freqVec;
    }

    vector<int> createNumsFreqInColsVec(vector<vector<int> >& mat, int num) {
        int numRows = mat.size();
        int numCols = mat[0].size();

        vector<int> freqVec(numCols, 0);
        for (int j = 0; j < numCols; j++) {
            freqVec[j] = countNumsInCol(mat, j, num);
        }

        return freqVec;
    }

public:
    friend class SolutionTest;

    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int numRows = grid.size();
        int numCols = grid[0].size();

        vector<int> freq1sInRows = createNumsFreqInRowsVec(grid, 1);
        vector<int> freq1sInCols = createNumsFreqInColsVec(grid, 1);
        vector<int> freq0sInRows = createNumsFreqInRowsVec(grid, 0);
        vector<int> freq0sInCols = createNumsFreqInColsVec(grid, 0);

//        showVecCol(freq1sInRows, "freq1sInRows");
//        showVecRow(freq1sInCols, "freq1sInCols");
//        showVecCol(freq0sInRows, "freq0sInRows");
//        showVecRow(freq0sInCols, "freq0sInCols");

        vector<vector<int> > mat = createMat(numRows, numCols, 0);
        for (int i = 0; i < numRows; i++) {
            int diff1 = freq1sInRows[i] - freq0sInRows[i];
//            printf("at i=%d, diff1 = %d - %d = %d\n", i, freq1sInRows[i], freq0sInRows[i], diff1);
            for (int j = 0; j < numCols; j++) {
                mat[i][j] = diff1 + freq1sInCols[j] - freq0sInCols[j];
//                printf("at i=%d,j=%d, diff = %d + %d - %d = %d\n", i, j, diff1, freq1sInCols[j], freq0sInCols[j], mat[i][j]);
            }
        }

        return mat;
    }
};

class SolutionTest {
public:
    void testOnesMinusZeros() {
        Solution soln = Solution();
        vector<vector<int> > grid;
        vector<vector<int> > matOutExpected;
        vector<vector<int> > matOutComputed;

        grid = {{0, 1, 1},
                {1, 0, 1},
                {0, 0, 1}};
        matOutExpected = {{0,  0,  4},
                          {0,  0,  4},
                          {-2, -2, 2}};
        matOutComputed = soln.onesMinusZeros(grid);
//        soln.showMat(matOutComputed, "matOutComputed");
        assert(matOutExpected == matOutComputed);

        grid = {{1, 1, 1},
                {1, 1, 1}};
        matOutExpected = {{5, 5, 5},
                          {5, 5, 5}};
        matOutComputed = soln.onesMinusZeros(grid);
        assert(matOutExpected == matOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testOnesMinusZeros();

    return 0;
}
