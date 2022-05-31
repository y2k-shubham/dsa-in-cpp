// LeetCode-1461: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/

#include <vector>
#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <cassert>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
private:
    int createMask(int k) {
        return (int) pow(2, k) - 1;
    }

    int extractBitsNum(string& str, int from, int to) {
        if ((from < 0) || (str.size() <= to)) {
            return -1;
        }

        int num = 0;

        for (int i = from; i <= to; i++) {
            num = num << 1;
            num |= str.at(i) - '0';
        }

        return num;
    }

    int countNumUniqueCodes(string& str, int k) {
        if (str.size() < k) {
            return 0;
        }
        if (k == 0) {
            return 1;
        }

        int mask = createMask(k);

        int crrCode = extractBitsNum(str, 0, k - 1);
        unordered_set<int> uniqueCodes = {crrCode};

        for (int i = k; i < str.size(); i++) {
            crrCode <<= 1;
            crrCode |= str.at(i) - '0';
            crrCode &= mask;

            uniqueCodes.insert(crrCode);
        }

        return uniqueCodes.size();
    }

public:
    friend class SolutionTest;

    bool hasAllCodes(string s, int k) {
        return countNumUniqueCodes(s, k) == (int) pow(2, k);
    }
};

class SolutionTest {
public:
    void testCreateMask() {
        Solution soln = Solution();
        int kIn;
        int maskOutExpected, maskOutComputed;

        kIn = 0;
        maskOutExpected = 0;
        maskOutComputed = soln.createMask(kIn);
        assert(maskOutExpected == maskOutComputed);

        kIn = 1;
        maskOutExpected = 1;
        maskOutComputed = soln.createMask(kIn);
        assert(maskOutExpected == maskOutComputed);

        kIn = 2;
        maskOutExpected = 3;
        maskOutComputed = soln.createMask(kIn);
        assert(maskOutExpected == maskOutComputed);

        kIn = 3;
        maskOutExpected = 7;
        maskOutComputed = soln.createMask(kIn);
        assert(maskOutExpected == maskOutComputed);

        kIn = 4;
        maskOutExpected = 15;
        maskOutComputed = soln.createMask(kIn);
        assert(maskOutExpected == maskOutComputed);
    }

    void testExtractBitsNum() {
        Solution soln = Solution();
        string strIn;
        int fromIn, toIn;
        int bitsNumOutExpected, bitsNumOutComputed;

        // empty string

        strIn = "";
        fromIn = 0;
        toIn = 0;
        bitsNumOutExpected = -1;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        fromIn = 0;
        toIn = 5;
        bitsNumOutExpected = -1;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        // non empty string 1
        strIn = "0011";

        fromIn = 0;
        toIn = 0;
        bitsNumOutExpected = 0;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        fromIn = 1;
        toIn = 2;
        bitsNumOutExpected = 1;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        fromIn = 1;
        toIn = 3;
        bitsNumOutExpected = 3;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        fromIn = 3;
        toIn = 3;
        bitsNumOutExpected = 1;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        // non empty string 2
        strIn = "11010011";

        fromIn = 2;
        toIn = 5;
        bitsNumOutExpected = 4;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);

        fromIn = 2;
        toIn = 6;
        bitsNumOutExpected = 9;
        bitsNumOutComputed = soln.extractBitsNum(strIn, fromIn, toIn);
        assert(bitsNumOutExpected == bitsNumOutComputed);
    }

    void testCountNumUniqueCodes() {
        Solution soln = Solution();
        string strIn;
        int kIn;
        int numUniqueCodesOutExpected, numUniqueCodesOutComputed;

        // empty string
        strIn = "";

        kIn = 0;
        numUniqueCodesOutExpected = 1;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 2;
        numUniqueCodesOutExpected = 0;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        // non empty string
        strIn = "00110110";

        kIn = 1;
        numUniqueCodesOutExpected = 2;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 2;
        numUniqueCodesOutExpected = 4;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 3;
        numUniqueCodesOutExpected = 4;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 4;
        numUniqueCodesOutExpected = 4;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 5;
        numUniqueCodesOutExpected = 4;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 6;
        numUniqueCodesOutExpected = 3;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 7;
        numUniqueCodesOutExpected = 2;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 8;
        numUniqueCodesOutExpected = 1;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);

        kIn = 9;
        numUniqueCodesOutExpected = 0;
        numUniqueCodesOutComputed = soln.countNumUniqueCodes(strIn, kIn);
        assert(numUniqueCodesOutExpected == numUniqueCodesOutComputed);
    }

    void testHasAllCodes() {
        Solution soln = Solution();
        string strIn;
        int kIn;
        bool hasAllCodesOutExpected, hasAllCodesOutComputed;

        // empty string
        strIn = "";

        kIn = 0;
        hasAllCodesOutExpected = true;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        kIn = 4;
        hasAllCodesOutExpected = false;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        // non empty string - 1
        strIn = "00110110";

        kIn = 0;
        hasAllCodesOutExpected = true;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        kIn = 1;
        hasAllCodesOutExpected = true;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        kIn = 2;
        hasAllCodesOutExpected = true;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        kIn = 3;
        hasAllCodesOutExpected = false;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        kIn = 4;
        hasAllCodesOutExpected = false;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        // non empty string - 2
        strIn = "0110";

        kIn = 1;
        hasAllCodesOutExpected = true;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);

        kIn = 2;
        hasAllCodesOutExpected = false;
        hasAllCodesOutComputed = soln.hasAllCodes(strIn, kIn);
        assert(hasAllCodesOutExpected == hasAllCodesOutComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testCreateMask();
    test.testExtractBitsNum();
    test.testCountNumUniqueCodes();
    test.testHasAllCodes();

    return 0;
}
