// LeetCode-2423: https://leetcode.com/problems/remove-letter-to-equalize-frequency/
// incomplete
// simple but frustrating problem: too many edge cases

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'z'

class Solution {
private:
    vector <int> createFreqVec(string& word) {
        vector <int> freqVec(END_CHAR + 1, 0);

        for (char ch : word) {
            freqVec[ch]++;
        }

        return freqVec;
    }

    unordered_map <int, int> createFreqFreqMap(vector <int>& freqVec) {
        unordered_map <int, int> freqFreqMap;

        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            int freq = freqVec[ch];
            if (freq > 0) {
                freqFreqMap[freq]++;
            }
        }

        return freqFreqMap;
    }

    unordered_map <int, int> filterFreqsWithFreqEqualTo1(unordered_map <int, int>& freqFreqMap) {
        unordered_map <int, int> filteredFreqFreqMap;

        for (auto it = freqFreqMap.begin(); it != freqFreqMap.end(); it++) {
            if (it->second == 1) {
                filteredFreqFreqMap[it->first] = it->second;
            }
        }

        return filteredFreqFreqMap;
    }

public:
    bool equalFrequency(string word) {
        vector <int> freqVec = createFreqVec(word);

        unordered_map <int, int> freqFreqMap = createFreqFreqMap(freqVec);
        if (freqFreqMap.size() == 1) {
            // if all frequencies already match, then they should all be equal to 1
            // so that they continue to match post removal of any one character
            return (freqFreqMap.begin()->first == 1);
        }
        if (freqFreqMap.size() != 2) {
            return false;
        }

        unordered_map <int, int> filteredFreqFreqMap = filterFreqsWithFreqEqualTo1(freqFreqMap);
        if (filteredFreqFreqMap.size() != 1) {
            return false;
        }

        int filteredFreq = filteredFreqFreqMap.begin()->first;
        if (freqFreqMap[filteredFreq - 1] <= 0) {
            return false;
        }

        return true;
    }
};
