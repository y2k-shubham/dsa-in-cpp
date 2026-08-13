// LeetCode-251: https://leetcode.com/problems/flatten-2d-vector/
// Premium
// Companies: [Airbnb]
// incomplete

#include <vector>

using namespace std;

class Vector2D {
private:
    vector<vector<int>> mat;
    int numRows;
    int crrRowNumCols;
    int crrRow;
    int crrCol;

    void movePtrsToNextValidElement() {
        if (crrRow >= numRows) {
            return;
        }

        // do {
        //     crrCol++;
        //     if (crrCol >= crrRowNumCols) {
        //         crrRow++;
        //         if (crrRow < numRows) {
        //             crrRowNumCols = mat[crrRow].size();
        //         } else {
        //             // finished
        //         }
        //
        //         crrCol = 0;
        //     }
        // } while ((crrRow < numRows) || (crrCol < crrRowNumCols));
    }

public:
    Vector2D(vector<vector<int>>& vec) {
        mat = vec;
        numRows = vec.size();
        if (numRows > 0) {
            crrRowNumCols = vec[0].size();
        }

        crrRow = 0;
        crrCol = -1;

        movePtrsToNextValidElement();
    }

    int next() {
        int crrVal = mat[crrRow][crrCol];

        movePtrsToNextValidElement();

        return crrVal;
    }

    bool hasNext() {
        return (crrRow < numRows) && (crrCol < crrRowNumCols);
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
