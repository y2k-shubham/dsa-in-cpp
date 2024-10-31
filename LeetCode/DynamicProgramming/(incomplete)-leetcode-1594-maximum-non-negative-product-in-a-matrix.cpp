// LeetCode-1594: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/
// (incomplete)

#include <vector>
#include <cassert>
#include <utility>
#include <climits>

using namespace std;

class Solution {
private:
    vector<vector<pair<int, int> > > createMemoMat(vector<vector<int> >& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        vector<vector<pair<int, int> > > memoMat(rows, vector<pair<int, int> >(cols, {0, 0}));
        return memoMat;
    }

    void fillMemoMat(vector<vector<int> >& mat, vector<vector<pair<int, int> > >& memoMat) {
        memoMat[0][0] = {mat[0][0], mat[0][0]};

        // fill first row
        for (int j = 1; j < mat[0].size(); j++) {
            int crrEle = mat[0][j];

            int prod1 = crrEle * memoMat[0][j - 1].first;
            int prod2 = crrEle * memoMat[0][j - 1].second;

            int prodBigger = max(prod1, prod2);
            int prodSmaller = min(prod1, prod2);

            if ((prodBigger >= 0) && (prodSmaller <= 0)) {
                memoMat[0][j] = {prodBigger, prodSmaller};
            } else {
                memoMat[0][j] = {prodBigger, prodBigger};
            }
        }
    }

public:
    int maxProductPath(vector<vector<int>>& grid) {

    }
};
