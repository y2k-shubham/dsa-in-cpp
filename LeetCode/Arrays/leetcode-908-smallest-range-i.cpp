// LeetCode-908: https://leetcode.com/problems/smallest-range-i/

#include <climits>
#include <vector>

using namespace std;

int smallestRangeI(vector<int>& A, int K) {
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] < minVal) {
            minVal = A[i];
        }
        if (A[i] > maxVal) {
            maxVal = A[i];
        }
    }

    int diff = maxVal - minVal;
    if (diff <= (2 * K)) {
        return 0;
    } else {
        return diff - (2 * K);
    }
}
