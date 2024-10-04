// LeetCode-3190: https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three
// dumb question; dont bother looking

#include <vector>

using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int totalOperations = 0;

        for (int n: nums) {
            int mod3 = n % 3;
            totalOperations += min(mod3, 3 - mod3);
        }

        return totalOperations;
    }
};
