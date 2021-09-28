// LeetCode-1962: https://leetcode.com/problems/remove-stones-to-minimize-the-total/

#include <cstdio>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
   public:
    int minStoneSum(vector<int>& pilesVec, int k) {
        priority_queue<int> pilesHeap(pilesVec.begin(), pilesVec.end());

        int numStones = accumulate(pilesVec.begin(), pilesVec.end(), 0);
        for (int i = 1; i <= k; i++) {
            int maxStones = pilesHeap.top();
            pilesHeap.pop();
            if (maxStones == 1) {
                break;
            }

            int removedStones = (int)floor(maxStones / 2.0);

            int remStones = maxStones - removedStones;
            pilesHeap.push(remStones);

            numStones -= removedStones;
        }

        return numStones;
    }
};
