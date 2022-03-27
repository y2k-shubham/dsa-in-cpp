// LeetCode-1337: https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/
// quite dumb problem; insist skipping

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
private:
    int count1sInRow(vector<vector<int>> &mat, int row) {
        int numCols = mat[row].size();

        for (int j = 0; j < numCols; j++) {
            if (mat[row][j] == 0) {
                return j;
            }
        }

        return numCols;
    }

    vector<pair<int, int> > buildRowStrengthVec(vector<vector<int>> &mat) {
        int numRows = mat.size();
        vector<pair<int, int> > rowStrengthVec(numRows);

        for (int i = 0; i < numRows; i++) {
            int num1s = count1sInRow(mat, i);
            rowStrengthVec[i] = {num1s, i};
        }

        return rowStrengthVec;
    }

    vector<int> extractFirstKRowNums(
            vector<pair<int, int> > &rowStrengthVec,
            int k
    ) {
        vector<int> vec(k);

        for (int i = 0; i < k; i++) {
            vec[i] = rowStrengthVec[i].second;
        }

        return vec;
    }

public:
    vector<int> kWeakestRows(vector<vector<int>> &mat, int k) {
        vector<pair<int, int> > rowStrengthVec = buildRowStrengthVec(mat);
        sort(rowStrengthVec.begin(), rowStrengthVec.end());

        vector<int> kWeakestRowIdxs = extractFirstKRowNums(rowStrengthVec, k);
        return kWeakestRowIdxs;
    }
};

