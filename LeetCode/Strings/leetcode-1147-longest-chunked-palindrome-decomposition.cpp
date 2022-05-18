// LeetCode-1147: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/

// this is basically brute-force kind of implementation only
// yet not only accepted, it scored 81 %tile on speed & 57 %tile on memory

#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

public:
    friend class SolutionTest;

    int longestDecomposition(string text) {
        int len = text.size();
        if (len <= 1) {
            return len;
        }

        string strLeft;
        string strRight;

        int numParts = 0;

        int iLeft = 0;
        int iRight = len - 1;
        while (iLeft < iRight) {
            strLeft += text.at(iLeft++);
            strRight = text.at(iRight--) + strRight;

            if (strLeft == strRight) {
                numParts += 2;
                strLeft = "";
                strRight = "";
            }
        }

        // strLeft != <empty> means the loop terminated while processing some part of string
        // iLeft == iRight means there's a central character in an odd-length string that has otherwise been de-composed
        if (!strLeft.empty() || (iLeft == iRight)) {
            ++numParts;
        }

        return numParts;
    }
};

class SolutionTest {
public:
    void testLongestDecomposition() {
        Solution soln = Solution();
        string textIn;
        int outExpected, outComputed;

        textIn = "";
        outExpected = 0;
        outComputed = soln.longestDecomposition(textIn);
        assert(outExpected == outComputed);

        textIn = "g";
        outExpected = 1;
        outComputed = soln.longestDecomposition(textIn);
        assert(outExpected == outComputed);

        textIn = "gg";
        outExpected = 2;
        outComputed = soln.longestDecomposition(textIn);
        assert(outExpected == outComputed);

        textIn = "gag";
        outExpected = 3;
        outComputed = soln.longestDecomposition(textIn);
//        cout << outComputed << endl;
        assert(outExpected == outComputed);

        textIn = "ghiabcdefhelloadamhelloabcdefghi";
        outExpected = 7;
        outComputed = soln.longestDecomposition(textIn);
        assert(outExpected == outComputed);

        textIn = "merchant";
        outExpected = 1;
        outComputed = soln.longestDecomposition(textIn);
        assert(outExpected == outComputed);

        textIn = "antaprezatepzapreanta";
        outExpected = 11;
        outComputed = soln.longestDecomposition(textIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testLongestDecomposition();

    return 0;
}
