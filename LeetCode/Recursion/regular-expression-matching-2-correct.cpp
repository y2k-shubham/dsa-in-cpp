// https://leetcode.com/problems/regular-expression-matching/
// simplified DFS soln explained at https://coderscat.com/leetcode-regular-expression-matching

/*
a ab*
true
*/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isMatch(string, string);

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

bool isMatch(string s, string p) {
  if (p.empty()) {
    return s.empty();
  } else {
    // check whether current character of string matches with current char of pattern
    bool matches = !s.empty() && (s[0] == p[0] || p[0] == '.');
    // check if pattern has a star as next character
    bool isStar = (p.size() >= 2) && p[1] == '*';
    if (isStar) {
      /**
       * if pattern has star, then we branch into following 2 cases
       *  1. jump the current char (and star) in pattern
       *     (let current char & star 'c*' in pattern match empty string)
       *     we do this irrespective of whether or not the current chars in string
       *     and pattern match with one another
       *  2. if current chars in string and pattern match, then we can consume
       *     the current char of string as well. technically here also 2 cases arise:
       *     (a) consume current char (and star) in pattern
       *     (b) do not consume current char (and star) in pattern
       *     however case (a) above is automatically handled in subsequent recursive
       *     call as case 1. therefore merely making recursive call for case 2.a. suffices
       */
      return isMatch(s, p.substr(2)) || (matches && isMatch(s.substr(1), p));
    } else {
      /**
       * for non-star case, it is imperative that current chars across string and
       * pattern should match (directly or when pattern has a dot).
       *  - if that is the case, we proceed with matching the remaining string & pattern
       *  - or else, we return false
       */
      return matches && isMatch(s.substr(1), p.substr(1));
    }
  }
}
