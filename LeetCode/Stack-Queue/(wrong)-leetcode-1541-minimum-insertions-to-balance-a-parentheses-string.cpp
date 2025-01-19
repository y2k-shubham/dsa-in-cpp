// LeetCode-1541: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/
// wrong

#include <string>

using namespace std;

#define OPEN_BRACE '('
#define CLOSED_BRACE ')'

class Solution {
public:
    int minInsertions(string s) {
        int len = s.size();
        int numInsertions = 0;

        int numOpenBraces = 0;
        int numClosedBraces = 0;
        for (int i = 0; i < len; i++) {
            char ch = s.at(i);
            if (ch == OPEN_BRACE) {
                ++numOpenBraces;
            } else if (ch == CLOSED_BRACE) {
                ++numClosedBraces;
            }

            if (ch == CLOSED_BRACE) {
                if (numClosedBraces >= 2) {
                    if (numOpenBraces >= 1) {
                        // happy-case (no insertion): eat 1 open-brace and 2 closed-braces
                        numOpenBraces--;
                        numClosedBraces -= 2;
                    } else {
                        // insert one '(' before it and swallow entire ()) combination
                        numInsertions++;
                        numClosedBraces -= 2;
                    }
                } else if ((numClosedBraces == 1) && (numOpenBraces == 0)) {
                    char chNext = (i == (len - 1)) ? '\0' : s.at(i + 1);
                    if (chNext == CLOSED_BRACE) {
                        /**
                         * we have '))...' kind of string implying that
                         * (a) we need to insert a '(' before it
                         * and (b) we need to consume the 2nd ')' in above
                         */
                        numInsertions++;
                        numClosedBraces--;
                        i++;
                    } else {
                        /**
                         * we have ')..' kind of string implying that
                         * (a) we need to insert a '(' before it and a ')' after it
                         */
                        numInsertions += 2;
                        numClosedBraces--;
                    }
                }
            }
        }

        if (numOpenBraces > 0) {
            if (numClosedBraces == 0) {
                numInsertions += (2 * numOpenBraces);
                numOpenBraces = 0;
            } else if (numClosedBraces == 1) {
                numInsertions++;
                numClosedBraces = 0;
                numOpenBraces--;

                if (numOpenBraces > 0) {
                    numInsertions += (2 * numOpenBraces);
                    numOpenBraces = 0;
                }
            }
        }

        return numInsertions;
    }
};
