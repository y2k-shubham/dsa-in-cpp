// LeetCode-2640: https://leetcode.com/problems/find-the-score-of-all-prefixes-of-an-array/
// dumb, do-as-directed problem. Skip looking

#include <vector>

using namespace std;

class Solution {
private:
    vector<int> createConverVec(vector<int>& nums) {
        int len = nums.size();

        vector<int> conver(len, 0);
        int maxSoFar = nums[0];
        for (int i = 0; i < len; i++) {
            int crrEle = nums[i];

            maxSoFar = max(maxSoFar, crrEle);
            conver[i] = crrEle + maxSoFar;
        }

        return conver;
    }

    vector<long long> createPrefixSumVec(vector<int>& conver) {
        int len = conver.size();

        vector<long long> prefixSum(len, 0L);
        long long sum = 0L;
        for (int i = 0; i < len; i++) {
            sum += conver[i];
            prefixSum[i] = sum;
        }

        return prefixSum;
    }

public:
    vector<long long> findPrefixScore(vector<int>& nums) {
        vector<int> conver = createConverVec(nums);
        return createPrefixSumVec(conver);
    }
};
