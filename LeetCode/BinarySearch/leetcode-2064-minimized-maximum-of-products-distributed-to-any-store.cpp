// LeetCode-2064: https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    long long calcSum(vector<int>& vec) {
        long long sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            sum += vec[i];
        }

        return sum;
    }

    int calcMax(vector<int>& vec) {
        return *max_element(vec.begin(), vec.end());
    }

    int calcTheoreticalMinimizedMaximum(int n, vector<int>& qtys) {
        long long sum = calcSum(qtys);
        return (int)ceil(sum / (1.0 * n));
    }

    bool canDistribute(int n, vector<int>& qtys, int maxItems) {
        sort(qtys.begin(), qtys.end());

        int m = qtys.size();
        int i;
        for (i = 0; i < m; i++) {
            int qty = qtys[i];
            int numStoresNeeded = (int)ceil(qty / (maxItems * 1.0));

            n -= numStoresNeeded;
            if (n < 0) {
                return false;
            }
        }

        return (i >= m) && (n >= 0);
    }

    // binary search
    // barely accepted; LC submission: speed 5 %tile, memory 42 %tile
    long long findMinimizedMax(
        int n,
        vector<int>& qtys,
        long long minVal,
        long long maxVal) {
        long long minMax = INT_MAX;
        while (minVal <= maxVal) {
            long long midVal = (minVal + maxVal) / 2;
            if (canDistribute(n, qtys, (int)midVal)) {
                minMax = min(minMax, midVal);
                maxVal = midVal - 1;
            } else {
                minVal = midVal + 1;
            }
        }

        return minMax;
    }

   public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        int maxVal = calcMax(quantities);

        int m = quantities.size();
        if (m == n) {
            // each store will simply get entire lot of single product type
            return maxVal;
        }

        int minVal = calcTheoreticalMinimizedMaximum(n, quantities);

        int minimizedMax = findMinimizedMax(n, quantities, minVal, maxVal);
        return minimizedMax;
    }
};