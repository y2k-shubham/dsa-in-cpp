// LeetCode-67: https://leetcode.com/problems/add-binary/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
   public:
    string addBinary(string a, string b) {
        int lenA = a.size();
        int lenB = b.size();

        ostringstream oss;
        int iA = lenA - 1;
        int iB = lenB - 1;
        int carry = 0;
        while ((carry > 0) || (max(iA, iB) >= 0)) {
            int bitA = (iA >= 0) ? (a.at(iA) - '0') : 0;
            int bitB = (iB >= 0) ? (b.at(iB) - '0') : 0;

            int sum = bitA + bitB + carry;
            int rem = sum % 2;
            carry = sum / 2;

            oss << rem;

            iA--;
            iB--;

            // printf("iA=%d, iB=%d, carry=%d, oss=%s\n", iA, iB, carry, oss.str().c_str());
        }

        string binarySum = oss.str();
        reverse(binarySum.begin(), binarySum.end());

        return binarySum;
    }
};
