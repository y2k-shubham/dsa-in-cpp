// https://leetcode.com/problems/regular-expression-matching/
// simplified DFS soln explained at https://coderscat.com/leetcode-regular-expression-matching

/*
a ab*
true
*/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isMatchNormal(string, string);
bool isMatchMemoized(string, string, map<string, bool>&);

int main() {
    assert(isMatchNormal("aa", "a") == false);
    assert(isMatchNormal("aa", "a*") == true);
    assert(isMatchNormal("ab", ".*") == true);
    assert(isMatchNormal("aab", "c*a*b") == true);
    assert(isMatchNormal("mississippi", "mis*is*p*.") == false);
    assert(isMatchNormal("a", "ab*.") == false);
    assert(isMatchNormal("ab", ".*c") == false);

    map<string, bool> memoMap;
    assert(isMatchMemoized("aa", "a", memoMap) == false);
    assert(isMatchMemoized("aa", "a*", memoMap) == true);
    assert(isMatchMemoized("ab", ".*", memoMap) == true);
    assert(isMatchMemoized("aab", "c*a*b", memoMap) == true);
    assert(isMatchMemoized("mississippi", "mis*is*p*.", memoMap) == false);
    assert(isMatchMemoized("a", "ab*.", memoMap) == false);
    assert(isMatchMemoized("ab", ".*c", memoMap) == false);

    return 0;
}

bool isMatchNormal(string s, string p) {
    if (p.empty()) {
        return s.empty();
    } else {
        // check whether current character of string matches with current char of pattern
        bool crrCharMatches = !s.empty() && (s[0] == p[0] || p[0] == '.');
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
            return isMatchNormal(s, p.substr(2)) || (crrCharMatches && isMatchNormal(s.substr(1), p));
        } else {
            /**
       * for non-star case, it is imperative that current chars across string and
       * pattern should match (directly or when pattern has a dot).
       *  - if that is the case, we proceed with matching the remaining string & pattern
       *  - or else, we return false
       */
            return crrCharMatches && isMatchNormal(s.substr(1), p.substr(1));
        }
    }
}

bool isMatchMemoized(string s, string p, map<string, bool>& memoMap) {
    if (p.empty()) {
        return s.empty();
    } else {
        string memoKey = s + "_" + p;
        // if result already exsits in memoMap, we return it
        if (memoMap.find(memoKey) != memoMap.end()) {
            return memoMap[memoKey];
        } else {
            bool matches = false;

            // check whether current character of string matches with current char of pattern
            bool crrCharMatches = !s.empty() && (s[0] == p[0] || p[0] == '.');
            // check if pattern has a star as next character
            bool isStar = (p.size() >= 2) && p[1] == '*';
            if (isStar) {
                matches = isMatchMemoized(s, p.substr(2), memoMap) || (crrCharMatches && isMatchMemoized(s.substr(1), p, memoMap));
            } else {
                matches = crrCharMatches && isMatchMemoized(s.substr(1), p.substr(1), memoMap);
            }

            memoMap[memoKey] = matches;
            return matches;
        }
    }
}
