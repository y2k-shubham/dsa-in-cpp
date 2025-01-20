// LeetCode-2133: https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/description/

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
private:
    vector <int> readColumn(vector<vector<int>>& matrix, int colIdx) {
        int numRows = matrix.size();
        vector <int> columnVec(numRows);

        for (int i = 0; i < numRows; i++) {
            columnVec[i] = matrix[i][colIdx];
        }

        return columnVec;
    }

    bool hasAllValuesFrom1toN(vector <int>& valueVec, int n) {
        if (valueVec.size() != n) {
            return false;
        }

        unordered_set<int> valueSet;
        for (int value: valueVec) {
            if ((value < 1) || (n < value)) {
                return false;
            }

            // here we can also check if valueSet already contains value
            // to detect duplicates and do an early return

            valueSet.insert(value);
        }

        return valueSet.size() == n;
    }

    bool hasAllValuesFrom1toNInAllRows(vector<vector<int>>& matrix, int n) {
        for (int i = 0; i < matrix.size(); i++) {
            if (!hasAllValuesFrom1toN(matrix[i], n)) {
                return false;
            }
        }

        return true;
    }

    bool hasAllValuesFrom1toNInAllColumns(vector<vector<int>>& matrix, int n) {
        for (int i = 0; i < matrix.size(); i++) {
            vector <int> columnVec = readColumn(matrix, i);

            if (!hasAllValuesFrom1toN(columnVec, n)) {
                return false;
            }
        }

        return true;
    }

public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size();

        return hasAllValuesFrom1toNInAllRows(matrix, n)
            && hasAllValuesFrom1toNInAllColumns(matrix, n);
    }
};
