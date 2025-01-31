// LeetCode-3334: https://leetcode.com/problems/find-the-maximum-factor-score-of-array/

// many edge cases
// even long long multiplication was overflowing, had to use unsigned long long for intermediate calculations

#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    void printVector(const vector <int>& vec, const string& name) {
        if (vec.empty()) {
            cout << "The vector '" << name << "' is empty" << endl;
            return;
        }

        cout << "The vector '" << name << "' is:-" << endl;

        // Print indexes
        cout << "Idx:\t";
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        // Print values
        cout << "Val:\t";
        for (int val : vec) {
            printf("%d\t", val);
        }
        cout << endl;
    }

    void printVector(const vector <unsigned long long>& vec, const string& name) {
        if (vec.empty()) {
            cout << "The vector '" << name << "' is empty" << endl;
            return;
        }

        cout << "The vector '" << name << "' is:-" << endl;

        // Print indexes
        cout << "Idx:\t";
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        // Print values
        cout << "Val:\t";
        for (unsigned long long val : vec) {
            printf("%lld\t", val);
        }
        cout << endl;
    }


    // ------- HCF / GCD utilities -------
    unsigned long long findHcf(unsigned long long num1, unsigned long long num2) {
        // Handle cases involving zero
        if (num1 == 0) {
            return num2;
        }
        if (num2 == 0) {
            return num1;
        }
        if (min(num1, num2) == 1) {
            return 1;
        }

        unsigned long long numSmall = min(num1, num2);
        unsigned long long numBig = max(num1, num2);

        unsigned long long divisor = numSmall;
        unsigned long long dividend = numBig;
        unsigned long long remainder = dividend % divisor;
        while (remainder > 0) {
            dividend = divisor;
            divisor = remainder;
            remainder = dividend % divisor;
        }

        return divisor;
    }

    vector <int> buildHcfPrefixVec(vector <int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector <int> hcfPrefixVec(len);
        int crrHcf = vec[0];
        hcfPrefixVec[0] = crrHcf;

        for (int i = 1; i < len; i++) {
            crrHcf = static_cast <int>(findHcf(crrHcf, vec[i]));
            // printf("at hcfPrefixVec[i=%d] = hcf(crrHcf=%d, vec[i=%d]=%d) = %d\n", i, crrHcf, i, vec[i], crrHcf);
            hcfPrefixVec[i] = crrHcf;
        }

        return hcfPrefixVec;
    }

    vector <int> buildHcfSuffixVec(vector <int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector <int> hcfSuffixVec(len);
        int crrHcf = vec[len - 1];
        hcfSuffixVec[len - 1] = crrHcf;

        for (int i = len - 2; i >= 0; i--) {
            crrHcf = static_cast <int>(findHcf(crrHcf, vec[i]));
            // printf("at hcfSuffixVec[i=%d] = hcf(crrHcf=%d, vec[i=%d]=%d) = %d\n", i, crrHcf, i, vec[i], crrHcf);
            hcfSuffixVec[i] = crrHcf;
        }

        return hcfSuffixVec;
    }

    // ------- LCM utilities -------

    unsigned long long findLcm(unsigned long long num1, unsigned long long num2) {
        unsigned long long product = num1 * num2;
        return product / findHcf(num1, num2);
    }

    vector <unsigned long long> buildLcmPrefixVec(vector <int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {static_cast <unsigned long long>(vec[0])};
        }

        vector <unsigned long long> lcmPrefixVec(len);
        unsigned long long crrLcm = vec[0];
        lcmPrefixVec[0] = crrLcm;

        for (int i = 1; i < len; i++) {
            // unsigned long long prevLcm = crrLcm;
            crrLcm = findLcm(crrLcm, vec[i]);
            // printf("at lcmPrefixVec[i=%d] = lcm(crrLcm=%lld, vec[i=%d]=%d) = %lld\n", i, prevLcm, i, vec[i], crrLcm);
            lcmPrefixVec[i] = crrLcm;
        }

        return lcmPrefixVec;
    }

    vector <unsigned long long> buildLcmSuffixVec(vector <int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {static_cast <unsigned long long>(vec[0])};
        }

        vector <unsigned long long> lcmSuffixVec(len);
        unsigned long long crrLcm = vec[len - 1];
        lcmSuffixVec[len - 1] = crrLcm;

        for (int i = len - 2; i >= 0; i--) {
            // unsigned long long prevLcm = crrLcm;
            crrLcm = findLcm(crrLcm, vec[i]);
            // printf("at lcmPrefixVec[i=%d] = lcm(crrLcm=%lld, vec[i=%d]=%d) = %lld\n", i, prevLcm, i, vec[i], crrLcm);
            lcmSuffixVec[i] = crrLcm;
        }

        return lcmSuffixVec;
    }

