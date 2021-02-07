// LeetCode-312: https://leetcode.com/problems/burst-balloons/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void showVec(vector<int>& vec) {
    int len = (int)vec.size();

    cout << endl;
    for (int j = 0; j < len; j++) {
        printf("[%d]\t", j);
    }
    cout << endl;

    for (int j = 0; j < len; j++) {
        printf("%d\t", vec[j]);
    }
    cout << endl;
}

void showMatUpperTriangle(vector<vector<int> >& mat, vector<int>& balloons) {
    cout << endl;
    int len = (int)balloons.size();

    cout << "\t\t";
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    cout << "\t\t";
    for (int i = 0; i < len; i++) {
        printf("%d\t", balloons[i]);
    }
    cout << endl;

    for (int i = 0; i < len; i++) {
        printf("[%d]\t%d\t", i, balloons[i]);
        for (int j = 0; j < len; j++) {
            if (j < i) {
                printf("\t");
            } else {
                printf("%d\t", mat[i][j]);
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
        if (debug) {
            showVec(nums);
        }

        vector<vector<int> > memoMat(len);

        for (int i = 0; i < len; i++) {
            vector<int> memoRow(len);
            memoRow[i] = nums[i];
            memoMat[i] = memoRow;
        }

        if (debug) {
            showMatUpperTriangle(memoMat, nums);
        }

        int rLo = 0;
        int cHi = len - 1;
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
                    if (debug) {
                        printf("\nk = %d\n", k);
                    }

                    int lMult = 1;
                    int rMult = 1;
                    if (k == rBegin) {
                        if (debug) {
                            printf("\nk is at begin, updating just rMult to %d\n", nums[cEnd + 1]);
                        }
                        rMult = nums[cEnd + 1];
                    } else if (k == cEnd) {
                        if (debug) {
                            printf("\nk is at   end, updating just lMult to %d\n", nums[rBegin - 1]);
                        }
                        lMult = nums[rBegin - 1];
                    } else {
                        if (debug) {
                            printf("\nk is in betwe, updating lMult to %d and rMult to %d\n", nums[rBegin - 1], nums[cEnd + 1]);
                        }
                        lMult = nums[rBegin - 1];
                        rMult = nums[cEnd + 1];
                    }
                    int prod = lMult * nums[k] * rMult;

                    int lSum = 0;
                    if (k > 0) {
                        lSum = memoMat[rBegin][k - 1]; 
                    }
                    int rSum = 0;
                    if (k == len - 1) {
                        rSum = memoMat[k + 1][cEnd];
                    }
                    int crrCoins = lSum + prod + rSum;
                    maxCoins = max(maxCoins, crrCoins);
                    if (debug) {
                        printf("for k=%d, %d + (%d x %d x %d) + %d = %d\n", k, lSum, lMult, nums[k], rMult, rSum, crrCoins);
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

        return memoMat[0][len - 1];
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
