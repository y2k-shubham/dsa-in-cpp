// LeetCode-3030: https://leetcode.com/problems/find-the-grid-of-region-average
// simple do-as-directed but cumbersome to code

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    void showMat(vector<vector<int> >& mat, const char* name) {
        printf("%s matrix is:-\n", name);

        for (int j = 0; j < mat[0].size(); j++) {
            printf("\t[%d]", j);
        }
        printf("\n");

        for (int i = 0; i < mat.size(); i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < mat[0].size(); j++) {
                printf("%d\t", mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    inline bool isEdgePixel(vector<vector<int> >& mat, int row, int col) {
        int rows = mat.size();
        int cols = mat[0].size();

        if (row == 0 || row == rows - 1) {
            return true;
        }

        if (col == 0 || col == cols - 1) {
            return true;
        }

        return false;
    }

    inline bool isCornerPixel(vector<vector<int> >& mat, int row, int col) {
        int rows = mat.size();
        int cols = mat[0].size();

        return isEdgePixel(mat, row, col) && (row == 0 || row == rows - 1) && (col == 0 || col == cols - 1);
    }

    inline bool canBeCenterOfARegion(vector<vector<int> >& mat, int row, int col) {
        return !isEdgePixel(mat, row, col);
    }

    inline int calcRegionAvgIntensity(vector<vector<int> >& mat, int threshold, int row, int col) {
        if (!canBeCenterOfARegion(mat, row, col)) {
            return -1;
        }

        int b00 = mat[row - 1][col - 1];
        int b01 = mat[row - 1][col];
        int b02 = mat[row - 1][col + 1];

        int b10 = mat[row][col - 1];
        int b11 = mat[row][col];
        int b12 = mat[row][col + 1];

        int b20 = mat[row + 1][col - 1];
        int b21 = mat[row + 1][col];
        int b22 = mat[row + 1][col + 1];

        int brightnessSum = 0;

        // first row
        if (max(abs(b00 - b01), abs(b00 - b10)) <= threshold) {
            brightnessSum += b00;
        } else {
//            printf("returned -1 at 00\n");
            return -1;
        }
        if (max(abs(b01 - b00), max(abs(b01 - b02), abs(b01 - b11))) <= threshold) {
            brightnessSum += b01;
        } else {
//            printf("returned -1 at 01\n");
            return -1;
        }
        if (max(abs(b02 - b01), abs(b02 - b12)) <= threshold) {
            brightnessSum += b02;
        } else {
//            printf("returned -1 at 02 because diff=%d > threshold=%d\n", max(abs(b02 - b01), abs(b02 - b12)), threshold);
            return -1;
        }

        // second row
        if (max(abs(b10 - b00), max(abs(b10 - b11), abs(b10 - b20))) <= threshold) {
            brightnessSum += b10;
        } else {
//            printf("returned -1 at 10\n");
            return -1;
        }
        if (max(max(abs(b11 - b01), abs(b11 - b10)), max(abs(b11 - b12), abs(b11 - b21))) <= threshold) {
            brightnessSum += b11;
        } else {
//            printf("returned -1 at 11\n");
            return -1;
        }
        if (max(max(abs(b12 - b02), abs(b12 - b11)), abs(b12 - b22)) <= threshold) {
            brightnessSum += b12;
        } else {
//            printf("returned -1 at 12\n");
            return -1;
        }

        // third row
        if (max(abs(b20 - b10), abs(b20 - b21)) <= threshold) {
            brightnessSum += b20;
        } else {
//            printf("returned -1 at 20\n");
            return -1;
        }
        if (max(abs(b21 - b11), max(abs(b21 - b20), abs(b21 - b22))) <= threshold) {
            brightnessSum += b21;
        } else {
//            printf("returned -1 at 21\n");
            return -1;
        }
        if (max(abs(b22 - b12), abs(b22 - b21)) <= threshold) {
            brightnessSum += b22;
        } else {
//            printf("returned -1 at 22\n");
            return -1;
        }

        return brightnessSum / 9;
    }

    vector<vector<int> > createRegionAvgIntensitiesMat(vector<vector<int> >& mat, int threshold) {
        int rows = mat.size();
        int cols = mat[0].size();

        // create  a matrix with all elements initialized to -1
        vector<vector<int> > regionAvgIntensities(rows, vector<int>(cols, -1));

        for (int row = 1; row < rows - 1; row++) {
            for (int col = 1; col < cols - 1; col++) {
                regionAvgIntensities[row][col] = calcRegionAvgIntensity(mat, threshold, row, col);
            }
        }

        return regionAvgIntensities;
    }

public:
    friend class SolutionTest;

    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
//        showMat(image, "image");
        vector<vector<int> > regionAvgIntensities = createRegionAvgIntensitiesMat(image, threshold);
//        showMat(regionAvgIntensities, "regionAvgIntensities");

        int rows = image.size();
        int cols = image[0].size();

        vector<vector<int> > imageToReturn = image;

        // [0,0] corner pixel
        imageToReturn[0][0] = (regionAvgIntensities[1][1] != -1) ? regionAvgIntensities[1][1] : imageToReturn[0][0];
        // [0,cols - 1] corner pixel
        imageToReturn[0][cols - 1] = (regionAvgIntensities[1][cols - 2] != -1) ? regionAvgIntensities[1][cols - 2] : imageToReturn[0][cols - 1];
        // [rows - 1,0] corner pixel
        imageToReturn[rows - 1][0] = (regionAvgIntensities[rows - 2][1] != -1) ? regionAvgIntensities[rows - 2][1] : imageToReturn[rows - 1][0];
        // [rows - 1,cols-1] corner pixel
        imageToReturn[rows - 1][cols - 1] = (regionAvgIntensities[rows - 2][cols - 2] != -1) ? regionAvgIntensities[rows - 2][cols - 2] : imageToReturn[rows - 1][cols - 1];

        // top edge pixels
        for (int col = 1; col < cols - 1; col++) {
            int regionAvgIntensitiesSum = 0;
            int numRegions = 0;

            if (regionAvgIntensities[1][col - 1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[1][col - 1];
                numRegions++;
            }
            if (regionAvgIntensities[1][col] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[1][col];
                numRegions++;
            }
            if (regionAvgIntensities[1][col + 1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[1][col + 1];
                numRegions++;
            }

            imageToReturn[0][col] = (numRegions > 0) ? (regionAvgIntensitiesSum / numRegions) : imageToReturn[0][col];
        }

        // left edge pixels
        for (int row = 1; row < rows - 1; row++) {
            int regionAvgIntensitiesSum = 0;
            int numRegions = 0;

            if (regionAvgIntensities[row - 1][1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[row - 1][1];
                numRegions++;
            }
            if (regionAvgIntensities[row][1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[row][1];
                numRegions++;
            }
            if (regionAvgIntensities[row + 1][1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[row + 1][1];
                numRegions++;
            }

            imageToReturn[row][0] = (numRegions > 0) ? (regionAvgIntensitiesSum / numRegions) : imageToReturn[row][0];
        }

        // right edge pixels
        for (int row = 1; row < rows - 1; row++) {
            int regionAvgIntensitiesSum = 0;
            int numRegions = 0;

            if (regionAvgIntensities[row - 1][cols - 2] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[row - 1][cols - 2];
                numRegions++;
            }
            if (regionAvgIntensities[row][cols - 2] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[row][cols - 2];
                numRegions++;
            }
            if (regionAvgIntensities[row + 1][cols - 2] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[row + 1][cols - 2];
                numRegions++;
            }

            imageToReturn[row][cols - 1] = (numRegions > 0) ? (regionAvgIntensitiesSum / numRegions) : imageToReturn[row][cols - 1];
        }

        // bottom row pixels
//        printf("going to execute computation for bottom row\n");
        for (int col = 1; col < cols - 1; col++) {
            int regionAvgIntensitiesSum = 0;
            int numRegions = 0;

//            printf("came here 1\n");
            if (regionAvgIntensities[rows - 2][col - 1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[rows - 2][col - 1];
                numRegions++;
            }
//            printf("came here 2\n");
            if (regionAvgIntensities[rows - 2][col] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[rows - 2][col];
                numRegions++;
            }
//            printf("came here 3\n");
            if (regionAvgIntensities[rows - 2][col + 1] != -1) {
                regionAvgIntensitiesSum += regionAvgIntensities[rows - 2][col + 1];
                numRegions++;
            }
//            printf("at [lastRow][%d], regionAvgIntensitiesSum=%d, numRegions=%d\n", col, regionAvgIntensitiesSum, numRegions);

            imageToReturn[rows - 1][col] = (numRegions > 0) ? (regionAvgIntensitiesSum / numRegions) : imageToReturn[rows - 1][col];
        }

        // central region pixels
        for (int row = 1; row < rows - 1; row++) {
            for (int col = 1; col < cols - 1; col++) {
                int regionAvgIntensitiesSum = 0;
                int numRegions = 0;

                for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
                    for (int colOffset = -1; colOffset <= 1; colOffset++) {
                        if (regionAvgIntensities[row + rowOffset][col + colOffset] != -1) {
                            regionAvgIntensitiesSum += regionAvgIntensities[row + rowOffset][col + colOffset];
                            numRegions++;
                        }
                    }
                }

                imageToReturn[row][col] = (numRegions > 0) ? (regionAvgIntensitiesSum / numRegions) : imageToReturn[row][col];
            }
        }

        return imageToReturn;
    }
};

class SolutionTest {
public:
    void testResultGrid() {
        Solution soln = Solution();
        vector<vector<int> > image;
        int threshold;
        vector<vector<int> > expected, computed;

        image = {{5,  6,  7,  10},
                 {8,  9,  10, 10},
                 {11, 12, 13, 10}};
        threshold = 3;
        expected = {{9, 9, 9, 9},
                    {9, 9, 9, 9},
                    {9, 9, 9, 9}};
//        computed = soln.resultGrid(image, threshold);
//        assert(expected == computed);

        image = {{10, 20, 30},
                 {15, 25, 35},
                 {20, 30, 40},
                 {25, 35, 45}};
        threshold = 12;
        expected = {{25, 25, 25},
                    {27, 27, 27},
                    {27, 27, 27},
                    {30, 30, 30}};
        computed = soln.resultGrid(image, threshold);
//        soln.showMat(computed, "computed");
        assert(expected == computed);

        image = {{5,  6,  7},
                 {8,  9,  10},
                 {11, 12, 13}};
        threshold = 1;
        expected = {{5,  6,  7},
                    {8,  9,  10},
                    {11, 12, 13}};
        computed = soln.resultGrid(image, threshold);
//        soln.showMat(computed, "computed");
        assert(expected == computed);

        printf("[testResultGrid] All test-cases passed\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testResultGrid();

    return 0;
}
