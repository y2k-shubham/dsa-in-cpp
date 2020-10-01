// LeetCode-120: https://leetcode.com/problems/triangle
// https://www.interviewbit.com/problems/min-sum-path-in-triangle
// https://www.geeksforgeeks.org/maximum-path-sum-triangle/
// https://www.hackerrank.com/contests/projecteuler/challenges/euler018/problem this one asks for MAXIMUM sum (rather than minimum)

#include <climits>
#include <cmath>
#include <vector>

using namespace std;

int minimumTotal(vector<vector<int>>& triangle) {
    int len = triangle.size();

    if (len == 0) {
        return 0;
    } else if (len == 1) {
        return triangle[0][0];
    } else {
        vector<int> prevCost(len);
        vector<int> crrCost(len);
        prevCost[0] = triangle[0][0];

        for (int i = 1; i < len; i++) {
            // 1st value
            crrCost[0] = triangle[i][0] + prevCost[0];

            // intermediate values
            for (int j = 1; j < i; j++) {
                crrCost[j] = min(prevCost[j - 1], prevCost[j]) + triangle[i][j];
            }

            // last value
            crrCost[i] = prevCost[i - 1] + triangle[i][i];

            prevCost = crrCost;
        }

        int minCost = INT_MAX;
        for (int j = 0; j < len; j++) {
            minCost = min(minCost, crrCost[j]);
        }

        return minCost;
    }
}
