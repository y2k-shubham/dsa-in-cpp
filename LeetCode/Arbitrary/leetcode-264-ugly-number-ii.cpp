// LeetCode-264: https://leetcode.com/problems/ugly-number-ii/
// (if stuck, refer to hints on LeetCode)

#include <vector>

using namespace std;

class Solution {
   public:
    int nthUglyNumber(int n) {
        vector<unsigned long long> uglyNums(n + 1);

        uglyNums[0] = 1;
        int idxUglyNum = 1;

        int idx2 = 0;
        int idx3 = 0;
        int idx5 = 0;
        while (idxUglyNum < n) {
            unsigned long long mult2Num = uglyNums[idx2] * 2;
            unsigned long long mult3Num = uglyNums[idx3] * 3;
            unsigned long long mult5Num = uglyNums[idx5] * 5;

            // printf("\nmult2=%lld, mult3=%lld, mult5=%lld\n", mult2Num, mult3Num, mult5Num);

            if (mult2Num <= min(mult3Num, mult5Num)) {
                // printf("picking 2: setting arr[%d]=%lld\n", idxUglyNum, mult2Num);
                uglyNums[idxUglyNum] = mult2Num;
                idx2++;

                if (mult2Num == mult3Num) {
                    idx3++;
                }
                if (mult2Num == mult5Num) {
                    idx5++;
                }
            } else if (mult3Num <= min(mult2Num, mult5Num)) {
                // printf("picking 3: setting arr[%d]=%lld\n", idxUglyNum, mult3Num);
                uglyNums[idxUglyNum] = mult3Num;
                idx3++;

                if (mult3Num == mult2Num) {
                    idx2++;
                }
                if (mult3Num == mult5Num) {
                    idx5++;
                }
            } else {
                // printf("picking 5: setting arr[%d]=%lld\n", idxUglyNum, mult5Num);
                uglyNums[idxUglyNum] = mult5Num;
                idx5++;

                if (mult5Num == mult2Num) {
                    idx2++;
                }
                if (mult5Num == mult3Num) {
                    idx3++;
                }
            }

            idxUglyNum++;
        }

        return (int)uglyNums[idxUglyNum - 1];
    }
};
