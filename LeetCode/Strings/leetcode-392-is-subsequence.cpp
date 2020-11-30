// LeetCode-392: https://leetcode.com/problems/is-subsequence/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

////////////////
// simple method
////////////////

// simple linear scan soln
// LC-submission speed: 100 %tile, memory: 63 %tile
bool isSubsequenceSimple(string s, string t) {
    int tLen = t.size();
    int sLen = s.size();

    if (tLen > sLen) {
        return false;
    } else if (sLen == 0) {
        return tLen == 0;
    } else if (tLen == 0) {
        return true;
    } else {
        int tInd = 0;
        int sInd = 0;

        while ((sInd < sLen) && (tInd < tLen)) {
            if (s.at(sInd) == t.at(tInd)) {
                sInd++;
            }
            tInd++;
        }

        return (sInd == sLen);
    }
}

/////////////////////////////////////
// optimized (pre-computation) method
/////////////////////////////////////

map<char, vector<int> > createCharIndMap(string str) {
    map<char, vector<int> > charIndMap;

    for (int i = 0; i < str.size(); i++) {
        char c = str.at(i);
        charIndMap[c].push_back(i);
    }

    return charIndMap;
}

void testCreateCharIndMap() {
    string str;
    map<char, vector<int> > charIndMapOutExpected;
    map<char, vector<int> > charIndMapOutComputed;

    str = "";
    charIndMapOutExpected = {};
    charIndMapOutComputed = createCharIndMap(str);
    assert(charIndMapOutExpected == charIndMapOutComputed);

    str = "a";
    charIndMapOutExpected = {{'a', {0}}};
    charIndMapOutComputed = createCharIndMap(str);
    assert(charIndMapOutExpected == charIndMapOutComputed);

    str = "aa";
    charIndMapOutExpected = {{'a', {0, 1}}};
    charIndMapOutComputed = createCharIndMap(str);
    assert(charIndMapOutExpected == charIndMapOutComputed);

    str = "aba";
    charIndMapOutExpected = {{'a', {0, 2}}, {'b', {1}}};
    charIndMapOutComputed = createCharIndMap(str);
    assert(charIndMapOutExpected == charIndMapOutComputed);

    str = "pinoccio";
    charIndMapOutExpected = {{'c', {4, 5}}, {'i', {1, 6}}, {'n', {2}}, {'o', {3, 7}}, {'p', {0}}};
    charIndMapOutComputed = createCharIndMap(str);
    assert(charIndMapOutExpected == charIndMapOutComputed);
}

int findFirstEleIndBeyond(vector<int>& vec, int refEle, int lo, int hi) {
    int crrLen = hi - lo + 1;

    if (crrLen <= 0) {
        return -1;
    } else if (crrLen == 1) {
        if (vec[lo] > refEle) {
            return lo;
        } else {
            return -1;
        }
    } else if (crrLen == 2) {
        if (vec[lo] > refEle) {
            return lo;
        } else if (vec[hi] > refEle) {
            return hi;
        } else {
            return -1;
        }
    } else {
        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        if (midEle <= refEle) {
            return findFirstEleIndBeyond(vec, refEle, mid + 1, hi);
        } else {
            int lRes = findFirstEleIndBeyond(vec, refEle, lo, mid - 1);
            if (lRes >= 0) {
                return lRes;
            } else {
                return mid;
            }
        }
    }
}

void testFindFirstEleIndBeyond() {
    vector<int> vec;
    int lo, hi;
    int refEle;

    vec = {};
    lo = 0, hi = INT_MAX;
    refEle = INT_MIN;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == -1);

    vec = {1};
    lo = 0, hi = 0;
    refEle = INT_MIN;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == 0);

    vec = {INT_MIN + 1, 2};
    lo = 0, hi = 1;
    refEle = INT_MIN;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == 0);

    vec = {INT_MIN, 2};
    lo = 0, hi = 1;
    refEle = INT_MIN;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == 1);

    vec = {INT_MIN, 2};
    lo = 0, hi = 1;
    refEle = 2;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == -1);

    vec = {INT_MIN, 2, 3, 5};
    lo = 0, hi = 3;
    refEle = 2;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == 2);

    vec = {INT_MIN, 2, 3, 5};
    lo = 0, hi = 3;
    refEle = 3;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == 3);

    vec = {INT_MIN, 2, 3, 5};
    lo = 0, hi = 3;
    refEle = 4;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == 3);

    vec = {INT_MIN, 2, 3, 5};
    lo = 0, hi = 3;
    refEle = 5;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == -1);

    vec = {INT_MIN, 2, 3, 5};
    lo = 0, hi = 3;
    refEle = 6;
    assert(findFirstEleIndBeyond(vec, refEle, lo, hi) == -1);
}

bool isSubsequencePreComp(string s, map<char, vector<int> >& charIndMap, string t) {
    int sLen = s.size();
    int tLen = t.size();

    if (tLen > sLen) {
        return false;
    } else if (sLen == 0) {
        return tLen == 0;
    } else if (tLen == 0) {
        return true;
    } else {
        // happy path
        int sInd = -1;
        int tInd = 0;

        while ((tInd < tLen) && (sInd < sLen)) {
            char c = t.at(tInd);

            if (charIndMap.find(c) == charIndMap.end()) {
                return false;
            } else {
                vector<int> indices = charIndMap[c];
                int pickInd = findFirstEleIndBeyond(indices, sInd, 0, (((int)indices.size()) - 1));

                if (pickInd < 0) {
                    return false;
                } else {
                    sInd = indices[pickInd];
                    tInd++;
                }
            }
        }

        return (tInd == tLen);
    }
}

// pre-computation based soln
// LC-submission speed: 24 %tile, memory: 12 %tile
void testIsSubsequencePreComp() {
    string s;
    string t;
    map<char, vector<int> > charIndMap;

    // test-set-1

    s = "";
    charIndMap = createCharIndMap(s);

    t = "";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "p";
    assert(isSubsequencePreComp(s, charIndMap, t) == false);

    // test-set-2

    s = "munchkow";
    charIndMap = createCharIndMap(s);

    t = "";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "mk";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "mkw";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "mkh";
    assert(isSubsequencePreComp(s, charIndMap, t) == false);

    // test-set-3

    s = "pomoegranate";
    charIndMap = createCharIndMap(s);

    t = "pom";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "pmo";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "pomo";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "pegrt";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "pegrnt";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "pgrte";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);

    t = "pgrnte";
    assert(isSubsequencePreComp(s, charIndMap, t) == true);
}

int main() {
    testCreateCharIndMap();
    testFindFirstEleIndBeyond();
    testIsSubsequencePreComp();

    return 0;
}