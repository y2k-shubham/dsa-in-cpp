// LeetCode-1191: https://leetcode.com/problems/k-concatenation-maximum-sum/

#include <vector>
#include <cassert>

using namespace std;

#define MODULO 1000000007

class Solution {
private:
    vector <long long> createPrefixSumVec(const vector <int>& vec) {
        int len = vec.size();
        vector <long long> prefixSumVec(len);

        long long prefixSum = 0;
        for (int i = 0; i < len; i++) {
            prefixSum += vec[i];
            prefixSumVec[i] = prefixSum;
        }

        return prefixSumVec;
    }

    vector <long long> createSuffixSumVec(const vector <int>& vec) {
        int len = vec.size();
        vector <long long> suffixSumVec(len);

        long long suffixSum = 0;
        for (int i = len - 1; i >= 0; i--) {
            suffixSum += vec[i];
            suffixSumVec[i] = suffixSum;
        }

        return suffixSumVec;
    }

    long long calculateMaxSubArraySum(const vector <int>& vec) {
        long long maxSubArraySum = 0;

        long long crrSubArraySum = 0;
        for (int val : vec) {
            crrSubArraySum += val;

            if (crrSubArraySum < 0) {
                crrSubArraySum = 0;
            } else {
                maxSubArraySum = max(maxSubArraySum, crrSubArraySum);
            }
        }

        return maxSubArraySum;
    }

    int calculateModulo(const long long num) {
        return static_cast <int>(num % MODULO);
    }

public:
    int kConcatenationMaxSum(const vector <int>& vec, const int k) {
        long long maxSubarraySumForSingleVec = calculateMaxSubArraySum(vec);
        if (k == 1) {
            return calculateModulo(maxSubarraySumForSingleVec);
        }

        vector <long long> prefixSumVec = createPrefixSumVec(vec);
        vector <long long> suffixSumVec = createSuffixSumVec(vec);

        long long vecSum = suffixSumVec[0];
        long long maxPrefixSum = *max_element(prefixSumVec.begin(), prefixSumVec.end());
        long long maxSuffixSum = *max_element(suffixSumVec.begin(), suffixSumVec.end());

        long long maxSum = 0;

        if ((vecSum > 0) && (k > 2)) {
            maxSum += vecSum * (k - 2);
        }

        maxSum += max(maxPrefixSum, 0LL);
        maxSum += max(maxSuffixSum, 0LL);

        /**
         * IMPORTANT: considering max subarray sum for single array is necessary
         * this is because we could have a case where a long array mostly made up of big negative numbers
         * may have a 'small patch' of big positive numbers in between, which could sum upto greater than
         * max prefix or suffix sum (when in such case the sum of entire array would likely be negative)
         *
         * Also it is important to take modulo after taking max, otherwise we'll get wrong result
         * for few edge cases (including the one given here below in tests)
         */
        return calculateModulo(max(maxSubarraySumForSingleVec, maxSum));
    }
};

class SolutionTest {
private:
    vector <int> generateInput(int val, int len) {
        vector <int> vec(len, val);
        return vec;
    }

public:
    void testKConcatenationMaxSum() {
        Solution soln = Solution();
        vector <int> vecIn;
        int kIn;
        long long maxSumOutExpected, maxSumOutComputed;

        vecIn = generateInput(10000, 100000);
        kIn = 2;
        maxSumOutExpected = 999999993;
        maxSumOutComputed = soln.kConcatenationMaxSum(vecIn, kIn);
        assert(maxSumOutExpected == maxSumOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testKConcatenationMaxSum();

    return 0;
}
