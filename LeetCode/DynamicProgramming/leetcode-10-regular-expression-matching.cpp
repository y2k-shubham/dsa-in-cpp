// LeetCode 10: https://leetcode.com/problems/regular-expression-matching/submissions/
// Tushar Roy: https://www.youtube.com/watch?v=l3hda49XcDE
// the approach is simply bottom up implementation of memoization technique
// discussed in 'regular-expression-matching-2-correct.cpp' at
// https://coderscat.com/leetcode-regular-expression-matching

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isMatch(string, string);
vector <vector <bool> > createMemoMat(string, string);
void initMemoMat(string, vector <vector <bool> >&);
void fillMemoMat(string, string, vector <vector <bool> >&);

int main() {
  assert(isMatch("aa", "a") == false);
  assert(isMatch("aa", "a*") == true);
  assert(isMatch("ab", ".*") == true);
  assert(isMatch("aab", "c*a*b") == true);
  assert(isMatch("mississippi", "mis*is*p*.") == false);
  assert(isMatch("a", "ab*.") == false);
  assert(isMatch("ab", ".*c") == false);

  return 0;
}

// LeetCode total runtime 20 ms, memory 7.2 MB
bool isMatch(string s, string p) {
  vector <vector <bool> > memoMat = createMemoMat(s, p);
  initMemoMat(p, memoMat);
  fillMemoMat(s, p, memoMat);

  return memoMat[p.size()][s.size()];
}

vector <vector <bool> > createMemoMat(string s, string p) {
  /**
   * we are creating the matrix with
   *  - string laid out along columns &
   *  - pattern laid out across rows
   */
  vector <vector <bool> > memoMat(p.size() + 1);

  for (int i = 0; i <= p.size(); i++) {
    vector <bool> memoVec(s.size() + 1, false);
    memoMat[i] = memoVec;
  }

  return memoMat;
}

void initMemoMat(string p, vector <vector <bool> >& memoMat) {
  memoMat[0][0] = true;

  for (int i = 1; i <= p.size(); i++) {
    /**
     * an empty string can't match a non-empty pattern until the pattern ends with
     * a star '*'. And when that happens, whether or not the match succeeds would
     * depend on the match of empty string with prefix of pattern ending 2 chars
     * before the current one (that is ignoring the star & preceding char pair)
     */
    if (p.at(i - 1) == '*') {
      memoMat[i][0] = memoMat[i - 2][0];
    }
  }
}

void fillMemoMat(string s, string p, vector <vector <bool> >& memoMat) {
  /**
   * note that here we fill the matrix column-wise
   *  - for a given prefix of string
   *  - we first determine match status with all prefixes of pattern
   * (rather than other way around)
   */
  for (int j = 1; j <= s.size(); j++) {
    for (int i = 1; i <= p.size(); i++) {
      if ((p.at(i - 1) == '.') || (s.at(j - 1) == p.at(i - 1))) {
        /**
         * simple (non-star) case:
         *  - crr chars of string and pattern match
         *  - or crr char of pattern in dot '.' (which also matches)
         * then the match status would be same as the status obtained
         * by stripping of the crr chars from both string and pattern
         */
        memoMat[i][j] = memoMat[i - 1][j - 1];
      } else if (p.at(i - 1) == '*') {
        /**
         * star case (actual problematic case): entire solution revolves around this
         * 
         * NOTE: (obvious, yet not intuitive)
         * star is always taken into account along with
         * it's parent (preceding) char who's occurences it is qualifying
         */

        /**
         * either we let pattern's char-star pair match empty string
         * (in other words not match anything)
         * then the result is simply the match status of string with pattern with
         * it's current char-star pair stripped
         */
        bool matchesWithStarCharMatchingEmptyString = memoMat[i - 2][j];
        /**
         * otherwise we'll try to consume the current char of string within the
         * pattern's char-star pair. that is, we'll check the match status of
         * current string without the current char with the pattern (which is
         * fine since if crr string char is 'consumed', it can be ignored)
         * 
         * needless to say, that is possible only if
         * pattern's current char (before) star matches with string's current char.
         * 
         * This, in turn, can happen if
         *  - they are identical
         *  - pattern's preceding char is dot '.'
         */
        bool matchesWithCrrCharConsumedInStar = ((p.at(i - 2) == '.') || (p.at(i - 2) == s.at(j - 1))) && memoMat[i][j - 1];

        memoMat[i][j] = matchesWithStarCharMatchingEmptyString || matchesWithCrrCharConsumedInStar;
      }
    }
  }
}
