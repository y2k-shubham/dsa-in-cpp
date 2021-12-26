// LeetCode-1646: https://leetcode.com/problems/get-maximum-in-generated-array/
// pretty dumb problem; look away

#include <vector>

using namespace std;

#define MAX 101

class Solution {
   public:
    int getMaximumGenerated(int n) {
        vector<int> vec(MAX, 0);
        vec[0] = 0;
        vec[1] = 1;

        if (n <= 1) {
            return vec[n];
        }

        int maxVal = 1;
        for (int i = 2; i <= n; i++) {
            if ((i % 2) == 0) {
                // even
                vec[i] = vec[i / 2];
            } else {
                // odd
                vec[i] = vec[i / 2] + vec[(i / 2) + 1];
            }

            maxVal = max(maxVal, vec[i]);
        }

        return maxVal;
    }
};
