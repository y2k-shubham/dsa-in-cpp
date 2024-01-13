// LeetCode-1347: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/

#include <vector>
#include <string>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'z'

class Solution {
private:
    vector<int> createFreqVec(string& str) {
        vector<int> freqVec(END_CHAR + 1, 0);

        for (char ch: str) {
            freqVec[ch]++;
        }

        return freqVec;
    }

    // LC runtime: 56 ms
    int calcExcessFreq(vector<int>& freqVecS, vector<int>& freqVecT) {
        int excessFreq = 0;

        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            int freqS = freqVecS[ch];
            int freqT = freqVecT[ch];

            if (freqS > freqT) {
                excessFreq += freqS - freqT;
            }
        }

        return excessFreq;
    }

public:
    int minSteps(string s, string t) {
        vector<int> freqVecS = createFreqVec(s);
        vector<int> freqVecT = createFreqVec(t);
        return calcExcessFreq(freqVecS, freqVecT);
    }
};
