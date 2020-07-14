// https://www.geeksforgeeks.org/wildcard-pattern-matching/
// https://leetcode.com/problems/wildcard-matching/

// going TLE on LeetCode (with & without simple memoization)

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string simplifyPattern(string);
bool isMatchNormal(string, string, bool);
bool isMatchMemoized(string, string, map<string, bool>&, bool);

int main() {
    bool debug = false;

    // GeeksForGeerks
    assert(simplifyPattern("*****ba*****ab") == "*ba*ab");
    assert(simplifyPattern("baaa?ab") == "baaa?ab");
    assert(simplifyPattern("ba*a?") == "ba*a?");
    assert(simplifyPattern("a*ab") == "a*ab");
    // LeetCode
    assert(simplifyPattern("a") == "a");
    assert(simplifyPattern("*") == "*");
    assert(simplifyPattern("?a") == "?a");
    assert(simplifyPattern("*a*b") == "*a*b");
    assert(simplifyPattern("a*c?b") == "a*c?b");
    assert(simplifyPattern("a*******b") == "a*b");

    // GeeksForGeerks
    assert(isMatchNormal("baaabab", simplifyPattern("*****ba*****ab"), debug) == true);
    assert(isMatchNormal("baaabab", simplifyPattern("baaa?ab"), debug) == true);
    assert(isMatchNormal("baaabab", simplifyPattern("ba*a?"), debug) == true);
    assert(isMatchNormal("baaabab", simplifyPattern("a*ab"), debug) == false);
    // LeetCode
    assert(isMatchNormal("aa", simplifyPattern("a"), debug) == false);
    assert(isMatchNormal("aa", simplifyPattern("*"), debug) == true);
    assert(isMatchNormal("cb", simplifyPattern("?a"), debug) == false);
    assert(isMatchNormal("adceb", simplifyPattern("*a*b"), debug) == true);
    assert(isMatchNormal("acdcb", simplifyPattern("a*c?b"), debug) == false);
    assert(isMatchNormal("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", simplifyPattern("a*******b"), debug) == false);
    // TLE
    // assert(isMatchNormal("babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb", simplifyPattern("b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a"), debug) == false);

    map<string, bool> memoMap;

    // GeeksForGeerks
    assert(isMatchMemoized("baaabab", simplifyPattern("*****ba*****ab"), memoMap, debug) == true);
    memoMap.clear();
    assert(isMatchMemoized("baaabab", simplifyPattern("baaa?ab"), memoMap, debug) == true);
    memoMap.clear();
    assert(isMatchMemoized("baaabab", simplifyPattern("ba*a?"), memoMap, debug) == true);
    memoMap.clear();
    assert(isMatchMemoized("baaabab", simplifyPattern("a*ab"), memoMap, debug) == false);
    memoMap.clear();
    // LeetCode
    assert(isMatchMemoized("aa", simplifyPattern("a"), memoMap, debug) == false);
    memoMap.clear();
    assert(isMatchMemoized("aa", simplifyPattern("*"), memoMap, debug) == true);
    memoMap.clear();
    assert(isMatchMemoized("cb", simplifyPattern("?a"), memoMap, debug) == false);
    memoMap.clear();
    assert(isMatchMemoized("adceb", simplifyPattern("*a*b"), memoMap, debug) == true);
    memoMap.clear();
    assert(isMatchMemoized("acdcb", simplifyPattern("a*c?b"), memoMap, debug) == false);
    memoMap.clear();
    assert(isMatchMemoized("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", simplifyPattern("a*******b"), memoMap, debug) == false);
    memoMap.clear();
    assert(isMatchMemoized("babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb", simplifyPattern("b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a"), memoMap, debug) == false);
    memoMap.clear();
    // TLE
    assert(isMatchMemoized("babbabbabaaaaabaabaaaaabbabaabbbaaaabbaabbbbbaabbabaabbbbaabbbabaabbaaabbbbabbbabbababaababbaaaaaabaabababbbaaabbaaaaaabbbabbbbabaabaaaabbabbaabaababbaaaababaaaaababbbaabaababbbaaabaababbabbabaaabbbbaa", simplifyPattern("*a*ab*b*ab*a*bb**bb**a**abb*bb*ab*a*bbbb***ba***aa**ba*b*ab*ba***aaabbbaa*ba*ba*b****baabb**b*aa*aaab*a"), memoMap, debug) == false);
    memoMap.clear();

    return 0;
}

