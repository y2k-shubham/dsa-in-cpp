// LeetCode-948: https://leetcode.com/problems/bag-of-tokens/

#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

public:
    friend class SolutionTest;

    int bagOfTokensScore(vector<int>& tokens, int power) {
        int len = tokens.size();
        if (len == 0) {
            return 0;
        }

        sort(tokens.begin(), tokens.end());
        if (tokens[0] > power) {
            return 0;
        }

        int maxScore = INT_MIN;

        int crrScore = 0;
        int iLo = 0;
        int iHi = len - 1;
        while ((iLo <= (iHi + 1)) && (iLo < len) && (iHi >= 0)) {
            if (power >= tokens[iLo]) {
                if (debug) {
                    printf("\n-------\n");
                    printf("giving tokens[iLo=%d] = %d when power=%d & score=%d\n", iLo, tokens[iLo], power, crrScore);
                }

                power -= tokens[iLo];
                ++crrScore;
                ++iLo;

                maxScore = max(maxScore, crrScore);
                if (debug) {
                    printf("after that iLo=%d, power=%d & score=%d\n", iLo, power, crrScore);
                    printf("\n-------\n");
                }
            } else if (crrScore > 0) {
                if (debug) {
                    printf("\n-------\n");
                    printf("taking tokens[iHi=%d] = %d when power=%d & score=%d\n", iHi, tokens[iHi], power, crrScore);
                }

                power += tokens[iHi];
                --crrScore;
                --iHi;

                if (debug) {
                    printf("after that iHi=%d, power=%d & score=%d\n", iHi, power, crrScore);
                    printf("\n-------\n");
                }
            } else {
                break;
            }
        }

        return maxScore;
    }
};

class SolutionTest {
public:
    void testBagOfTokens() {
        Solution soln = Solution();
        vector<int> tokensIn;
        int powerIn;
        int scoreOutExpected, scoreOutComputed;

        tokensIn = {100};
        powerIn = 50;
        scoreOutExpected = 0;
        scoreOutComputed = soln.bagOfTokensScore(tokensIn, powerIn);
        assert(scoreOutExpected == scoreOutComputed);

        tokensIn = {100, 200};
        powerIn = 150;
        scoreOutExpected = 1;
        scoreOutComputed = soln.bagOfTokensScore(tokensIn, powerIn);
        assert(scoreOutExpected == scoreOutComputed);

//        soln.debug = true;
        tokensIn = {100, 200, 300, 400};
        powerIn = 200;
        scoreOutExpected = 2;
        scoreOutComputed = soln.bagOfTokensScore(tokensIn, powerIn);
        assert(scoreOutExpected == scoreOutComputed);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBagOfTokens();

    return 0;
}
