// LeetCode-242: https://leetcode.com/problems/valid-anagram/

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<char, int> createCharFreqMap(string s) {
        unordered_map<char, int> charFreqMap;
        for (char c: s) {
            charFreqMap[c]++;
        }

        return charFreqMap;
    }

    bool areIdentical(unordered_map<char, int>& charFreqMap1, unordered_map<char, int>& charFreqMap2) {
        if (charFreqMap1.size() != charFreqMap2.size()) {
            return false;
        }

        for (auto it = charFreqMap1.begin(); it != charFreqMap1.end(); it++) {
            if (charFreqMap2[it->first] != it->second) {
                return false;
            }
        }

        return true;
    }

public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        unordered_map<char, int> charFreqMap1 = createCharFreqMap(s);
        unordered_map<char, int> charFreqMap2 = createCharFreqMap(t);
        return areIdentical(charFreqMap1, charFreqMap2);
    }
};
