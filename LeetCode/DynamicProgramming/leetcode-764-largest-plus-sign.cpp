// LeetCode-764: https://leetcode.com/problems/largest-plus-sign/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class CDirs {
   public:
    int left;
    int right;
    int up;
    int down;
};

class Solution {
   public:
    vector<vector<int>> createMat(int N) {
        vector<vector<int>> mat(N);
        for (int i = 0; i < N; i++) {
            vector<int> matRow(N, 1);
            mat[i] = matRow;
        }
        return mat;
    }

    void fillMat(int N, vector<vector<int>>& mines, vector<vector<int>>& mat) {
        for (int i = 0; i < mines.size(); i++) {
            mat[mines[i][0]][mines[i][1]] = 0;
        }
    }

    vector<vector<CDirs>> createMemoMat(int N) {
        vector<vector<CDirs>> memoMat(N);

        for (int i = 0; i < N; i++) {
            vector<CDirs> memoMatRow(N);
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    void fillMatLeft(int N, vector<vector<int>>& mat, vector<vector<CDirs>>& memoMat) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (mat[i][j] == 0) {
                    memoMat[i][j].left = 0;
                } else {
                    if (j == 0) {
                        memoMat[i][j].left = 1;
                    } else {
                        memoMat[i][j].left = memoMat[i][j - 1].left + 1;
                    }
                }
            }
        }
    }

    void fillMatRight(int N, vector<vector<int>>& mat, vector<vector<CDirs>>& memoMat) {
        for (int i = 0; i < N; i++) {
            for (int j = N - 1; j >= 0; j--) {
                if (mat[i][j] == 0) {
                    memoMat[i][j].right = 0;
                } else {
                    if (j == N - 1) {
                        memoMat[i][j].right = 1;
                    } else {
                        memoMat[i][j].right = memoMat[i][j + 1].right + 1;
                    }
                }
            }
        }
    }

    void fillMatDown(int N, vector<vector<int>>& mat, vector<vector<CDirs>>& memoMat) {
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                if (mat[i][j] == 0) {
                    memoMat[i][j].down = 0;
                } else {
                    if (i == 0) {
                        memoMat[i][j].down = 1;
                    } else {
                        memoMat[i][j].down = memoMat[i - 1][j].down + 1;
                    }
                }
            }
        }
    }

    void fillMatUp(int N, vector<vector<int>>& mat, vector<vector<CDirs>>& memoMat) {
        for (int j = 0; j < N; j++) {
            for (int i = N - 1; i >= 0; i--) {
                if (mat[i][j] == 0) {
                    memoMat[i][j].up = 0;
                } else {
                    if (i == N - 1) {
                        memoMat[i][j].up = 1;
                    } else {
                        memoMat[i][j].up = memoMat[i + 1][j].up + 1;
                    }
                }
            }
        }
    }

    int searchLargestPlus(int N, vector<vector<CDirs>>& memoMat) {
        int largestPlusSize = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int minLen = min(min(memoMat[i][j].left, memoMat[i][j].right), min(memoMat[i][j].up, memoMat[i][j].down));
                largestPlusSize = max(largestPlusSize, minLen);
            }
        }

        return largestPlusSize;
    }

    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>> mat = createMat(N);
        fillMat(N, mines, mat);

        vector<vector<CDirs>> memoMat = createMemoMat(N);

        fillMatLeft(N, mat, memoMat);
        fillMatRight(N, mat, memoMat);
        fillMatUp(N, mat, memoMat);
        fillMatDown(N, mat, memoMat);

        return searchLargestPlus(N, memoMat);
    }
};
