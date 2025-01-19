// LeetCode-1541: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/
// solved after seeing hints; not an easy question

#include <string>
#include <stack>

using namespace std;

#define NULL_CHAR '\0'
#define OPEN_BRACE '('
#define CLOSED_BRACE ')'

class Solution {
public:
    int minInsertions(string str) {
        int len = str.size();
        int numInsertions = 0;
        int numOpenBraces = 0;

        for (int i = 0; i < len; i++) {
            char ch = str.at(i);

            if (ch == OPEN_BRACE) {
                numOpenBraces++;
            }

            if (ch == CLOSED_BRACE) {
                char chNext = (i == (len - 1)) ? NULL_CHAR : str.at(i + 1);
                if (numOpenBraces == 0) {
                    if (chNext == CLOSED_BRACE) {
                        // we have )).. kind of string
                        numInsertions++;
                        i++;
                    } else {
                        // we have ).. kind of string
                        numInsertions += 2;
                    }
                } else {
                    if (chNext == CLOSED_BRACE) {
                        // we have ()).. kind of string
                        numOpenBraces--;
                        i++;
                    } else {
                        // we have ().. kind of string
                        numOpenBraces--;
                        numInsertions++;
                    }
                }
            }
        }

        if (numOpenBraces > 0) {
            numInsertions += 2 * numOpenBraces;
        }

        return numInsertions;
    }
};
