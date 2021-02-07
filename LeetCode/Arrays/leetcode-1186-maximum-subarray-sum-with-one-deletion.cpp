// LeetCode-1186: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/
// magic print stmt commenting

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void showVec(vector<int>& vec, int ind) {
    printf("\nInd:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }

    printf("\nVal:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }

    printf("\n\t");
    for (int i = 0; i < vec.size(); i++) {
        if (i == ind) {
            printf("^\t");
        } else {
            printf("\t");
        }
    }
    cout << endl;
}

bool allNonPositive(vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > 0) {
            return false;
        }
    }
    return true;
}

int findMaxEle(vector<int>& vec) {
    int maxEle = INT_MIN;
    for (int i = 0; i < vec.size(); i++) {
        maxEle = max(maxEle, vec[i]);
    }
    return maxEle;
}

////////
// wrong
////////

int findMaxSum(vector<int>& arr, bool debug) {
    int maxSum = 0;

    int crrMinNeg = 0;
    int crrSum = 0;
    for (int i = 0; i < arr.size(); i++) {
        int crrEle = arr[i];
        if (debug) {
            printf("\n-----------\n");

            showVec(arr, i);

            printf("\nat arr[%d] = %d\n", i, crrEle);
            printf("org crrSum = %d, new crrSum = %d\n", crrSum, (crrSum + crrEle));
        }
        crrSum = crrSum + crrEle;

        if ((crrEle < 0) && (crrEle < crrMinNeg)) {
            if (debug) {
                int crrSumCopy = crrSum;

                printf("\ncrrEle = %d is less than crrMinNeg = %d\n", crrEle, crrMinNeg);
                printf("so crrMinNeg = %d wont be deleted, hence crrSum = crrSum=%d - abs(crrMinNeg)=%d = %d\n", crrMinNeg, crrSumCopy, abs(crrMinNeg), (crrSumCopy - abs(crrMinNeg)));
                crrSumCopy = crrSumCopy - abs(crrMinNeg);
                printf("now crrEle = %d will be deleted, hence crrSum = crrSum=%d + abs(crrEle)=%d = %d\n", crrEle, crrSumCopy, abs(crrEle), (crrSumCopy + abs(crrEle)));
                crrSumCopy = crrSumCopy + abs(crrEle);
                printf("and of course, crrMinNeg = crrEle = %d\n", crrEle);
            }
            crrSum = crrSum - abs(crrMinNeg);
            crrSum = crrSum + abs(crrEle);
            crrMinNeg = crrEle;
        }

        // equality is essential in following if-expression,
        // because otherwise crrMinNeg wont be reset to 0 (when it should have)
        // (for more details, check 4th test-case in debug mode)
        if (crrSum <= 0) {
            if (debug) {
                printf("\nsince crrSum=%d < 0, we reset crrSum = 0 & crrMinNeg = 0\n", crrSum);
            }
            crrSum = 0;
            crrMinNeg = 0;
        } else {
            if (debug) {
                if (crrSum > maxSum) {
                    printf("\nupdating maxSum = crrSum = %d\n", crrSum);
                } else {
                    printf("\nunchanged maxSum = %d\n", maxSum);
                }
            }
            maxSum = max(maxSum, crrSum);
        }
    }

    if (debug) {
        printf("\n-----------\n");
        printf("\nreturning maxSum = %d\n", maxSum);
    }
    return maxSum;
}

// check 4th test case to understand why this is wrong
int maximumSumWrongDebug(vector<int>& arr, bool debug) {
    if (allNonPositive(arr)) {
        int maxEle = findMaxEle(arr);
        if (debug) {
            printf("no positive numbers, returning maxEle = %d\n", maxEle);
        }
        return maxEle;
    } else {
        return findMaxSum(arr, debug);
    }
}

void testMaximumSumWrongDebug() {
    vector<int> arr;

    arr = {1, -2, 0, 3};
    assert(maximumSumWrongDebug(arr, false) == 4);

    arr = {1, -2, -2, 3};
    assert(maximumSumWrongDebug(arr, false) == 3);

    arr = {-1, -1, -1, -1};
    assert(maximumSumWrongDebug(arr, false) == -1);

    arr = {1, -4, -5, -2, 5, 0, -1, 2};
    assert(maximumSumWrongDebug(arr, false) == 7);

    arr = {11, -10, -11, 8, 7, -6, 9, 4, 11, 6, 5, 0};
    assert(maximumSumWrongDebug(arr, true) == 50);
}

////////
// correct
////////

