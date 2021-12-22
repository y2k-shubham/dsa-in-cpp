// LeetCode-2087: https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/

// question just takes a bit to understand; otherwise solution-wise it is very dumb
// we just have to sum up cost of moving from source row to destination row and source col to dest col
// (yes, thats right: nothing else; baloney!)

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minCost(
        vector<int>& startPos,
        vector<int>& homePos,
        vector<int>& rowCosts,
        vector<int>& colCosts
    ) {
        int totalCost = 0;
        
        int rBegin = startPos[0];
        int rEnd = homePos[0];
        if (rBegin < rEnd) {
            for (int r = rBegin + 1; r <= rEnd; r++) {
                totalCost += rowCosts[r];
            }
        } else if (rBegin > rEnd) {
            for (int r = rBegin - 1; r >= rEnd; r--) {
                totalCost += rowCosts[r];
            }
        }
        
        int cBegin = startPos[1];
        int cEnd = homePos[1];
        if (cBegin < cEnd) {
            for (int c = cBegin + 1; c <= cEnd; c++) {
                totalCost += colCosts[c];
            }
        } else if (cBegin > cEnd) {
            for (int c = cBegin - 1; c >= cEnd; c--) {
                totalCost += colCosts[c];
            }
        }
        
        return totalCost;
    }
};