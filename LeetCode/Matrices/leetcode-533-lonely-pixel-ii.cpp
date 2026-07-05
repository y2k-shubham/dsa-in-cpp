// LeetCode-533: https://leetcode.com/problems/lonely-pixel-ii/

#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

#define BLACK_PIXEL 'B'

class Solution {
private:
    pair <vector <int>, vector <string> > createRowWiseTraversalStructures(vector<vector<char>>& picture) {
        int numRows = picture.size();
        int numCols = picture[0].size();

        vector <int> numBlackPixelsVec(numRows, 0);
        vector<string> stringifiedRowsVec(numRows);

        for (int i = 0; i < numRows; i++) {

            int numBlackPixels = 0;
            for (int j = 0; j < numCols; j++) {
                if (picture[i][j] == BLACK_PIXEL) {
                    numBlackPixels++;
                }
            }

            numBlackPixelsVec[i] = numBlackPixels;

            string stringifiedRow(picture[i].begin(), picture[i].end());
            stringifiedRowsVec[i] = stringifiedRow;
        }

        return {numBlackPixelsVec, stringifiedRowsVec};
    }

    pair <vector <int>, vector<unordered_set <int>>> createColWiseTraversalStructures(vector<vector<char>>& picture) {
        int numRows = picture.size();
        int numCols = picture[0].size();

        vector <int> numBlackPixelsVec(numCols, 0);
        vector<unordered_set<int>> rowsHavingBlackPixelsPerCol(numCols);

        for (int j = 0; j < numCols; j++) {

            int numBlackPixels = 0;
            unordered_set <int> rowsHavingBlackPixels;
            for (int i = 0; i < numRows; i++) {
                if (picture[i][j] == BLACK_PIXEL) {
                    numBlackPixels++;
                    rowsHavingBlackPixels.insert(i);
                }
            }

            numBlackPixelsVec[j] = numBlackPixels;
            rowsHavingBlackPixelsPerCol[j] = rowsHavingBlackPixels;
        }

        return {numBlackPixelsVec, rowsHavingBlackPixelsPerCol};
    }

    bool areIdenticalRows(vector<string>& stringifiedRowsVec, unordered_set<int>& rows) {
        int numRows = rows.size();
        if (numRows <= 1) {
            return true;
        }

        string stringifiedRow = stringifiedRowsVec[*rows.begin()];
        for (auto it = rows.begin(); it != rows.end(); ++it) {
            if (stringifiedRowsVec[(*it)] != stringifiedRow) {
                return false;
            }
        }

        return true;
    }

    int countLonelyPixels(
        vector<vector<char>>& picture,
        int target,
        vector <int>& numBlackPixelsPerRowVec,
        vector<int>& numBlackPixelsPerColVec,
        vector<string>& stringifiedRowsVec,
        vector<unordered_set<int>>& rowsHavingBlackPixelsPerCol) {
        int numRows = picture.size();
        int numCols = picture[0].size();

        int numLonelyPixels = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                // pre-req: check if black pixel
                bool isBlackPixels = picture[i][j] == BLACK_PIXEL;
                if (!isBlackPixels) {
                    continue;
                }

                // cond-1: check if current row and column have target no of black pixels
                bool hasRequiredBlackPixelsCount = (numBlackPixelsPerRowVec[i] == target) && (numBlackPixelsPerColVec[j] == target);
                if (!hasRequiredBlackPixelsCount) {
                    continue;
                }

                // cond-2: check if all rows of current col having black pixels are identical
                unordered_set<int> rowsHavingBlackPixelsInCrrCol = rowsHavingBlackPixelsPerCol[j];
                if (!areIdenticalRows(stringifiedRowsVec, rowsHavingBlackPixelsInCrrCol)) {
                    continue;
                }

                numLonelyPixels++;
            }
        }

        return numLonelyPixels;
    }

public:
    int findBlackPixel(vector<vector<char>>& picture, int target) {
        pair <vector <int>, vector <string> > rowWiseTraversalStructures = createRowWiseTraversalStructures(picture);
        vector <int> numBlackPixelsPerRowVec = rowWiseTraversalStructures.first;
        vector<string> stringifiedRowsVec = rowWiseTraversalStructures.second;

        pair <vector <int>, vector<unordered_set <int>>> colWiseTraversalStructures = createColWiseTraversalStructures(picture);
        vector<int> numBlackPixelsPerColVec = colWiseTraversalStructures.first;
        vector<unordered_set<int>> rowsHavingBlackPixelsPerCol = colWiseTraversalStructures.second;

        return countLonelyPixels(
            picture,
            target,
            numBlackPixelsPerRowVec,
            numBlackPixelsPerColVec,
            stringifiedRowsVec,
            rowsHavingBlackPixelsPerCol);
    }
};
