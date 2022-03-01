// LeetCode-1657: https://leetcode.com/problems/determine-if-two-strings-are-close/

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Solution {
   private:
    unordered_map<char, int> buildFreqMap(string& str) {
        unordered_map<char, int> freqMap;

        for (int i = 0; i < str.size(); i++) {
            freqMap[str.at(i)]++;
        }

        return freqMap;
    }

    unordered_map<int, list<char> > invertMap(unordered_map<char, int>& orgMap) {
        unordered_map<int, list<char> > invertedMap;

        for (
            unordered_map<char, int>::iterator it = orgMap.begin();
            it != orgMap.end();
            it++) {
            invertedMap[it->second].push_back(it->first);
        }

        return invertedMap;
    }

    // both strings have same set of characters
    bool haveSameChars(
        unordered_map<char, int>& freqMap1,
        unordered_map<char, int>& freqMap2) {
        if (freqMap1.size() != freqMap2.size()) {
            return false;
        }

        for (
            unordered_map<char, int>::iterator it = freqMap1.begin();
            it != freqMap1.end();
            it++) {
            if (freqMap2[it->first] == 0) {
                return false;
            }
        }

        for (
            unordered_map<char, int>::iterator it = freqMap2.begin();
            it != freqMap2.end();
            it++) {
            if (freqMap1[it->first] == 0) {
                return false;
            }
        }

        return true;
    }

    // frequency distribution curves of (characters of) both strings are same
    bool haveSameShapes(
        unordered_map<int, list<char> >& mMap1,
        unordered_map<int, list<char> >& mMap2) {
        if (mMap1.size() != mMap2.size()) {
            return false;
        }

        for (
            unordered_map<int, list<char> >::iterator it = mMap1.begin();
            it != mMap1.end();
            it++) {
            if (it->second.size() != mMap2[it->first].size()) {
                return false;
            }
        }

        return true;
    }

   public:
    bool closeStrings(string word1, string word2) {
        unordered_map<char, int> freqMap1 = buildFreqMap(word1);
        unordered_map<char, int> freqMap2 = buildFreqMap(word2);

        unordered_map<int, list<char> > invertedFreqMap1 = invertMap(freqMap1);
        unordered_map<int, list<char> > invertedFreqMap2 = invertMap(freqMap2);

        return haveSameChars(freqMap1, freqMap2) && haveSameShapes(invertedFreqMap1, invertedFreqMap2);
    }
};
