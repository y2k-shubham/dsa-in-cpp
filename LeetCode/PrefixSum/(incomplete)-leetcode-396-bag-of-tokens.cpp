// LeetCode-396: https://leetcode.com/problems/rotate-function/
// incomplete: getting wrong answer right now (approach is likely correct)

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
        long long crrSum = maxSum;
        for (int i = 1; i < len; i++) {
            //crrSum = progPrefSum[i - 1] + (prefSum[i - 1] * (len - i));
            //crrSum += (prefSum[i - 1] * (len - i));
            crrSum += prefSum[i - 1] * (len - i);

            //crrSum -= nums[i];
            //crrSum -= (i < (len - 1)) ? suffSum[i + 1] : 0;
            crrSum -= suffSum[i];
            if (debug) {
                printf("at i=%d\n", i);
                printf("added prefSum[%d]=%d * %d = %d\n", (i - 1), prefSum[i - 1], (len - i), (prefSum[i - 1] * (len - i)));
                printf("subtracted suffSum[%d] = %d\n", i, suffSum[i]);
                printf("crrSum = %lld\n", crrSum);
                printf("---------\n");
            }

            maxSum = max(maxSum, crrSum);
        }

        return maxSum;
    }
};

class SolutionTest {
public:
    void testBuildProgPrefSum() {
        Solution soln = Solution();
        vector <int> vecIn;
        vector <long long> progPrefSumOutExpected;
        vector <long long> progPrefSumOutComputed;

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
        vector <int> vecIn;
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
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildProgPrefSum();
    solnTest.testMaxRotateFunction();

    return 0;
}
