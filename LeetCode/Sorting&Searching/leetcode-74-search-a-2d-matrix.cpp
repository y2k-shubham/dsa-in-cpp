// LeetCode-74: https://leetcode.com/problems/search-a-2d-matrix/

#include <vector>

using namespace std;

class Solution {
private:
    int findPossibleRow(vector<vector<int> > &mat, int target, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midRowFirstEle = mat[mid][0];

        int numRows = mat.size();
        bool notPresentInHigherRows = (mid == (numRows - 1)) || ((mid < numRows) && (target < mat[mid + 1][0]));

        if (target < midRowFirstEle) {
            return findPossibleRow(mat, target, lo, mid - 1);
        } else if ((target == midRowFirstEle) || notPresentInHigherRows) {
            return mid;
        } else {
            return findPossibleRow(mat, target, mid + 1, hi);
        }
    }

    int binSearchEleInRow(vector<vector<int> > &mat, int row, int target, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midEle = mat[row][mid];

        if (target < midEle) {
            return binSearchEleInRow(mat, row, target, lo, mid - 1);
        } else if (target == midEle) {
            return mid;
        } else {
            return binSearchEleInRow(mat, row, target, mid + 1, hi);
        }
    }

public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int numRows = matrix.size();
        int numCols = matrix[0].size();

        int row = findPossibleRow(matrix, target, 0, numRows - 1);
        if (row < 0) {
            return false;
        }


        int col = binSearchEleInRow(matrix, row, target, 0, numCols - 1);
        return col >= 0;
    }
};

