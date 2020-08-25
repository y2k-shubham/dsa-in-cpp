// LeetCode-316: https://leetcode.com/problems/remove-duplicate-letters/
// LeetCode-1081: smallest-subsequence-of-distinct-characters

// very hard problem
// still most likely a better soln exists (need to explore)

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
// comparing iterators https://stackoverflow.com/q/5842647/3679900
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

map<char, vector<int> > buildCharIndMap(string s);
void testBuildCharIndMap();
int findInd(map<int, char>, vector<int>, bool);
void testFindInd();
string buildStr(map<int, char>);
void testBuildStr();
string removeDuplicateLetters(string s);
void testRemoveDuplicateLetters();
map<char, int> buildFreqMapOld(string);
unordered_map<char, int> buildFreqMapNew(string);
string removeDuplicateLettersOld(string);
string removeDuplicateLettersNew(string);
string removeDuplicateLettersArr(string);

int main() {
    testBuildCharIndMap();
    testFindInd();
    testBuildStr();
    testRemoveDuplicateLetters();

    return 0;
}

// wrong soln: from here

void testBuildCharIndMap() {
    string s;
    map<char, vector<int> > outExpected;
    map<char, vector<int> > outComputed;

    s = "";
    outExpected = {};
    outComputed = buildCharIndMap(s);
    assert(outExpected == outComputed);

    s = "g";
    outExpected = {{'g', {0}}};
    outComputed = buildCharIndMap(s);
    assert(outExpected == outComputed);

    s = "pqp";
    outExpected = {{'p', {0, 2}}, {'q', {1}}};
    outComputed = buildCharIndMap(s);
    assert(outExpected == outComputed);

    s = "rashkeqamar";
    outExpected = {
        {'a', {1, 7, 9}},
        {'e', {5}},
        {'h', {3}},
        {'k', {4}},
        {'m', {8}},
        {'r', {0, 10}},
        {'s', {2}},
        {'q', {6}}};
    outComputed = buildCharIndMap(s);
    assert(outExpected == outComputed);

    s = "";
    outExpected = {};
    outComputed = buildCharIndMap(s);
    assert(outExpected == outComputed);

    s = "";
    outExpected = {};
    outComputed = buildCharIndMap(s);
    assert(outExpected == outComputed);
}

map<char, vector<int> > buildCharIndMap(string s) {
    map<char, vector<int> > charIndMap;
    for (int i = i; i < s.size(); i++) {
        char c = s.at(i);
        charIndMap[c].push_back(i);
    }
    return charIndMap;
}

void testFindInd() {
    map<int, char> crrStrMap;
    vector<int> crrCharInds;

    crrStrMap = {};
    crrCharInds = {};
    assert(findInd(crrStrMap, crrCharInds, false) == -1);

    crrStrMap = {};
    crrCharInds = {0};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);

    crrStrMap = {{4, 'c'}, {9, 'm'}};
    crrCharInds = {0, 1, 5, 8, 18, 21};
    // cout << findInd(crrStrMap, crrCharInds, false) << endl;
    assert(findInd(crrStrMap, crrCharInds, false) == 18);

    crrStrMap = {{9, 'm'}, {4, 'c'}};
    crrCharInds = {0, 1, 5, 8, 18, 21};
    assert(findInd(crrStrMap, crrCharInds, false) == 18);

    crrStrMap = {{9, 'm'}, {4, 'c'}};
    crrCharInds = {0, 1, 5, 8, 18};
    assert(findInd(crrStrMap, crrCharInds, false) == 18);

    crrStrMap = {{9, 'm'}, {4, 'c'}};
    crrCharInds = {0, 1, 5, 8};
    assert(findInd(crrStrMap, crrCharInds, false) == 8);

    crrStrMap = {{9, 'm'}, {4, 'c'}};
    crrCharInds = {0, 1, 5, 18};
    assert(findInd(crrStrMap, crrCharInds, false) == 18);

    crrStrMap = {{9, 'm'}, {4, 'c'}};
    crrCharInds = {0, 1};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);

    crrStrMap = {};
    crrCharInds = {0};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);

    crrStrMap = {};
    crrCharInds = {0};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);

    crrStrMap = {};
    crrCharInds = {0};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);

    crrStrMap = {};
    crrCharInds = {0};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);

    crrStrMap = {};
    crrCharInds = {0};
    assert(findInd(crrStrMap, crrCharInds, false) == 0);
}

