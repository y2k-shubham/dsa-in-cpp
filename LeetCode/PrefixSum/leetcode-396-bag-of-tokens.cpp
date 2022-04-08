// LeetCode-396: https://leetcode.com/problems/rotate-function/
// not a medium problem; clever maths involved

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug;

    vector<int> buildPrefSum(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> prefSum(len);
        prefSum[0] = vec[0];

        for (int i = 1; i < len; i++) {
            prefSum[i] = prefSum[i - 1] + vec[i];
        }

        return prefSum;
    }

    vector<long long> buildProgPrefSum(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<long long> progPrefSum(len);
        progPrefSum[0] = vec[0] * 0;

        for (int i = 1; i < len; i++) {
            progPrefSum[i] = progPrefSum[i - 1] + (vec[i] * ((long long) i));
        }

        return progPrefSum;
    }

    vector<int> buildSuffSum(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> suffSum(len);
        suffSum[len - 1] = vec[len - 1];

        for (int i = len - 2; i >= 0; i--) {
            suffSum[i] = vec[i] + suffSum[i + 1];
        }

        return suffSum;
    }

public:
    friend class SolutionTest;

    int maxRotateFunction(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        vector<int> prefSum = buildPrefSum(nums);
        vector<long long> progPrefSum = buildProgPrefSum(nums);
        vector<int> suffSum = buildSuffSum(nums);

        long long maxSum = progPrefSum[len - 1];
        for (int i = 1; i < len; i++) {
            /**
             * the way to think: instead of shifting (rotating) numbers, let's think like we're
             * rotating their multipliers instead
             *
             * after 1 rotation
             * 0*a[0] + 1*a[1] + 2*a[2] ... n*a[n]
             * will become
             * n*a[0] + 0*a[1] + 1*a[2] ... (n-1)*a[n-1]
             *
             * in general, consider we want to evaluate this sum (i=k)
             * (n-k+0)*a[0] + (n-k+1)*a[1] + (n-k+2)*a[2] ... n*a[k-1] ... (n-k-1)*a[n]
             * ^---------left-part--------------------------^  ^------right-part-----^
             *
             * this can be calculated by applying some clever maths using
             * prefixSum, progPrefixSum & suffixSum
             *
             * progPrefixSum (progressive prefix sum) is just the vector storing this sum (with multipliers) at every posn
             * 0*a[0] + 1*a[1] + 2*a[2] ... n*a[n]
             */

            // sum of left part
            long long baseLSum = progPrefSum[i - 1];
            long long addendLSum = prefSum[i - 1] * (len - i);
            long long totalLSum = baseLSum + addendLSum;

            // sum of right part
            long long baseRSum = (progPrefSum[len - 1] - progPrefSum[i - 1]);
            long long subtractendRSum = suffSum[i] * i;
            long long totalRSum = baseRSum - subtractendRSum;

            // total sum
            baseLSum = totalLSum + totalRSum;

            // take maximum
            maxSum = max(maxSum, baseLSum);
        }

        return maxSum;
    }
};

class SolutionTest {
public:
    void testBuildProgPrefSum() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<long long> progPrefSumOutExpected;
        vector<long long> progPrefSumOutComputed;

        vecIn = {};
        progPrefSumOutExpected = {};
        progPrefSumOutComputed = soln.buildProgPrefSum(vecIn);
        assert(progPrefSumOutExpected == progPrefSumOutComputed);

        vecIn = {2, 5, 1, 9};
        progPrefSumOutExpected = {0, 5, 7, 34};
        progPrefSumOutComputed = soln.buildProgPrefSum(vecIn);
        assert(progPrefSumOutExpected == progPrefSumOutComputed);

        vecIn = {2, -5, 1, -9, 4};
        progPrefSumOutExpected = {0, -5, -3, -30, -14};
        progPrefSumOutComputed = soln.buildProgPrefSum(vecIn);
        assert(progPrefSumOutExpected == progPrefSumOutComputed);
    }

    void testMaxRotateFunction() {
        Solution soln = Solution();
        vector<int> vecIn;
        int outExpected, outComputed;

        vecIn = {};
        outExpected = 0;
        outComputed = soln.maxRotateFunction(vecIn);
        assert(outExpected == outComputed);

        vecIn = {9};
        outExpected = 0;
        outComputed = soln.maxRotateFunction(vecIn);
        assert(outExpected == outComputed);

        soln.debug = true;
        vecIn = {4, 3, 2, 6};
        outExpected = 26;
        outComputed = soln.maxRotateFunction(vecIn);
        assert(outExpected == outComputed);
        soln.debug = false;

        vecIn = {100};
        outExpected = 0;
        outComputed = soln.maxRotateFunction(vecIn);
        assert(outExpected == outComputed);

        // [1,2,3,4,5,6,7,8,9,10]
        soln.debug = true;
        vecIn = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        outExpected = 330;
        outComputed = soln.maxRotateFunction(vecIn);
        assert(outExpected == outComputed);
        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildProgPrefSum();
    solnTest.testMaxRotateFunction();

    return 0;
}