string simplifyPattern(string p) {
    string sp;
    for (int i = 0; i < p.size();) {
        char c = p.at(i);
        if (c == '*') {
            while (i < p.size() && p.at(i) == '*') {
                i++;
            }
            sp = sp + '*';
        } else {
            sp = sp + c;
            i++;
        }
    }

    return sp;
}

// LeetCode TLE
bool isMatchNormal(string s, string p, bool debug) {
    if (debug) {
        printf("\n---------\n");
        printf("s = '%s', p = '%s'\n", s.c_str(), p.c_str());
    }
    if (p.empty()) {
        if (debug) {
            printf("p is empty, so returning is s is empty = %s", (s.empty() ? "true" : "false"));
        }
        return s.empty();
    } else {
        // check whether current character of string matches with current char of pattern
        bool crrCharMatches = !s.empty() && (s[0] == p[0] || p[0] == '?');
        // check if pattern has a star character
        bool isStar = p[0] == '*';

        if (debug) {
            cout << endl;
            printf("crrCharMatch = %s, isStar = %s\n", (crrCharMatches ? "true" : "false"), (isStar ? "true" : "false"));
        }

        if (isStar) {
            /**
             * if pattern has star, then we branch into following 2 cases
             *  1. jump the current star in pattern
             *     (let star in pattern match empty string)
             *  2. we can consume the current char of string into star of pattern.
             *     technically here also 2 cases arise:
             *     (a) consume current char in string and star in pattern
             *     (b) consume current char in string but do not consume star in pattern
             *     however case (a) above is automatically handled in subsequent recursive
             *     call as case 1. therefore merely making recursive call for case 2.a. suffices
             */
            return isMatchNormal(s, p.substr(1), debug) || (!s.empty() && isMatchNormal(s.substr(1), p, debug));
        } else {
            /**
             * for non-star case, it is imperative that current chars across string and
             * pattern should match (directly or when pattern has a ?).
             *  - if that is the case, we proceed with matching the remaining string & pattern
             *  - or else, we return false
             */
            return crrCharMatches && isMatchNormal(s.substr(1), p.substr(1), debug);
        }
    }
}

// LeetCode TLE
bool isMatchMemoized(string s, string p, map<string, bool>& memoMap, bool debug) {
    if (debug) {
        printf("\n---------\n");
        printf("s = '%s', p = '%s'\n", s.c_str(), p.c_str());
    }

    string memoKey = s + "_" + p;
    if (memoMap.find(memoKey) != memoMap.end()) {
        return memoMap[memoKey];
    } else {
        if (p.empty()) {
            if (debug) {
                printf("p is empty, so returning is s is empty = %s", (s.empty() ? "true" : "false"));
            }
            return s.empty();
        } else {
            // check whether current character of string matches with current char of pattern
            bool crrCharMatches = !s.empty() && (s[0] == p[0] || p[0] == '?');
            // check if pattern has a star character
            bool isStar = p[0] == '*';

            if (debug) {
                cout << endl;
                printf("crrCharMatch = %s, isStar = %s\n", (crrCharMatches ? "true" : "false"), (isStar ? "true" : "false"));
            }

            bool result;
            if (isStar) {
                /**
             * if pattern has star, then we branch into following 2 cases
             *  1. jump the current star in pattern
             *     (let star in pattern match empty string)
             *  2. we can consume the current char of string into star of pattern.
             *     technically here also 2 cases arise:
             *     (a) consume current char in string and star in pattern
             *     (b) consume current char in string but do not consume star in pattern
             *     however case (a) above is automatically handled in subsequent recursive
             *     call as case 1. therefore merely making recursive call for case 2.a. suffices
             */
                result = isMatchMemoized(s, p.substr(1), memoMap, debug) || (!s.empty() && isMatchMemoized(s.substr(1), p, memoMap, debug));
            } else {
                /**
             * for non-star case, it is imperative that current chars across string and
             * pattern should match (directly or when pattern has a ?).
             *  - if that is the case, we proceed with matching the remaining string & pattern
             *  - or else, we return false
             */
                result = crrCharMatches && isMatchMemoized(s.substr(1), p.substr(1), memoMap, debug);
            }

            memoMap[memoKey] = result;
            return result;
        }
    }
}
