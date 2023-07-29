// LeetCode-7: https://leetcode.com/problems/reverse-integer/
// incomplete (wrong answer)

/**
 * 0, INT_MAX & INT_MIN are passing
 *
 * Failing test-case
 * -2147483412
 * Expected output
 * -2143847412
 * Actual output
 * 0
 */

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    int countDigits(int n) {
        int numDigits = 0;
        while (n > 0) {
            n /= 10;
            numDigits++;
        }

        return numDigits;
    }

    vector<int> numToRevVec(int num) {
        vector<int> digVec;

        while (num > 0) {
            digVec.push_back(num % 10);
            num /= 10;
        }

        return digVec;
    }

    int digVecToNum(vector<int>& digVec) {
        int num = 0;

        for (int i = 0; i < digVec.size(); i++) {
            num *= 10;
            num += digVec[i];
        }

        return num;
    }

    void showVec(vector<int>& vec, const char* name) {
        printf("%s vec is:-\n", name);
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    bool isDigVecGreater(vector<int>& digVecToCompare, vector<int>& digVecCompareWith) {
        // showVec(digVecToCompare, "digVecToCompare");
        // showVec(digVecCompareWith, "digVecCompareWith");

        int len1 = digVecToCompare.size();
        int len2 = digVecCompareWith.size();

        if (len1 > len2) {
            // printf("early return 1\n");
            return true;
        }
        if (len1 < len2) {
            // printf("early return 2\n");
            return false;
        }

        for (int i = 0; i < len1; i++) {
            if (digVecToCompare[i] > digVecCompareWith[i]) {
                // printf("returning at digVecToCompare[i=%d]=%d > digVecCompareWith[i=%d]=%d\n", i, digVecToCompare[i], i, digVecCompareWith[i]);
                return true;
            }
        }

        // printf("returning false\n");
        return false;
    }

    vector<int> getReversedVec(vector<int>& vec) {
        int len = vec.size();
        vector<int> revVec(len);

        for (int i = 0; i < len; i++) {
            revVec[len - i - 1] = vec[i];
        }

        return revVec;
    }

public:
    int reverse(int x) {
        bool isNegative = x < 0;

        vector<int> xDigVec = numToRevVec(abs(x));
        vector<int> digVec_INT_MAX = numToRevVec(INT_MAX);
        vector<int> revDigVec_INT_MAX = getReversedVec(digVec_INT_MAX);

        if (isDigVecGreater(xDigVec, revDigVec_INT_MAX)) {
            return 0;
        }

        int revX = digVecToNum(xDigVec);
        return isNegative ? -revX : revX;
    }
};

