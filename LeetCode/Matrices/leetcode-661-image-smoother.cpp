// LeetCode-661: https://leetcode.com/problems/image-smoother

#include <vector>
#include <climits>
#include <utility>
#include <cmath>

using namespace std;

class Solution {
private:
    vector<vector<int> > mat;
    int rows, cols;

    void init(vector<vector<int> >& img) {
        this->mat = img;
        this->rows = this->mat.size();
        this->cols = this->mat[0].size();
    }

    vector<vector<int> > createMat(int rows, int cols) {
        vector<vector<int> > mat(rows);

        for (int i = 0; i < rows; i++) {
            vector<int> matRow(cols, 0);
            mat[i] = matRow;
        }

        return mat;
    }

    inline pair<bool, bool> isCornerOrEdgeCell(int r, int c) {
        bool isFirstOrLastRow = (r == 0) || (r == this->rows - 1);
        bool isFirstOrLastCol = (c == 0) || (c == this->cols - 1);

        return {
                isFirstOrLastRow && isFirstOrLastCol,
                isFirstOrLastRow || isFirstOrLastCol
        };
    }

    inline int calcInternalCellSum(int r, int c) {
        int sum = 0;
        for (int i = r - 1; i <= r + 1; i++) {
            for (int j = c - 1; j <= c + 1; j++) {
                sum += this->mat[i][j];
            }
        }

        //printf("for internal cell [%d][%d], calculated sum = %d\n", r, c, sum);

        return sum;
    }

    inline int calcEdgeCellSum(int r, int c) {
        int sum = 0;
        for (int i = r - 1; i <= r + 1; i++) {
            for (int j = c - 1; j <= c + 1; j++) {
                if ((i >= 0) && (i < this->rows) && (j >= 0) && (j < this->cols)) {
                    sum += this->mat[i][j];
                }
            }
        }

        //printf("for corner or edge cell [%d][%d], calculated sum = %d\n", r, c, sum);

        return sum;
    }

    inline int calcAvg(int r, int c) {
        pair<bool, bool> isCornerOrEdgeCellFlags = isCornerOrEdgeCell(r, c);
        if (!isCornerOrEdgeCellFlags.first && !isCornerOrEdgeCellFlags.second) {
            return (int) floor(calcInternalCellSum(r, c) / 9.0f);
        }

        if (isCornerOrEdgeCellFlags.first) {
            float denom = (min(this->rows, this->cols) <= 1) ? 2.0f : 4.0f;
            return (int) floor(calcEdgeCellSum(r, c) / denom);
        } else if (isCornerOrEdgeCellFlags.second) {
            float denom = (min(this->rows, this->cols) <= 1) ? 3.0f : 6.0f;
            return (int) floor(calcEdgeCellSum(r, c) / denom);
        } else {
            return INT_MIN;
        }
    }

public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        init(img);
        if (max(this->rows, this->cols) == 1) {
            return img;
        }

        vector<vector<int> > avgMat = createMat(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                avgMat[i][j] = calcAvg(i, j);
            }
        }

        return avgMat;
    }
};
