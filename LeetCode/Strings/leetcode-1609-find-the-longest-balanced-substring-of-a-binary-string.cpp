// LeetCode-1609: https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/

#include <string>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <utility>

using namespace std;

class Solution {
private:
    bool debug = false;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    int swallowNums(string& str, char numToSwallow, int startIdx) {
        int i;
        for (i = startIdx; (i < str.size()) && (str.at(i) == numToSwallow); i++) {
            // do nothing
        }

        return i;
    }

public:
    friend class SolutionTest;

    int findTheLongestBalancedSubstring(string str) {
        int maxBalancedSubstrLen = 0;

        int i = 0;
        while (i < str.size()) {
            if (debug) {
                printf("\n");
            }

            int iNew;

            // swallow 0s
            iNew = swallowNums(str, '0', i);
            int num0sSwallowed = iNew - i;
            if (debug) {
                printf("starting from i=%d, swallowed 0s till iNew=%d, num0sSwallowed=%d\n", i, iNew, num0sSwallowed);
            }

            i = iNew;

            // swallow 0s
            iNew = swallowNums(str, '1', i);
            int num1sSwallowed = iNew - i;
            if (debug) {
                printf("starting from i=%d, swallowed 1s till iNew=%d, num1sSwallowed=%d\n", i, iNew, num1sSwallowed);
            }

            i = iNew;

            int crrBalancedSubstrLen = 2 * min(num0sSwallowed, num1sSwallowed);
            maxBalancedSubstrLen = max(maxBalancedSubstrLen, crrBalancedSubstrLen);
        }

        return maxBalancedSubstrLen;
    }
};

class SolutionTest {
public:
    void testFindTheLongestBalancedSubstring() {
        Solution soln = Solution();
        string strIn;
        int lenOutExpected, lenOutComputed;

        // soln.enableDebug();
        strIn = "01000111";
        lenOutExpected = 6;
        lenOutComputed = soln.findTheLongestBalancedSubstring(strIn);
        assert(lenOutExpected == lenOutComputed);
        // soln.disableDebug();

        // printf("came here 1\n");

        strIn = "00111";
        lenOutExpected = 4;
        lenOutComputed = soln.findTheLongestBalancedSubstring(strIn);
        assert(lenOutExpected == lenOutComputed);

        // printf("came here 2\n");

        strIn = "111";
        lenOutExpected = 0;
        lenOutComputed = soln.findTheLongestBalancedSubstring(strIn);
        assert(lenOutExpected == lenOutComputed);

        // printf("came here 3\n");
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindTheLongestBalancedSubstring();

    return 0;
}