public:
    long long maxScore(vector <int>& nums) {
        int len = nums.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return static_cast <long long>(nums[0] * static_cast <unsigned long long>(nums[0]));
        }

        vector <int> hcfPrefixVec = buildHcfPrefixVec(nums);
        vector <int> hcfSuffixVec = buildHcfSuffixVec(nums);

        vector <unsigned long long> lcmPrefixVec = buildLcmPrefixVec(nums);
        vector <unsigned long long> lcmSuffixVec = buildLcmSuffixVec(nums);

        // printVector(nums, "nums");
        //
        // printVector(hcfPrefixVec, "hcfPrefixVec");
        // printVector(lcmPrefixVec, "lcmPrefixVec");
        //
        // printVector(hcfSuffixVec, "hcfSuffixVec");
        // printVector(lcmSuffixVec, "lcmSuffixVec");

        unsigned long long maxFactorScore = 0;
        for (int i = 1; i < len - 1; i++) {
            int prefixHcfWithoutCrrIdx = hcfPrefixVec[i - 1];
            int suffixHcfWithoutCrrIdx = hcfSuffixVec[i + 1];

            unsigned long long prefixLcmWithoutCrrIdx = lcmPrefixVec[i - 1];
            unsigned long long suffixLcmWithoutCrrIdx = lcmSuffixVec[i + 1];

            int hcfWithoutCrrIdx = static_cast <int>(findHcf(prefixHcfWithoutCrrIdx, suffixHcfWithoutCrrIdx));
            unsigned long long lcmWithoutCrrIdx = findLcm(prefixLcmWithoutCrrIdx, suffixLcmWithoutCrrIdx);

            unsigned long long crrFactorScore = hcfWithoutCrrIdx * lcmWithoutCrrIdx;
            maxFactorScore = max(maxFactorScore, crrFactorScore);
        }

        unsigned long long factorScoreWithoutFirstIdx = hcfSuffixVec[1] * lcmSuffixVec[1];
        unsigned long long factorScoreWithoutLastIdx = hcfPrefixVec[len - 2] * lcmPrefixVec[len - 2];
        unsigned long long factorScoreWithoutRemovingAnyElement = hcfSuffixVec[0] * lcmSuffixVec[0];

        maxFactorScore = max(maxFactorScore, factorScoreWithoutFirstIdx);
        maxFactorScore = max(maxFactorScore, factorScoreWithoutLastIdx);
        maxFactorScore = max(maxFactorScore, factorScoreWithoutRemovingAnyElement);

        return static_cast <long long>(maxFactorScore);
    }
};

class SolutionTest {
public:
    void testMaxScore() {
        Solution soln = Solution();
        vector <int> vecIn;
        unsigned long long scoreOutExpected, scoreOutComputed;

        vecIn = {2, 4, 8, 16};
        scoreOutExpected = 64;
        scoreOutComputed = soln.maxScore(vecIn);
        assert(scoreOutExpected == scoreOutComputed);

        // vecIn = {1, 2, 3, 4, 5};
        // scoreOutExpected = 60;
        // scoreOutComputed = soln.maxScore(vecIn);
        // assert(scoreOutExpected == scoreOutComputed);
        //
        // vecIn = {18};
        // scoreOutExpected = 324;
        // scoreOutComputed = soln.maxScore(vecIn);
        // assert(scoreOutExpected == scoreOutComputed);
        //
        // vecIn = {6, 5, 1, 9};
        // scoreOutExpected = 90;
        // scoreOutComputed = soln.maxScore(vecIn);
        // // cout << scoreOutComputed << endl;
        // assert(scoreOutExpected == scoreOutComputed);
        //
        // vecIn = {6, 14, 20};
        // scoreOutExpected = 840;
        // scoreOutComputed = soln.maxScore(vecIn);
        // // cout << scoreOutComputed << endl;
        // assert(scoreOutExpected == scoreOutComputed);
        //
        // vecIn = {11, 4};
        // scoreOutExpected = 121;
        // scoreOutComputed = soln.maxScore(vecIn);
        // // cout << scoreOutComputed << endl;
        // assert(scoreOutExpected == scoreOutComputed);
        //
        // vecIn = {10, 25, 6};
        // scoreOutExpected = 250;
        // scoreOutComputed = soln.maxScore(vecIn);
        // // cout << scoreOutComputed << endl;
        // assert(scoreOutExpected == scoreOutComputed);
        //
        // vecIn = {29, 2, 2, 19, 22, 19, 2, 16, 25, 20, 27, 13, 14, 23, 17, 27, 14, 29, 23, 21, 9, 7, 15, 22, 23};
        // scoreOutExpected = 10765773977026068000;
        // scoreOutComputed = soln.maxScore(vecIn);
        // // cout << scoreOutComputed << endl;
        // assert(scoreOutExpected == scoreOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxScore();

    return 0;
}