int findInd(map<int, char> crrStrMap, vector<int> crrCharInds, bool debug) {
    if (crrCharInds.empty()) {
        // error
        return -1;
    } else if (crrStrMap.empty()) {
        // 1st char being assigned, just return index of it's first occurence
        return crrCharInds[0];
    } else {
        int strLo = (*crrStrMap.begin()).first;
        // last element of map https://stackoverflow.com/q/289715/3679900
        int strHi = (*crrStrMap.rbegin()).first;

        int cLo = crrCharInds[0];
        // last element of vector https://stackoverflow.com/q/14275291/3679900
        int cHi = crrCharInds.back();

        if (debug) {
            printf("strLo=%d, strHi=%d\n", strLo, strHi);
            printf("cLo=%d, cHi=%d\n", cLo, cHi);
        }

        // try to pick occurence of char c beyond index strHi
        vector<int>::iterator cLoBeyondRange = upper_bound(crrCharInds.begin(), crrCharInds.end(), strHi);
        if (cLoBeyondRange != crrCharInds.end()) {
            return *cLoBeyondRange;
        } else if (debug) {
            printf("no occurence of c beyond strHi=%d\n", strHi);
        }

        // try to pick greatest (ind) occurence of c within index range (strLo, strHi)
        // but before that check if such an occurence exists
        vector<int>::iterator cLoWithinRange = upper_bound(crrCharInds.begin(), crrCharInds.end(), strLo);
        vector<int>::iterator cHiWithinRange = lower_bound(crrCharInds.begin(), crrCharInds.end(), strHi);
        if (cHiWithinRange == crrCharInds.end()) {
            cHiWithinRange = --crrCharInds.end();
        }
        if (debug) {
            printf("cLoWithinRange=%d, cHiWithinRange=%d\n", *cLoWithinRange, *cHiWithinRange);
            // printf("cHiWithinRange is end = %s\n", ((cHiWithinRange == crrCharInds.end()) ? "true" : "false"));
        }
        // comparing iterators https://stackoverflow.com/q/5842647/3679900
        if (cLoWithinRange != crrCharInds.end() && cHiWithinRange != crrCharInds.end() && distance(cLoWithinRange, cHiWithinRange) >= 0) {
            return *cHiWithinRange;
        }

        // pick the first occurrence of char c
        return cLo;
    }
}

void testBuildStr() {
    map<int, char> indCharMap;

    indCharMap = {};
    assert(buildStr(indCharMap) == "");

    indCharMap = {{5, 'd'}};
    assert(buildStr(indCharMap) == "d");

    indCharMap = {{2, 'k'}, {5, 'd'}, {9, 'a'}};
    assert(buildStr(indCharMap) == "kda");

    indCharMap = {{9, 'a'}, {5, 'd'}, {2, 'k'}};
    assert(buildStr(indCharMap) == "kda");
}

string buildStr(map<int, char> indCharMap) {
    string s;

    for (map<int, char>::iterator i = indCharMap.begin(); i != indCharMap.end(); i++) {
        s = s + (*i).second;
    }

    return s;
}

void testRemoveDuplicateLetters() {
    assert(removeDuplicateLetters("") == "");
    assert(removeDuplicateLetters("a") == "a");
    assert(removeDuplicateLetters("pq") == "pq");
    assert(removeDuplicateLetters("qpq") == "pq");
    assert(removeDuplicateLetters("bcabc") == "abc");
    assert(removeDuplicateLetters("cbacdcbc") == "acdb");
}

