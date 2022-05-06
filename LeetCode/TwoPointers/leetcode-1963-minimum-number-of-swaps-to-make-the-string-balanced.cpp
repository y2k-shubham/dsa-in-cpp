// LeetCode-1963: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/

// not very intuitive
// implemented using hints given on LeetCode problem page itself

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    int findOpenBrIdxFromEnd(string& str, int iHi) {
        for (int i = iHi; i >= 0; i--) {
            if (str.at(i) == '[') {
                return i;
            }
        }

        return -1;
    }

    void swapChars(string& str, int idx1, int idx2) {
        char tmp = str.at(idx1);
        str[idx1] = str.at(idx2);
        str[idx2] = tmp;
    }

public:
    friend class SolutionTest;

    int minSwaps(string s) {
        int len = s.size();

        int numSwaps = 0;

        int numOpenBrs = 0;
        int numCloseBrs = 0;

        int iLo = 0;
        int iHi = len - 1;
        while (iLo < iHi) {
            if (debug) {
                cout << endl;
            }
            char ch = s.at(iLo);
            bool isOpenBr = ch == '[';

            if (isOpenBr) {
                ++numOpenBrs;
                if (debug) {
                    printf("found open  bracket at s.at(iLo=%d), numOpenBrs=%d, numCloseBrs=%d, numSwaps=%d\n", iLo,
                           numOpenBrs, numCloseBrs, numSwaps);
                }
            } else {
                ++numCloseBrs;
                if (debug) {
                    printf("found close bracket at s.at(iLo=%d), numOpenBrs=%d, numCloseBrs=%d, numSwaps=%d\n", iLo,
                           numOpenBrs, numCloseBrs, numSwaps);
                }

                if (numCloseBrs > numOpenBrs) {
                    iHi = findOpenBrIdxFromEnd(s, iHi);
                    swapChars(s, iLo, iHi);
                    --iHi; // this can be skipped

                    --numCloseBrs;
                    ++numOpenBrs;

                    ++numSwaps;
                    if (debug) {
                        printf("swapped s.at(iLo=%d) with s.at(iHi=%d), numOpenBrs=%d, numCloseBrs=%d, numSwaps=%d, str=%s\n",
                               iLo, (iHi + 1), numOpenBrs, numCloseBrs, numSwaps, s.c_str());
                    }
                }
            }

            ++iLo; // dont forget this
        }

        return numSwaps;
    }
};

class SolutionTest {
public:
    void testMinSwaps() {
        Solution soln = Solution();
        string strIn;
        int outExpected, outComputed;

        strIn = "][][";
        outExpected = 1;
        outComputed = soln.minSwaps(strIn);
        assert(outExpected == outComputed);

//        soln.debug = true;
        strIn = "]]][[[";
        outExpected = 2;
        outComputed = soln.minSwaps(strIn);
        assert(outExpected == outComputed);
//        soln.debug = false;

        strIn = "[]";
        outExpected = 0;
        outComputed = soln.minSwaps(strIn);
        assert(outExpected == outComputed);

        strIn = "]]][[[";
        outExpected = 2;
        outComputed = soln.minSwaps(strIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinSwaps();

    return 0;
}
