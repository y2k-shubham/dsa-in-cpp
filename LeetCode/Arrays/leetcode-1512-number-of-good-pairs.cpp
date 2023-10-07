// LeetCode-1512: https://leetcode.com/problems/number-of-good-pairs/
// pretty dumb problem; don't bother looking

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int, int> freqMap;

        int numPairs = 0;
        for (int i = 0; i < nums.size(); i++) {
            int ele = nums[i];

            numPairs += freqMap[ele];
            freqMap[ele]++;
        }

        return numPairs;
    }
};
