// LeetCode-2545: https://leetcode.com/problems/sort-the-students-by-their-kth-score/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector <pair <int, int>> getKthColValues(vector <vector <int>>& matrix, int k) {
        int numRows = matrix.size();
        vector <pair <int, int>> kthColValues(numRows);

        for (int i = 0; i < numRows; i++) {
            kthColValues[i] = {matrix[i][k], i};
        }

        return kthColValues;
    }

public:
    vector <vector <int>> sortTheStudents(vector <vector <int>>& score, int k) {
        int numRows = score.size();
        if (numRows <= 1) {
            return score;
        }

        vector <pair <int, int>> kthColValues = getKthColValues(score, k);
        sort(kthColValues.begin(), kthColValues.end(), greater <>());

        vector <vector <int>> scoresSortedByKthCol(numRows);
        for (int i = 0; i < numRows; i++) {
            int rowIdxToInsert = kthColValues[i].second;
            scoresSortedByKthCol[i] = score[rowIdxToInsert];
        }

        return scoresSortedByKthCol;
    }
};
