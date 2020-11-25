// LeetCode-1186: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/

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

int maximumSumDebug(vector<int>& arr, bool debug) {
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

void testMaximumSumDebug() {
    vector<int> arr;

    arr = {1, -2, 0, 3};
    assert(maximumSumDebug(arr, false) == 4);

    arr = {1, -2, -2, 3};
    assert(maximumSumDebug(arr, false) == 3);

    arr = {-1, -1, -1, -1};
    assert(maximumSumDebug(arr, false) == -1);

    arr = {1, -4, -5, -2, 5, 0, -1, 2};
    assert(maximumSumDebug(arr, false) == 7);

    arr = {11, -10, -11, 8, 7, -6, 9, 4, 11, 6, 5, 0};
    assert(maximumSumDebug(arr, true) == 50);
}

int maximumSum(vector<int>& arr) {
    return maximumSumDebug(arr, false);
}

int main() {
    testMaximumSumDebug();
    return 0;
}
