// LeetCode-2840: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/

#include <string>
#include <vector>
#include <utility>

using namespace std;

#define NUM_CHARS 26
#define START_CHAR 'a'

class Solution {
private:
    vector<int> buildFreqMapAlternateChars(string& str, int startIdx) {
        vector<int> freqMap(NUM_CHARS, 0);
        for (int i = startIdx; i < str.length(); i += 2) {
            freqMap[str[i] - START_CHAR]++;
        }
        return freqMap;
    }

    pair <vector<int>, vector<int>> buildFreqMapsAlternateChars(string& str) {
        return make_pair(
            buildFreqMapAlternateChars(str, 0),
            buildFreqMapAlternateChars(str, 1)
        );
    }

public:
    bool checkStrings(string s1, string s2) {
        return buildFreqMapsAlternateChars(s1) == buildFreqMapsAlternateChars(s2);
    }
};
