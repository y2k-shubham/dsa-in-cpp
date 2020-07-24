// https://www.youtube.com/watch?v=H4VrKHVG5qI
// Goes out of range while calculating hash in LeetCode 28: https://leetcode.com/problems/implement-strstr/submissions/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
#define PRM 101

void testFindHash();
unsigned long long findHash(string);
void testFindNextHash();
unsigned long long findNextHash(unsigned long long, int, char, char);
bool startsWithAt(string, string, int);
void testStartsWithAt();
void testStrStr();
int strStr(string, string);

int main() {
    testFindHash();
    testFindNextHash();
    testStartsWithAt();
    testStrStr();

    return 0;
}

void testFindHash() {
    assert(findHash("") == 0);
    assert(findHash("a") == 97);
    assert(findHash("A") == 65);
    assert(findHash("aa") == 9894);
    assert(findHash("aAb") == 1006360);
    assert(findHash("Abc") == 1019862);
    assert(findHash("bcQ") == 836378);
    assert(findHash("cQj") == 1089586);
    assert(findHash("QjP") == 826867);
}

unsigned long long findHash(string str) {
    unsigned long long hash = 0;
    for (int i = 0; i < str.size(); i++) {
        int ch = (int)str.at(i);
        hash += ch * ((unsigned long long)pow(PRM, i));
    }
    return hash;
}

void testFindNextHash() {
    unsigned long long prevHash;
    unsigned long long newHash;

    prevHash = findHash("aAb");
    newHash = findNextHash(prevHash, 3, 'a', 'c');
    assert(newHash == 1019862);

    prevHash = findHash("Abc");
    newHash = findNextHash(prevHash, 3, 'A', 'Q');
    assert(newHash == 836378);

    prevHash = findHash("bcQ");
    newHash = findNextHash(prevHash, 3, 'b', 'j');
    assert(newHash == 1089586);

    prevHash = findHash("cQj");
    newHash = findNextHash(prevHash, 3, 'c', 'P');
    assert(newHash == 826867);

    prevHash = findHash("b");
    newHash = findNextHash(prevHash, 1, 'b', 'a');
    assert(newHash == 97);
}

unsigned long long findNextHash(unsigned long long crrHash, int len, char outChar, char inChar) {
    unsigned long long newHash = crrHash;
    newHash = newHash - ((int)outChar);
    newHash = newHash / PRM;
    newHash = newHash + ((unsigned long long)(((int)inChar) * pow(PRM, len - 1)));
    return newHash;
}

void testStartsWithAt() {
    assert(startsWithAt("pinchkoo", "", 0) == true);
    assert(startsWithAt("pinchkoo", "", 1) == true);
    assert(startsWithAt("pinchkoo", "", 7) == true);
    assert(startsWithAt("pinchkoo", "", 8) == false);

    assert(startsWithAt("pinchkoo", "p", 0) == true);
    assert(startsWithAt("pinchkoo", "p", 1) == false);
    assert(startsWithAt("pinchkoo", "i", 0) == false);
    assert(startsWithAt("pinchkoo", "i", 1) == true);

    assert(startsWithAt("pinchkoo", "pi", 0) == true);
    assert(startsWithAt("pinchkoo", "chk", 2) == false);
    assert(startsWithAt("pinchkoo", "chk", 3) == true);
    assert(startsWithAt("pinchkoo", "chk", 4) == false);
    assert(startsWithAt("pinchkoo", "chk", 7) == false);
    assert(startsWithAt("pinchkoo", "chk", 11) == false);
}

bool startsWithAt(string haystack, string needle, int ind) {
    if (ind + needle.size() >= haystack.size()) {
        return false;
    } else if (needle.empty()) {
        return true;
    } else {
        for (int i = 0; i < needle.size(); i++) {
            if (haystack.at(ind + i) != needle.at(i)) {
                return false;
            }
        }
        return true;
    }
}

void testStrStr() {
    assert(strStr("", "") == 0);
    assert(strStr("", " ") == -1);
    assert(strStr("a", "") == 0);
    assert(strStr("a", "b") == -1);
    assert(strStr("a", "a") == 0);
    assert(strStr("asdfghjkl", "") == 0);
    assert(strStr("asdfghjkl", "a") == 0);
    assert(strStr("asdfghjkl", "asd") == 0);
    assert(strStr("asdfghjkl", "ads") == -1);
    assert(strStr("asdfghjkl", "ghj") == 4);
    assert(strStr("asdfghjkl", "kj") == -1);
    assert(strStr("asdfghjkl", "jkl") == 6);
    assert(strStr("asdfghjkl", "jklm") == -1);
    // assert(strStr("ababcaababcaabc", "ababcaabc") == 6);
}

int strStr(string haystack, string needle) {
    if (needle.empty()) {
        return 0;
    } else if (haystack.size() < needle.size()) {
        return -1;
    } else {
        int i;
        unsigned long long reqHash = findHash(needle);

        string initString = haystack.substr(0, needle.size());
        unsigned long long hash = findHash(initString);

        if (hash == reqHash) {
            return 0;
        }

        for (i = 1; (i + needle.size() <= haystack.size()) && (hash != reqHash);) {
            char inChar = haystack.at(i + needle.size() - 1);
            char outChar = haystack.at(i - 1);

            hash = findNextHash(hash, needle.size(), outChar, inChar);

            if (hash == reqHash) {
                return i;
            } else {
                i++;
            }
        }

        return -1;
    }
}
