// LeetCode-3365: https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map <string, int> splitAndBuildSubstrFreqMap(string& str, int numSplits) {
        int len = str.size();
        int partLen = len / numSplits;

        unordered_map <string, int> freqMap;
        for (int i = 0; i < len; i += partLen) {
            string split = str.substr(i, partLen);
            freqMap[split]++;
        }

        return freqMap;
    }

public:
    bool isPossibleToRearrange(string s, string t, int k) {
        int len = s.size();
        if (len <= 1) {
            return true;
        }

        if (k == 1) {
            return s == t;
        }

        unordered_map <string, int> subStrFreqs = splitAndBuildSubstrFreqMap(s, k);

        int partLen = len / k;
        for (int i = 0; i < len; i += partLen) {
            string crrSubStr = t.substr(i, partLen);

            int subStrRemainingFreqsInS = subStrFreqs[crrSubStr];
            if (subStrRemainingFreqsInS <= 0) {
                return false;
            }

            subStrRemainingFreqsInS--;
            subStrFreqs[crrSubStr] = subStrRemainingFreqsInS;
        }

        return true;
    }
};
