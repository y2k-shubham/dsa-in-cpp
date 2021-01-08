// Wrong Code (couldn't understand the correct implementation)
// best visual explaination: https://www.youtube.com/watch?v=x1ehCsZI1jU

#include <climits>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int numBooks = books.size();

        vector<int> minHeights(numBooks + 1, INT_MAX);
        minHeights[0] = 0;
        minHeights[1] = books[0][1];

        pair<int, int> crrLvlDim = {books[0][0], books[0][1]};
        for (int i = 2; i <= numBooks; i++) {
            pair<int, int> crrBookDim = {books[i - 1][0], books[i - 1][1]};

            // try to fit in current level
            if ((crrLvlDim.first + crrBookDim.first) <= shelfWidth) {
                crrLvlDim.first = crrLvlDim.first + crrBookDim.first;

                int heightWithoutCrrLvl = minHeights[i - 1] - crrLvlDim.second;
                crrLvlDim.second = max(crrLvlDim.second, crrBookDim.second);

                int heightWithCrrLvl = heightWithoutCrrLvl + crrLvlDim.second;
                minHeights[i] = heightWithCrrLvl;
            } else {
                pair<int, int> newLvlDim = crrBookDim;
                pair<int, int> newLvlBestDim = newLvlDim;
                int minHeight = minHeights[i - 1] + newLvlDim.second;
                int minHeightSplitInd = i - 1;

                int j = i - 1;
                pair<int, int> jthBookDim = {books[j - 1][0], books[j - 1][1]};
                while ((newLvlDim.first + jthBookDim.first) <= shelfWidth) {
                    newLvlDim.first = newLvlDim.first + jthBookDim.first;
                    newLvlDim.second = max(newLvlDim.second, jthBookDim.second);

                    int heightTillJMinus1Books = (j >= 1) ? minHeights[j - 1] : 0;
                    int heightIncludingNewLvl = heightTillJMinus1Books + newLvlDim.second;

                    if (heightIncludingNewLvl < minHeight) {
                        minHeight = heightIncludingNewLvl;
                        minHeightSplitInd = j;
                        newLvlBestDim = newLvlDim;
                    }

                    j--;
                    if (j == 0) {
                        break;
                    }
                    if (j >= 1) {
                        jthBookDim = {books[j - 1][0], books[j - 1][1]};
                    }
                }

                minHeights[i] = minHeight;
                crrLvlDim = newLvlBestDim;
            }
        }

        return minHeights[numBooks];
    }
};
