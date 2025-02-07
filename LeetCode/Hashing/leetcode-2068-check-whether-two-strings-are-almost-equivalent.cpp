// LeetCode-2068: https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define LEN 26

class Solution {
private:
    // -------- method-1: using map --------

    unordered_map <char, int> createFreqMap1(string& word) {
        unordered_map <char, int> freqMap;

        for (char ch : word) {
            freqMap[ch]++;
        }

        return freqMap;
    }

    bool method1_map(string& word1, string& word2) {
        unordered_map <char, int> freqMap1 = createFreqMap1(word1);
        unordered_map <char, int> freqMap2 = createFreqMap1(word2);

        for (char ch = 'a'; ch <= 'z'; ch++) {
            int freq1 = freqMap1[ch];
            int freq2 = freqMap2[ch];

            int diff = abs(freq1 - freq2);
            if (diff > 3) {
                return false;
            }
        }

        return true;
    }

    // -------- method-2: using vector --------

    vector <int> createFreqVec2(string& word) {
        vector <int> freqVec('z' + 1, 0);

        for (char ch : word) {
            freqVec[ch]++;
        }

        return freqVec;
    }

    bool method2_vec(string& word1, string& word2) {
        vector <int> freqVec1 = createFreqVec2(word1);
        vector <int> freqVec2 = createFreqVec2(word2);

        for (char ch = 'a'; ch <= 'z'; ch++) {
            int freq1 = freqVec1[ch];
            int freq2 = freqVec2[ch];

            int diff = abs(freq1 - freq2);
            if (diff > 3) {
                return false;
            }
        }

        return true;
    }

public:
    bool checkAlmostEquivalent(string word1, string word2) {
        return method2_vec(word1, word2);
    }
};
