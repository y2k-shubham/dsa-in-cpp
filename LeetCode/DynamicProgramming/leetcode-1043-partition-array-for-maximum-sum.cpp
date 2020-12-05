// LeetCode-1043: https://leetcode.com/problems/partition-array-for-maximum-sum/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> maxSumEnding;
    vector<vector<int> > maxEleInRange;

    void computeMaxInRange() {
        int len = this->vec.size();
        vector<vector<int> > maxEleInRange(len);

        for (int i = 0; i < len; i++) {
            vector<int> matRow(len, INT_MIN);
            matRow[i] = this->vec[i];
            maxEleInRange[i] = matRow;
        }

        int rLo = 0;
        int cHi = len - 1;

        for (int subArrSize = 2; subArrSize <= len; subArrSize++) {
            int iStart = rLo;
            int jStart = subArrSize - 1;

            int i = iStart;
            int j = jStart;
            while ((j <= cHi)) {
                maxEleInRange[i][j] = max(maxEleInRange[i][j - 1], maxEleInRange[i + 1][j]);

                i++;
                j++;
            }
        }

        this->maxEleInRange = maxEleInRange;
    }

    void showMaxInRange() {
        int len = this->vec.size();
        printf("\n\t");

        for (int j = 0; j < len; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < len; j++) {
                if (j < i) {
                    printf("\t");
                } else {
                    printf("%d\t", this->maxEleInRange[i][j]);
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // LC-submission speed: 10%tile, memory: 5%tile
    void calcMaxSumEnding() {
        int len = this->vec.size();
        vector<int> maxSumEnding(len);

        // before k (incomplete / just-complete windows)
        for (int k = 0; k < this->k; k++) {
            int maxEle = this->maxEleInRange[0][k];
            maxSumEnding[k] = maxEle * (k + 1);
        }

        // complete k-length sliding window
        for (int i = this->k; i < len; i++) {
            int crrRangeMaxSum = INT_MIN;

            int rangeEndInd = i;
            for (int rangeSize = 1; rangeSize <= this->k; rangeSize++) {
                int rangeBeginInd = i - rangeSize + 1;

                int preComputedSum = maxSumEnding[rangeBeginInd - 1];
                int rangeSum = this->maxEleInRange[rangeBeginInd][rangeEndInd] * rangeSize;
                int totalSum = preComputedSum + rangeSum;

                crrRangeMaxSum = max(crrRangeMaxSum, totalSum);
            }

            maxSumEnding[i] = crrRangeMaxSum;
        }

        this->maxSumEnding = maxSumEnding;
    }

   public:
    vector<int> vec;
    int k;

    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        this->vec = arr;
        this->k = k;

        int len = this->vec.size();

        computeMaxInRange();
        calcMaxSumEnding();

        return this->maxSumEnding[len - 1];
    }
};

int main() {
    Solution soln = Solution();
    vector<int> vec;
    int k;

    vec = {1, 15, 7, 9, 2, 5, 10};
    k = 3;
    assert(soln.maxSumAfterPartitioning(vec, k) == 84);

    vec = {1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3};
    k = 4;
    assert(soln.maxSumAfterPartitioning(vec, k) == 83);

    vec = {1};
    k = 1;
    assert(soln.maxSumAfterPartitioning(vec, k) == 1);

    return 0;
}
