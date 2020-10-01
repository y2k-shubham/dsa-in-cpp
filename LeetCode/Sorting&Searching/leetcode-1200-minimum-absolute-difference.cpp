// LeetCode-1200: https://leetcode.com/problems/minimum-absolute-difference/
// https://www.geeksforgeeks.org/find-minimum-difference-pair/
// https://www.hackerrank.com/challenges/minimum-absolute-difference-in-an-array/problem

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
    int len = arr.size();
    sort(arr.begin(), arr.end());

    int minDiff = INT_MAX;
    for (int i = 1; i < len; i++) {
        minDiff = min(minDiff, arr[i] - arr[i - 1]);
    }

    vector<vector<int>> minDiffPairs;
    for (int i = 1; i < len; i++) {
        if ((arr[i] - arr[i - 1]) == minDiff) {
            minDiffPairs.push_back({arr[i - 1], arr[i]});
        }
    }

    return minDiffPairs;
}
