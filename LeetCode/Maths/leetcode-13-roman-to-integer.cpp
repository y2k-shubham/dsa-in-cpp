// LeetCode 13: https://leetcode.com/problems/roman-to-integer/
// https://www.geeksforgeeks.org/converting-roman-numerals-decimal-lying-1-3999/
// https://www.interviewbit.com/problems/roman-to-integer/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

void testFindMaxPrefix();
string findMaxPrefix(map<string, int>, string);
void testRemoveMaxPrefix();
pair<int, string> removeMaxPrefix(map<string, int>, string);
void testRomanToInt();
int romanToInt(string);

int main() {
    testFindMaxPrefix();
    testRemoveMaxPrefix();
    testRomanToInt();

    return 0;
}

map<string, int> createRepNumMap() {
    return {
        {"I", 1},
        {"IV", 4},
        {"V", 5},
        {"IX", 9},
        {"X", 10},
        {"XL", 40},
        {"L", 50},
        {"XC", 90},
        {"C", 100},
        {"CD", 400},
        {"D", 500},
        {"CM", 900},
        {"M", 1000}};
}

void testFindMaxPrefix() {
    map<string, int> repNumMap = createRepNumMap();

    assert(findMaxPrefix(repNumMap, "III") == "I");
    assert(findMaxPrefix(repNumMap, "IV") == "IV");
    assert(findMaxPrefix(repNumMap, "V") == "V");
    assert(findMaxPrefix(repNumMap, "IX") == "IX");
    assert(findMaxPrefix(repNumMap, "X") == "X");
    assert(findMaxPrefix(repNumMap, "LVIII") == "L");
    assert(findMaxPrefix(repNumMap, "MCMXCIV") == "M");
    assert(findMaxPrefix(repNumMap, "CMXCIV") == "CM");
    assert(findMaxPrefix(repNumMap, "XCIV") == "XC");
    assert(findMaxPrefix(repNumMap, "CIV") == "C");
}

string findMaxPrefix(map<string, int> repNumMap, string rep) {
    string maxPrefix;
    for (map<string, int>::iterator i = repNumMap.begin(); i != repNumMap.end(); i++) {
        string prefix = (*i).first;
        if (rep.find(prefix) == 0) {
            if (maxPrefix.size() < prefix.size()) {
                maxPrefix = prefix;
            }
        }
    }
    return maxPrefix;
}

void testRemoveMaxPrefix() {
    pair<int, string> outExpected;
    map<string, int> repNumMap = createRepNumMap();

    outExpected = make_pair(1, "II");
    assert(removeMaxPrefix(repNumMap, "III") == outExpected);

    outExpected = make_pair(4, "");
    assert(removeMaxPrefix(repNumMap, "IV") == outExpected);

    outExpected = make_pair(5, "");
    assert(removeMaxPrefix(repNumMap, "V") == outExpected);

    outExpected = make_pair(9, "");
    assert(removeMaxPrefix(repNumMap, "IX") == outExpected);

    outExpected = make_pair(10, "");
    assert(removeMaxPrefix(repNumMap, "X") == outExpected);

    outExpected = make_pair(50, "VIII");
    assert(removeMaxPrefix(repNumMap, "LVIII") == outExpected);

    outExpected = make_pair(1000, "CMXCIV");
    assert(removeMaxPrefix(repNumMap, "MCMXCIV") == outExpected);

    outExpected = make_pair(900, "XCIV");
    assert(removeMaxPrefix(repNumMap, "CMXCIV") == outExpected);

    outExpected = make_pair(90, "IV");
    assert(removeMaxPrefix(repNumMap, "XCIV") == outExpected);

    outExpected = make_pair(100, "IV");
    assert(removeMaxPrefix(repNumMap, "CIV") == outExpected);
}

pair<int, string> removeMaxPrefix(map<string, int> repNumMap, string rep) {
    pair<int, string> res;

    string maxPrefix = findMaxPrefix(repNumMap, rep);
    res.first = repNumMap[maxPrefix];
    res.second = rep.substr(maxPrefix.size());

    return res;
}

void testRomanToInt() {
    assert(romanToInt("I") == 1);
    assert(romanToInt("II") == 2);
    assert(romanToInt("XLIX") == 49);
    assert(romanToInt("LVIII") == 58);
    assert(romanToInt("CXCIV") == 194);
    assert(romanToInt("MCMXCIV") == 1994);
}

int romanToInt(string rep) {
    map<string, int> repNumMap = createRepNumMap();

    int num = 0;
    while (!rep.empty()) {
        pair<int, string> res = removeMaxPrefix(repNumMap, rep);
        num += res.first;
        rep = res.second;
    }

    return num;
}