vector<int> createMaxEndingHereLeft(vector<int>& vec) {
    int len = vec.size();
    vector<int> mehLeft(len, 0);

    int maxSoFar = INT_MIN;

    int maxEndingHere = 0;
    for (int i = 0; i < len; i++) {
        int crrEle = vec[i];
        // printf("\n1. maxEndingHere = %d\n", maxEndingHere);
        int maxEndingHere = maxEndingHere + crrEle;
        // printf("vec[i] = %d\n", vec[i]);
        // printf("2. maxEndingHere = %d\n", maxEndingHere);
        if (maxEndingHere < crrEle) {
            maxEndingHere = crrEle;
        }
        // printf("3. maxEndingHere = %d\n", maxEndingHere);

        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
        }

        // printf("4. maxEndingHere = %d\n\n", maxEndingHere);
        mehLeft[i] = maxEndingHere;
    }

    return mehLeft;
}

vector<int> createMaxEndingHereRight(vector<int>& vec) {
    int len = vec.size();
    vector<int> mehRight(len, 0);

    int maxSoFar = INT_MIN;

    int maxEndingHere = 0;
    for (int i = len - 1; i >= 0; i--) {
        int crrEle = vec[i];

        // comment out this statement and then see the magic
        printf("");
        // printf("\n1. maxEndingHere = %d\n", maxEndingHere);
        int maxEndingHere = maxEndingHere + crrEle;
        if (maxEndingHere < crrEle) {
            maxEndingHere = crrEle;
        }

        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
        }

        mehRight[i] = maxEndingHere;
    }

    return mehRight;
}

int findMaxSumWithOneDel(vector<int>& vec, vector<int>& mehLeft, vector<int>& mehRight, bool debug) {
    int len = vec.size();
    int maxSum = INT_MIN;

    for (int i = 0; i < len; i++) {
        int maxSumOneDelIncludingCrrEle = 0;

        if (debug) {
            printf("\n\nat vec[%d] = %d\n", i, vec[i]);
        }

        if (i == 0) {
            maxSumOneDelIncludingCrrEle = max(vec[1], 0);
        } else if (i == len - 1 && len >= 2) {
            maxSumOneDelIncludingCrrEle = max(vec[len - 2], 0);
        } else {
            maxSumOneDelIncludingCrrEle = max(vec[i - 1], 0) + max(vec[i + 1], 0);
        }

        if (debug) {
            printf("sumIncCrr = %d + %d = %d\n", maxSumOneDelIncludingCrrEle, vec[i], (maxSumOneDelIncludingCrrEle + vec[i]));
        }
        maxSumOneDelIncludingCrrEle = maxSumOneDelIncludingCrrEle + max(vec[i], 0);

        maxSum = max(maxSum, maxSumOneDelIncludingCrrEle);
    }

    return maxSum;
}

int maximumSumCorrectDebug(vector<int>& vec, bool debug) {
    int maxSum = INT_MIN;

    if (allNonPositive(vec)) {
        maxSum = findMaxEle(vec);
    } else {
        vector<int> mehLeft = createMaxEndingHereLeft(vec);
        vector<int> mehRight = createMaxEndingHereRight(vec);
        if (debug) {
            cout << "mehLeft" << endl;
            showVec(mehLeft, INT_MAX);
            cout << "mehRight" << endl;
            showVec(mehRight, INT_MAX);
        }

        maxSum = findMaxSumWithOneDel(vec, mehLeft, mehRight, debug);
    }

    return maxSum;
}

void testMaximumSumCorrectDebug() {
    vector<int> arr;

    // arr = {1, -2, 0, 3};
    // assert(maximumSumCorrectDebug(arr, true) == 4);

    // arr = {1, -2, -2, 3};
    // assert(maximumSumCorrectDebug(arr, false) == 3);

    // arr = {-1, -1, -1, -1};
    // assert(maximumSumCorrectDebug(arr, false) == -1);

    // arr = {1, -4, -5, -2, 5, 0, -1, 2};
    // assert(maximumSumCorrectDebug(arr, false) == 7);

    arr = {11, -10, -11, 8, 7, -6, 9, 4, 11, 6, 5, 0};
    assert(maximumSumCorrectDebug(arr, true) == 50);
}

////////
// main
////////

int maximumSum(vector<int>& arr) {
    // return maximumSumWrongDebug(arr, false);
    return maximumSumCorrectDebug(arr, false);
}

int main() {
    testMaximumSumCorrectDebug();
    return 0;
}
