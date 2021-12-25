// LeetCode-2111: https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/
// incomplete soln

/**
 * input
 * [5,4,3,2,1]
 * output
 * 1
 * 
 * input
 * [4,1,5,2,6,2]
 * output
 * 2
 * 
 * input
 * [4,1,5,2,6,2]
 * output
 * 3
 * 
 * input
 * [12,6,12,6,14,2,13,17,3,8,11,7,4,11,18,8,8,3]
 * output
 * 12
 */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = true;

    void showVec(vector<int>& vec) {
        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    int kIncLeft(vector<int> vec, int k) {
        int len = vec.size();
        if (len < k) {
            return 0;
        }

        int numOps = 0;
        for (int i = k; i < len; i++) {
            int crrEle = vec[i];

            int prevEleIdx = i - k;
            int prevEle = vec[prevEleIdx];

            if (prevEle <= crrEle) {
                if (debug) {
                    printf("left at prev=vec[%d]=%d and vec[i=%d]=%d, no change needed\n", prevEleIdx, prevEle, i, crrEle);
                }
                continue;
            }

            if (prevEleIdx < k) {
                if (debug) {
                    printf("left at prev=vec[%d]=%d and vec[i=%d]=%d, 'if' setting prev to crr\n", prevEleIdx, prevEle, i, crrEle);
                }
                vec[prevEleIdx] = crrEle;
            } else {
                if (vec[prevEleIdx - k] <= crrEle) {
                    if (debug) {
                        printf("left at prev=vec[%d]=%d and vec[i=%d]=%d, 'else-if' setting prev to crr\n", prevEleIdx, prevEle, i, crrEle);
                    }
                    vec[prevEleIdx] = crrEle;
                } else {
                    if (debug) {
                        printf("left at prev=vec[%d]=%d and vec[i=%d]=%d, 'else-else' setting crr to prev\n", prevEleIdx, prevEle, i, crrEle);
                    }
                    vec[i] = prevEle;
                }
            }

            numOps++;

            if (debug) {
                printf("left after iter=%d, numOps=%d\n", (i - k + 1), numOps);
                showVec(vec);
                printf("\n");
            }
        }

        if (debug) {
            printf("left ans = %d\n------\n", numOps);
        }

        return numOps;
    }

    int kIncRight(vector<int> vec, int k) {
        int len = vec.size();
        if (len < k) {
            return 0;
        }

        int numOps = 0;
        for (int i = len - 1; i >= k; i--) {
            int crrEle = vec[i];

            int prevEleIdx = i - k;
            int prevEle = vec[prevEleIdx];

            if (prevEle <= crrEle) {
                if (debug) {
                    printf("right at prev=vec[%d]=%d and vec[i=%d]=%d, no change needed\n", prevEleIdx, prevEle, i, crrEle);
                }
                continue;
            }

            if (i > (len - 1 - k)) {
                if (debug) {
                    printf("right at prev=vec[%d]=%d and vec[i=%d]=%d, 'if' setting crr to prev\n", prevEleIdx, prevEle, i, crrEle);
                }
                vec[i] = prevEle;
            } else {
                if (vec[i + k] >= prevEle) {
                    if (debug) {
                        printf("right at prev=vec[%d]=%d and vec[i=%d]=%d, 'else-if' setting crr to prev\n", prevEleIdx, prevEle, i, crrEle);
                    }
                    vec[i] = prevEle;
                } else {
                    if (debug) {
                        printf("right at prev=vec[%d]=%d and vec[i=%d]=%d, 'else-else' setting prev to crr\n", prevEleIdx, prevEle, i, crrEle);
                    }
                    vec[prevEleIdx] = crrEle;
                }
            }

            numOps++;

            if (debug) {
                printf("right after iter=%d, numOps=%d\n", (len - 1 - i + 1), numOps);
                showVec(vec);
                printf("\n");
            }
        }

        if (debug) {
            printf("right ans = %d\n", numOps);
        }

        return numOps;
    }

   public:
    int kIncreasing(vector<int>& arr, int k) {
        int len = arr.size();
        if (len < k) {
            return 0;
        }
        if (len <= 1) {
            return 0;
        }

        return min(
            kIncLeft(arr, k),
            kIncRight(arr, k));
    }
};
