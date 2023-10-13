// LeetCode-905: https://leetcode.com/problems/sort-array-by-parity/
// easy

#include <vector>

using namespace std;

class Solution {
private:
    inline bool isEven(int n) {
        return (n & 1) == 0;
    }

    inline void swapEles(vector <int>& vec, int i1, int i2) {
        if (i1 == i2) {
            return;
        }

        int tmp = vec[i1];
        vec[i1] = vec[i2];
        vec[i2] = tmp;
    }

    void sortArray(vector <int>& nums) {
        int len = nums.size();
        int i = -1;
        for (int j = 0; j < len; j++) {
            if (isEven(nums[j])) {
                ++i;

                // removing this if-expression had no impact on runtim
                if (i != j) {
                    swapEles(nums, i, j);
                }
            }
        }
    }

public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int len = nums.size();
        if (len > 1) {
            sortArray(nums);
        }

        return nums;
    }
};

