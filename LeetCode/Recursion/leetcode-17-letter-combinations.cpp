// LeetCode 17: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// https://www.geeksforgeeks.org/iterative-letter-combinations-of-a-phone-number/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<char, set<char> > buildNumCharsetMap();
void showNumCharsetMap(map<char, set<char> >);
vector<string> letterCombinations(string);
void findCombs(string, map<char, set<char> >, set<string>&, string);
void showSet(set<string>);

int main() {
    vector<string> result;

    result = {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    assert(letterCombinations("23") == result);

    result = {"w", "x", "y", "z"};
    assert(letterCombinations("9") == result);

    return 0;
}

map<char, set<char> > buildNumCharsetMap() {
    // g++ -std=c++11 LeetCode/Recursion/letter-combinations.cpp
    // initialize set using C++11: https://stackoverflow.com/a/12333803/3679900
    // intiialize map using C++11: https://stackoverflow.com/a/138612/3679900
    map<char, set<char> > numCharsetMap = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}};
    return numCharsetMap;
}

void showNumCharsetMap(map<char, set<char> > numCharsetMap) {
    for (map<char, set<char> >::iterator it = numCharsetMap.begin(); it != numCharsetMap.end(); it++) {
        printf("%c -> [", (*it).first);
        set<char> charset = (*it).second;
        for (set<char>::iterator jt = charset.begin(); jt != charset.end(); jt++) {
            printf("%c, ", *jt);
        }
        printf("]\n");
    }
}

vector<string> letterCombinations(string digits) {
    map<char, set<char> > numCharsetMap = buildNumCharsetMap();
    // showNumCharsetMap(numCharsetMap);

    set<string> letterCombsSet;
    findCombs(digits, numCharsetMap, letterCombsSet, "");
    // showSet(letterCombsSet);

    vector<string> letterCombsVec(letterCombsSet.begin(), letterCombsSet.end());
    return letterCombsVec;
}

void findCombs(
    string digits,
    map<char, set<char> > numCharsetMap,
    set<string>& letterCombs,
    string crrComb) {
    // printf("\n------\n");
    // printf("digits = %s, crrComb = %s\n", digits.c_str(), crrComb.c_str());

    // these two nested if blocks should NOT be combined via &&
    if (digits.empty()) {
        if (!crrComb.empty()) {
            letterCombs.insert(crrComb);
        }
    } else {
        char crrDig = digits[0];
        set<char> crrCharset = numCharsetMap[crrDig];
        for (set<char>::iterator i = crrCharset.begin(); i != crrCharset.end(); i++) {
            findCombs(digits.substr(1), numCharsetMap, letterCombs, crrComb + *i);
        }
    }
}

void showSet(set<string> mSet) {
    printf("\nset is: ");
    for (set<string>::iterator it = mSet.begin(); it != mSet.end(); it++) {
        cout << *it << "\t";
    }
    cout << endl;
}
