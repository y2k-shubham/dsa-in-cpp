// LeetCode-1370: https://leetcode.com/problems/increasing-decreasing-string/
// incomplete

#include <cstdio>
#include <map>
#include <sstream>

using namespace std;

#define NULL_CHAR '\0'

class Solution {
private:
    map<char, int> buildFreqMap(string& str) {
        map<char, int> freqMap;

        for (int i = 0; i < str.size(); i++) {
            freqMap[str.at(i)]++;
        }

        return freqMap;
    }

    char extractChar(map<char, int>& freqMap, map<char, int>::iterator it) {
        char ch = it->first;

        freqMap[ch]--;
        if (freqMap[ch] == 0) {
            freqMap.erase(ch);
        }

        return ch;
    }

    char getSmallestChar(map<char, int>& freqMap) {
        if (freqMap.empty()) {
            return NULL_CHAR;
        }

        return extractChar(freqMap, freqMap.begin());
    }

    char get2ndSmallestChar(map<char, int>& freqMap) {
        if (freqMap.empty()) {
            return NULL_CHAR;
        }
        if (freqMap.size() == 1) {
            return getSmallestChar(freqMap);
        }

        auto it = freqMap.begin();
        it++;
        return extractChar(freqMap, it);
    }

    char getBiggestChar(map<char, int>& freqMap) {
        if (freqMap.empty()) {
            return NULL_CHAR;
        }

        auto it = freqMap.end();
        it--;
        return extractChar(freqMap, it);
    }

    char get2ndBiggestChar(map<char, int>& freqMap) {
        if (freqMap.empty()) {
            return NULL_CHAR;
        }
        if (freqMap.size() == 1) {
            return getSmallestChar(freqMap);
        }

        auto it = freqMap.end();
        it--;
        it--;
        return extractChar(freqMap, it);
    }

public:
    string sortString(string s) {
        map<char, int> freqMap = buildFreqMap(s);

        ostringstream oss;
        while (!freqMap.empty()) {
            oss << getSmallestChar(freqMap);
        }
    }
};

