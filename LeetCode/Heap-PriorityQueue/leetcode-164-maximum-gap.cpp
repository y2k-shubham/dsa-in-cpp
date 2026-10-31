// LeetCode-164: https://leetcode.com/problems/maximum-gap/

#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) {
            return 0;
        }

        priority_queue<int, vector<int>, greater<int>> minHeap(nums.begin(), nums.end());

        int maxGap = 0;
        int prev = INT_MIN;
        while (!minHeap.empty()) {
            int crr = minHeap.top();
            minHeap.pop();

            int crrGap = (prev == INT_MIN) ? 0 : (crr - prev);
            maxGap = max(maxGap, crrGap);

            prev = crr;
        }

        return maxGap;
    }
};
