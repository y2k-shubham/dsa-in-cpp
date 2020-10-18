// LeetCode-198: https://leetcode.com/problems/house-robber/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

// LC submission: speed: 53 %tile (how to improve?) & memory: 100 %tile
int rob(vector<int>& nums) {
    int prevIncSum = 0;
    int prevExcSum = 0;

    for (int i = 0; i < nums.size(); i++) {
        int crrIncSum = prevExcSum + nums[i];
        int crrExcSum = max(prevExcSum, prevIncSum);

        prevIncSum = crrIncSum;
        prevExcSum = crrExcSum;
    }

    return max(prevIncSum, prevExcSum);
}
