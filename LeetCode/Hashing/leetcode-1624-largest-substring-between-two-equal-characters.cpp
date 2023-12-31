// LeetCode-1624: https://leetcode.com/problems/largest-substring-between-two-equal-characters/

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

#define LAST_CHAR 'z'

class Solution {
private:
    bool debug;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class SolutionTest;

    int maxLengthBetweenEqualCharacters(string s) {
        vector<int> charFirstIdxMap(LAST_CHAR + 1, -1);

        int maxLength = -1;
        for (int i = 0; i < s.size(); i++) {
            // get the character at the current index of the string
            char ch = s.at(i);
            if (debug) {
                printf("\n-------\n");
                printf("at str[i=%d] = '%c'\n", i, ch);
            }

            // find index of first appearance of the character in the string, if any
            int lastIdx = charFirstIdxMap[ch];
            if (lastIdx != -1) {
                if (debug) {
                    printf("last occurrence of '%c' = %d, crrWindowSize = %d\n", ch, lastIdx, (i - lastIdx - 1));
                    if ((i - lastIdx - 1) > maxLength) {
                        printf("updating maxWindowSize from %d to crrWindowSize=%d\n", maxLength, (i - lastIdx - 1));
                    } else {
                        printf("keeping maxWindowSize = %d unchanged\n", maxLength);
                    }
                }

                // if character had appeared earlier, then find the window length & update maxLength
                maxLength = max(maxLength, i - lastIdx - 1);
            } else {
                if (debug) {
                    printf("this is first occurrence of character '%c'\n", ch);
                }

                // update index of first appearance of the character in the string
                charFirstIdxMap[ch] = i;
            }
        }

        return maxLength;
    }
};

class SolutionTest {
public:
    void testMaxLengthBetweenEqualCharacters() {
        Solution soln = Solution();

//        soln.disableDebug();
        assert(soln.maxLengthBetweenEqualCharacters("aa") == 0);
        assert(soln.maxLengthBetweenEqualCharacters("abca") == 2);
        assert(soln.maxLengthBetweenEqualCharacters("cbzxy") == -1);
        assert(soln.maxLengthBetweenEqualCharacters("cabbac") == 4);
        assert(soln.maxLengthBetweenEqualCharacters("cabbacd") == 4);

//        soln.enableDebug();
        assert(soln.maxLengthBetweenEqualCharacters("mgntdygtxrvxjnwksqhxuxtrv") == 18);
//        soln.disableDebug();
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxLengthBetweenEqualCharacters();

    return 0;
}
