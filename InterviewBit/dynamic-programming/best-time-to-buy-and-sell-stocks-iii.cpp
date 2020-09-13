// https://www.interviewbit.com/problems/best-time-to-buy-and-sell-stocks-iii/
// https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-share-at-most-k-times/
// https://www.youtube.com/watch?v=oDhu5uGq_ic

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    return 0;
}

vector<vector<int> > createMat(int numTxn, int days) {
    int rows = numTxn + 1;
    // having extra column is actually redundant because in any case we leave the cells under
    // 1st column untouched (and initialized to 0)
    int cols = days + 1;

    vector<vector<int> > mat(rows);

    for (int i = 1; i <= rows; i++) {
        vector<int> rowVec(cols, 0);
        mat[i - 1] = rowVec;
    }

    return mat;
}

int maxProfit(const vector<int> &A) {
    int days = A.size();
    int k = 2;

    if (days < 2) {
        return 0;
    }

    // appending vectors https://stackoverflow.com/a/2551785/3679900
    vector<int> price(1);
    price.insert(price.end(), A.begin(), A.end());

    vector<vector<int> > mat = createMat(k, days);

    for (int i = 1; i <= k; i++) {
        int maxDiff = INT_MIN;

        // starting j from 2 is important, or we get wrong answer because of
        // incorrect initialization of maxDiff
        for (int j = 2; j <= days; j++) {
            maxDiff = max(maxDiff, mat[i - 1][j - 1] - price[j - 1]);

            if (j <= i) {
                mat[i][j] = mat[i - 1][j];
            } else {
                mat[i][j] = max(mat[i][j - 1], maxDiff + price[j]);
            }
        }
    }

    return mat[k][days];
}
