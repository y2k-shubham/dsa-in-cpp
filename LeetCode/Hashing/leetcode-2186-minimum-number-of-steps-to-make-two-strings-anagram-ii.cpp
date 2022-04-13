// LeetCode-2186: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/

#include <vector>
#include <iostream>

using namespace std;

#define NUM_CHARS 26
#define BEGIN_CHAR 'a'
#define END_CHAR 'z'

class Solution {
private:
    vector<int> prepareFreqVec(string& str) {
        vector<int> freqVec(NUM_CHARS, 0);

        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);
            freqVec[ch - BEGIN_CHAR]++;
        }

        return freqVec;
    }

    int calcFreqVecDiff(vector<int>& freqVec1, vector<int>& freqVec2) {
        int diffTotal = 0;

        for (int i = 0; i < freqVec1.size(); i++) {
            int diff = abs(freqVec1[i] - freqVec2[i]);
            diffTotal += diff;
        }

        return diffTotal;
    }

public:
    int minSteps(string s, string t) {
        vector<int> freqVecS = prepareFreqVec(s);
        vector<int> freqVecT = prepareFreqVec(t);
        return calcFreqVecDiff(freqVecS, freqVecT);
    }
};
