// TusharRoy: https://www.youtube.com/watch?v=3ZDZ-N0EPV0
// https://www.geeksforgeeks.org/wildcard-pattern-matching/
// https://leetcode.com/problems/regular-expression-matching/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isMatch(string, string, bool);
vector<vector<bool> > createMemoMat(string, string);
void initMemoMat(string, vector<vector<bool> >&);
void fillMemoMat(string, string, vector<vector<bool> >&);

int main() {
    bool debug = false;

    // GeeksForGeerks
    assert(isMatch("baaabab", "*****ba*****ab", debug) == true);
    assert(isMatch("baaabab", "baaa?ab", debug) == true);
    assert(isMatch("baaabab", "ba*a?", debug) == true);
    assert(isMatch("baaabab", "a*ab", debug) == false);
    // LeetCode
    assert(isMatch("aa", "a", debug) == false);
    assert(isMatch("aa", "*", debug) == true);
    assert(isMatch("cb", "?a", debug) == false);
    assert(isMatch("adceb", "*a*b", debug) == true);
    assert(isMatch("acdcb", "a*c?b", debug) == false);
    assert(isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b", debug) == false);
    // TLE
    assert(isMatch("babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb", "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a", debug) == false);
    assert(isMatch("babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb", "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a", debug) == false);
    assert(isMatch("babbabbabaaaaabaabaaaaabbabaabbbaaaabbaabbbbbaabbabaabbbbaabbbabaabbaaabbbbabbbabbababaababbaaaaaabaabababbbaaabbaaaaaabbbabbbbabaabaaaabbabbaabaababbaaaababaaaaababbbaabaababbbaaabaababbabbabaaabbbbaa", "*a*ab*b*ab*a*bb**bb**a**abb*bb*ab*a*bbbb***ba***aa**ba*b*ab*ba***aaabbbaa*ba*ba*b****baabb**b*aa*aaab*a", debug) == false);

    return 0;
}

// LeetCode total runtime 308 ms, memory 11.11 MB
bool isMatch(string s, string p, bool debug) {
    vector<vector<bool> > memoMat = createMemoMat(s, p);
    initMemoMat(p, memoMat);
    fillMemoMat(s, p, memoMat);

    return memoMat[p.size()][s.size()];
}

vector<vector<bool> > createMemoMat(string s, string p) {
    /**
   * we are creating the matrix with
   *  - string laid out along columns &
   *  - pattern laid out across rows
   */
    vector<vector<bool> > memoMat(p.size() + 1);

    for (int i = 0; i <= p.size(); i++) {
        vector<bool> memoVec(s.size() + 1, false);
        memoMat[i] = memoVec;
    }

    return memoMat;
}

void initMemoMat(string p, vector<vector<bool> >& memoMat) {
    memoMat[0][0] = true;

    for (int i = 1; i <= p.size(); i++) {
        /**
     * an empty string can't match a non-empty pattern until the pattern is made up
     * of only stars '*'. so whenever a star is encountered, we copy previous value
     * (and previous value itself would be true only if it too had a star)
     */
        if (p.at(i - 1) == '*') {
            memoMat[i][0] = memoMat[i - 1][0];
        }
    }
}

void fillMemoMat(string s, string p, vector<vector<bool> >& memoMat) {
    /**
   * note that here we fill the matrix column-wise
   *  - for a given prefix of string
   *  - we first determine match status with all prefixes of pattern
   * (rather than other way around)
   */
    for (int j = 1; j <= s.size(); j++) {
        for (int i = 1; i <= p.size(); i++) {
            if ((p.at(i - 1) == '?') || (s.at(j - 1) == p.at(i - 1))) {
                /**
         * simple (non-star) case:
         *  - crr chars of string and pattern match
         *  - or crr char of pattern in question-mark '?' (which also matches)
         * then the match status would be same as the status obtained
         * by stripping of the crr chars from both string and pattern
         */
                memoMat[i][j] = memoMat[i - 1][j - 1];
            } else if (p.at(i - 1) == '*') {
                /**
         * star case (actual problematic case): entire solution revolves around this
         */

                /**
         * either we let pattern's star match empty string
         * (in other words not match anything)
         * then the result is simply the match status of string with pattern with
         * it's current star stripped
         */
                bool matchesWithStarCharMatchingEmptyString = memoMat[i - 1][j];
                /**
         * otherwise we'll try to consume the current char of string within the
         * pattern's star. that is, we'll check the match status of
         * 'current string without the current char' with the pattern (which is
         * fine since if crr string char is 'consumed', it can be ignored)
         */
                bool matchesWithCrrCharConsumedInStar = memoMat[i][j - 1];

                memoMat[i][j] = matchesWithStarCharMatchingEmptyString || matchesWithCrrCharConsumedInStar;
            }
        }
    }
}
