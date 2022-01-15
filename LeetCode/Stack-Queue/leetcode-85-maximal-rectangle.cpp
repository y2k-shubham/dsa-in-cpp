// LeetCode-85: https://leetcode.com/problems/maximal-rectangle/
// solved using maximum area under histogram method

#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> createMat(int rows, int cols) {
        vector<vector<int>> mat(rows);

        for (int i = 0; i < rows; i++) {
            vector<int> matRow(cols);
            mat[i] = matRow;
        }

        return mat;
    }

    void fillSumMatRow(
        vector<vector<char>>& orgMat,
        int row,
        vector<vector<int>>& sumMat) {
        // fill up sumMat
        for (int j = 0; j < orgMat[0].size(); j++) {
            if (row == 0) {
                sumMat[0][j] = orgMat[0][j] - '0';
            } else {
                int orgVal = orgMat[row][j] - '0';
                sumMat[row][j] = (sumMat[row - 1][j] * orgVal) + orgVal;
            }
        }
    }

    void fillNleLeftIdxVec(
        int row,
        vector<vector<int>>& sumMat,
        vector<int>& nleLeftIdxVec) {
        stack<int> stk;

        for (int j = 0; j < sumMat[0].size(); j++) {
            int crrVal = sumMat[row][j];

            while (!stk.empty() && (sumMat[row][stk.top()] >= crrVal)) {
                stk.pop();
            }

            if (stk.empty()) {
                nleLeftIdxVec[j] = -1;
            } else {
                nleLeftIdxVec[j] = stk.top();
            }

            stk.push(j);
        }
    }

    void fillNleRightIdxVec(
        int row,
        vector<vector<int>>& sumMat,
        vector<int>& nleLeftIdxVec) {
        stack<int> stk;

        int cols = sumMat[0].size();
        for (int j = cols - 1; j >= 0; j--) {
            int crrVal = sumMat[row][j];

            while (!stk.empty() && (sumMat[row][stk.top()] >= crrVal)) {
                stk.pop();
            }

            if (stk.empty()) {
                nleLeftIdxVec[j] = cols;
            } else {
                nleLeftIdxVec[j] = stk.top();
            }

            stk.push(j);
        }
    }

    int findMaxAreaUnderHistForRow(
        int row,
        vector<vector<int>>& sumMat,
        vector<int>& nleLeftIdxVec,
        vector<int>& nleRightIdxVec) {
        int maxArea = 0;

        for (int j = 0; j < sumMat[0].size(); j++) {
            int crrVal = sumMat[row][j];
            int height = crrVal;

            int leftIdx = nleLeftIdxVec[j];
            int rightIdx = nleRightIdxVec[j];
            int width = rightIdx - leftIdx - 1;

            int crrArea = width * height;

            maxArea = max(maxArea, crrArea);
        }

        return maxArea;
    }

   public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        vector<vector<int>> sumMat = createMat(rows, cols);
        vector<int> nleLeftIdxVec(cols);
        vector<int> nleRightIdxVec(cols);

        int overallMaxAreaUnderHist = 0;
        for (int i = 0; i < rows; i++) {
            fillSumMatRow(matrix, i, sumMat);

            fillNleLeftIdxVec(i, sumMat, nleLeftIdxVec);
            fillNleRightIdxVec(i, sumMat, nleRightIdxVec);

            int crrMaxAreaUnderHist = findMaxAreaUnderHistForRow(
                i,
                sumMat,
                nleLeftIdxVec,
                nleRightIdxVec);
            overallMaxAreaUnderHist = max(overallMaxAreaUnderHist, crrMaxAreaUnderHist);
        }

        return overallMaxAreaUnderHist;
    }
};
