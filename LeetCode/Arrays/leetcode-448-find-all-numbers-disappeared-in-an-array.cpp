// LeetCode-448: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
   private:
    void setNegs(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int val = abs(nums[i]);
            nums[val - 1] = -1 * abs(nums[val - 1]);
        }
    }

    list<int> findMissingNums(vector<int>& nums) {
        int n = nums.size();

        list<int> missingNums;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                missingNums.push_back(i + 1);
            }
        }

        return missingNums;
    }

    vector<int> convertToVec(list<int>& mList) {
        if (mList.empty()) {
            return {};
        }

        vector<int> vec(mList.begin(), mList.end());
        return vec;
    }

   public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        setNegs(nums);
        list<int> missingNums = findMissingNums(nums);
        return convertToVec(missingNums);
    }
};
