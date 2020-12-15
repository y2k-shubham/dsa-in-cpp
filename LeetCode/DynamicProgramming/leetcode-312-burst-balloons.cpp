// LeetCode-312: https://leetcode.com/problems/burst-balloons/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void showVec(vector<int>& vec) {
    int len = ((int)vec.size()) - 2;

    cout << endl;
    for (int j = -1; j <= len; j++) {
        printf("[%d]\t", j);
    }
    cout << endl;

    for (int j = -1; j <= len; j++) {
        printf("%d\t", vec[j + 1]);
    }
    cout << endl;
}

void showMatUpperTriangle(vector<vector<int> >& mat, vector<int>& balloons) {
    cout << endl;
    int len = ((int)balloons.size()) - 2;

    cout << "\t\t";
    for (int i = -1; i <= len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "\t\t";
    for (int i = -1; i <= len; i++) {
        printf("%d\t", balloons[i + 1]);
    }
    cout << endl;

    for (int i = -1; i <= len; i++) {
        printf("[%d]\t%d\t", i, (balloons[i + 1]));
        for (int j = -1; j <= len; j++) {
            if (j < i) {
                printf("\t");
            } else {
                printf("%d\t", mat[i + 1][j + 1]);
            }
        }
        cout << endl;
    }
    cout << endl;
}

int maxCoinsDebug(vector<int>& nums, bool debug) {
    int len = nums.size();

    if (len == 0) {
        return 0;
    } else if (len == 1) {
        return nums[0];
    } else {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        if (debug) {
            showVec(nums);
        }

        vector<vector<int> > memoMat(len + 2);

        for (int i = -1; i <= len; i++) {
            vector<int> memoRow(len + 2);
            if ((-1 < i) && (i < len)) {
                memoRow[i + 1] = nums[i + 1];
            }
            memoMat[i + 1] = memoRow;
        }

        if (debug) {
            showMatUpperTriangle(memoMat, nums);
        }

        int rLo = 1;
        int cHi = len;
        for (int l = 2; l <= len; l++) {
            int rBegin = rLo;
            int cEnd = rBegin + l - 1;

            if (debug) {
                printf("\n===========\n");
                printf("\ncomputing diag for l=%d\n", l);
            }
            while (cEnd <= cHi) {
                if (debug) {
                    printf("\n------------\n");
                    printf("rBegin=%d, cEnd=%d\n", rBegin, cEnd);
                }

                int maxCoins = INT_MIN;
                for (int k = rBegin; k <= cEnd; k++) {
                    int crrCoins = memoMat[rBegin][k - 1] + (nums[rBegin - 1] * nums[k] * nums[cEnd + 1]) + memoMat[k + 1][cEnd];
                    maxCoins = max(maxCoins, crrCoins);
                    if (debug) {
                        printf("\nfor k=%d, %d + (%d x %d x %d) + %d = %d\n", k, memoMat[rBegin][k - 1], nums[rBegin - 1], nums[k], nums[cEnd + 1], memoMat[k + 1][cEnd], crrCoins);
                        printf("for k=%d, crrCoins=%d & maxCoins=%d\n", k, crrCoins, maxCoins);
                    }
                }
                memoMat[rBegin][cEnd] = maxCoins;

                if (debug) {
                    showMatUpperTriangle(memoMat, nums);
                }

                rBegin++;
                cEnd++;
            }
        }

        if (debug) {
            showMatUpperTriangle(memoMat, nums);
        }

        return memoMat[1][len];
    }
}

void testMaxCoinsDebug() {
    vector<int> balloons;

    balloons = {3, 1, 5, 8};
    assert(167 == maxCoinsDebug(balloons, true));
}

int main() {
    testMaxCoinsDebug();

    return 0;
}
