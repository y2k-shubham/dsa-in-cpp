// LeetCode-2206: https://leetcode.com/problems/divide-array-into-equal-pairs/

// solved via brute-force (as per LeetCode's own hint)
// this question would be tricky if you were to solve it any other way

#include <vector>

using namespace std;

#define MIN_VAL 1
#define MAX_VAL 500

class Solution {
private:
    int findCount(vector<int>& vec, int ele) {
        return count(vec.begin(), vec.end(), ele);
    }

public:
    bool divideArray(vector<int>& nums) {
        for (int i = MIN_VAL; i <= MAX_VAL; i++) {
            if ((findCount(nums, i) % 2) != 0) {
                return false;
            }
        }

        return true;
    }
};
