// LeetCode-531: https://leetcode.com/problems/lonely-pixel-i/

#include <vector>
#include <cstdio>

using namespace std;

#define BLACK_PIXEL 'B'

class Solution {
private:
    void showVec(vector <int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");
    }

    vector <int> createNumBlackPixelsPerRowVec(vector<vector<char>>& picture) {
        int numRows = picture.size();
        int numCols = picture[0].size();

        vector <int> numBlackPixelsVec(numRows, 0);

        for (int i = 0; i < numRows; i++) {

            int numBlackPixels = 0;
            for (int j = 0; j < numCols; j++) {
                if (picture[i][j] == BLACK_PIXEL) {
                    numBlackPixels++;
                }
            }

            numBlackPixelsVec[i] = numBlackPixels;
        }

        return numBlackPixelsVec;
    }

    vector <int> createNumBlackPixelsPerColVec(vector<vector<char>>& picture) {
        int numRows = picture.size();
        int numCols = picture[0].size();

        vector <int> numBlackPixelsVec(numCols, 0);

        for (int j = 0; j < numCols; j++) {

            int numBlackPixels = 0;
            for (int i = 0; i < numRows; i++) {
                if (picture[i][j] == BLACK_PIXEL) {
                    numBlackPixels++;
                }
            }

            numBlackPixelsVec[j] = numBlackPixels;
        }

        return numBlackPixelsVec;
    }

    int calcNumLonelyPixels(
        vector<vector<char>>& picture,
        vector<int>& numBlackPixelsPerRow,
        vector<int>& numBlackPixelsPerCol) {
        int numRows = picture.size();
        int numCols = picture[0].size();

        int numLonelyPixels = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if ((picture[i][j] == BLACK_PIXEL) && (numBlackPixelsPerRow[i] == 1) && (numBlackPixelsPerCol[j] == 1)) {
                    ++numLonelyPixels;
                }
            }
        }

        return numLonelyPixels;
    }

public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        vector <int> numBlackPixelsPerRow = createNumBlackPixelsPerRowVec(picture);
        vector <int> numBlackPixelsPerCol = createNumBlackPixelsPerColVec(picture);

        return calcNumLonelyPixels(picture, numBlackPixelsPerRow, numBlackPixelsPerCol);
    }
};
