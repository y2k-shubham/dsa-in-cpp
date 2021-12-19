// LeetCode-73: https://leetcode.com/problems/set-matrix-zeroes/
// Not that easy really

#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   public:
    pair<set<int>, set<int>> findRCsToZero(vector<vector<int>>& matrix) {
        set<int> rows;
        set<int> cols;

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    rows.insert(i);
                    cols.insert(j);
                }
            }
        }

        return make_pair(rows, cols);
    }

    void setRCsToZero(vector<vector<int>>& matrix, pair<set<int>, set<int>> rcsToZero) {
        set<int> rows = rcsToZero.first;
        for (set<int>::iterator i = rows.begin(); i != rows.end(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[*i][j] = 0;
            }
        }

        set<int> cols = rcsToZero.second;
        for (set<int>::iterator j = cols.begin(); j != cols.end(); j++) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][*j] = 0;
            }
        }
    }

    void setZeroes(vector<vector<int>>& matrix) {
        pair<set<int>, set<int>> rcsToZero = findRCsToZero(matrix);
        setRCsToZero(matrix, rcsToZero);
    }
};
