// LeetCode-304: https://leetcode.com/problems/range-sum-query-2d-immutable/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3740/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
   private:
    vector<vector<int>> mat;
    vector<vector<int>> matSum;
    int rows;
    int cols;
    bool debug;

    void buildMatSum() {
        vector<vector<int>> matSum(this->rows);

        for (int i = 0; i < this->rows; i++) {
            vector<int> matRow(this->cols, 0);
            matSum[i] = matRow;
        }

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                int leftSum = (j > 0) ? matSum[i][j - 1] : 0;
                int topSum = (i > 0) ? matSum[i - 1][j] : 0;
                int diagSum = ((i > 0) && (j > 0)) ? matSum[i - 1][j - 1] : 0;

                matSum[i][j] = leftSum + topSum - diagSum + this->mat[i][j];
            }
        }

        this->matSum = matSum;
    }

    void showMat(vector<vector<int>>& mat, string name) {
        printf("\n%s matrix is:-\n", name.c_str());

        int rows = mat.size();
        int cols = mat[0].size();

        printf("Ind:\t");
        for (int j = 0; j < cols; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (int i = 0; i < rows; i++) {
            printf("[%d]\t", i);

            for (int j = 0; j < cols; j++) {
                printf("%d\t", mat[i][j]);
            }
            cout << endl;
        }
    }

   public:
    NumMatrix(vector<vector<int>>& matrix) {
        this->debug = false;

        this->mat = matrix;
        this->rows = matrix.size();
        this->cols = matrix[0].size();

        this->buildMatSum();

        if (this->debug) {
            this->showMat(this->mat, "mat");
            this->showMat(this->matSum, "matSum");
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int totalSum = this->matSum[row2][col2];
        int leftSum = (col1 > 0) ? this->matSum[row2][col1 - 1] : 0;
        int topSum = (row1 > 0) ? this->matSum[row1 - 1][col2] : 0;
        int diagSum = ((row1 > 0) && (col1 > 0)) ? this->matSum[row1 - 1][col1 - 1] : 0;

        return totalSum - leftSum - topSum + diagSum;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