string removeDuplicateLettersWrong(string s) {
    map<char, vector<int> > charIndMap = buildCharIndMap(s);
    map<int, char> crrStrMap;

    for (map<char, vector<int> >::iterator i = charIndMap.begin(); i != charIndMap.end(); i++) {
        int ind = findInd(crrStrMap, (*i).second, false);
        crrStrMap[ind] = (*i).first;
    }

    return buildStr(crrStrMap);
}

// wrong soln: till here

// right soln here onwards

// slower

map<char, int> buildFreqMapOld(string s) {
    map<char, int> freqMap;
    for (int i = 0; i < s.size(); i++) {
        char c = s.at(i);
        freqMap[c]++;
    }
    return freqMap;
}

// solution taken from here https://ttzztt.gitbooks.io/lc/content/remove-duplicate-letters.html (Code 2)
// LC: faster than 5.82%
string removeDuplicateLettersOld(string s) {
    map<char, int> freqMap = buildFreqMapOld(s);
    set<char> visited;
    stack<char> stk;

    for (int i = 0; i < s.size(); i++) {
        char cCrr = s.at(i);

        if (visited.find(cCrr) == visited.end()) {
            while (!stk.empty()) {
                char cTop = stk.top();
                if (cTop > cCrr && freqMap[cTop] > 0) {
                    visited.erase(cTop);
                    stk.pop();
                } else {
                    break;
                }
            }

            stk.push(cCrr);
            visited.insert(cCrr);
        }

        freqMap[cCrr]--;
    }

    string minS;
    while (!stk.empty()) {
        minS = minS + stk.top();
        stk.pop();
    }
    reverse(minS.begin(), minS.end());

    return minS;
}

// slow

// right soln here onwards
unordered_map<char, int> buildFreqMapNew(string s) {
    unordered_map<char, int> freqMap;
    for (int i = 0; i < s.size(); i++) {
        char c = s.at(i);
        freqMap[c]++;
    }
    return freqMap;
}

// solution taken from here https://ttzztt.gitbooks.io/lc/content/remove-duplicate-letters.html (Code 2)
// LC: faster than 17.82%
string removeDuplicateLettersNew(string s) {
    unordered_map<char, int> freqMap = buildFreqMapNew(s);
    unordered_set<char> visited;
    stack<char> stk;

    for (int i = 0; i < s.size(); i++) {
        char cCrr = s.at(i);

        if (visited.find(cCrr) == visited.end()) {
            while (!stk.empty()) {
                char cTop = stk.top();
                if (cTop > cCrr && freqMap[cTop] > 0) {
                    visited.erase(cTop);
                    stk.pop();
                } else {
                    break;
                }
            }

            stk.push(cCrr);
            visited.insert(cCrr);
        }

        freqMap[cCrr]--;
    }

    string minS;
    while (!stk.empty()) {
        minS = minS + stk.top();
        stk.pop();
    }
    reverse(minS.begin(), minS.end());

    return minS;
}

// fast
// LC: faster than 28.82%
string removeDuplicateLettersArr(string s) {
    int len = 123;

    // build freqMap
    int freqArr[len];
    memset(freqArr, 0, sizeof(int) * len);

    for (int i = 0; i < s.size(); i++) {
        char c = s.at(i);
        freqArr[c]++;
    }

    // build visited array
    bool visited[len];
    memset(visited, false, sizeof(bool) * len);

    stack<char> stk;
    for (int i = 0; i < s.size(); i++) {
        char cCrr = s.at(i);

        if (visited[cCrr] == false) {
            while (!stk.empty()) {
                char cStk = stk.top();
                if (cStk > cCrr && freqArr[cStk] >= 1) {
                    visited[cStk] = false;
                    stk.pop();
                } else {
                    break;
                }
            }

            stk.push(cCrr);
            visited[cCrr] = true;
        }

        freqArr[cCrr]--;
    }

    // build string
    string minS;
    while (!stk.empty()) {
        minS = minS + stk.top();
        stk.pop();
    }
    reverse(minS.begin(), minS.end());

    return minS;
}

string removeDuplicateLetters(string s) {
    return removeDuplicateLettersArr(s);
}
