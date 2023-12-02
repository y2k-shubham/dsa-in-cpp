// LeetCode-2287: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/
// dump problem; dont bother looking
// quite a bit of the code here has been copied from our solution for LeetCode-1160: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/


#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

#define NUM_ALPHABETS 26
#define FIRST_ALPHABET 'a'

class Solution {
private:
    vector<int> buildCharFreqVec(string& chars) {
        vector<int> charFreqVec(NUM_ALPHABETS, 0);
        for (char ch: chars) {
            charFreqVec[ch - FIRST_ALPHABET]++;
        }

        return charFreqVec;
    }

    int countMaxCopies(vector<int>& availableCharFreq, vector<int>& requiredCharFreq) {
        int maxCopies = INT_MAX;
        for (int i = 0; i < NUM_ALPHABETS; i++) {
            if (requiredCharFreq[i] == 0) {
                continue;
            }

            if (availableCharFreq[i] < requiredCharFreq[i]) {
                return 0;
            }

            maxCopies = min(maxCopies, availableCharFreq[i] / requiredCharFreq[i]);
        }

        return maxCopies;
    }

public:
    int rearrangeCharacters(string s, string target) {
        vector<int> availableCharFreqVec = buildCharFreqVec(s);
        vector<int> requiredCharFreqVec = buildCharFreqVec(target);

        return countMaxCopies(availableCharFreqVec, requiredCharFreqVec);
    }
};
