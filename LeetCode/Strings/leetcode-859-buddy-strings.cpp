// LeetCode-859: https://leetcode.com/problems/buddy-strings/
// not that easy, has a little not-very-intuitive edge-cases flavour to it

#include <list>
#include <string>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'z'

class Solution {
private:
    list<int> findMismatchingIndices(string& s, string& goal) {
        list<int> mismatchingIndices;
        for (int i = 0; i < s.length(); i++) {
            if (s.at(i) != goal.at(i)) {
                mismatchingIndices.push_back(i);
            }
        }
        return mismatchingIndices;
    }

    bool hasAtLeastOneCharWithFreqGreaterOrEqualTo2(string& str) {
        vector<int> freqs(END_CHAR + 1, 0);
        for (char ch: str) {
            freqs[ch]++;
            if (freqs[ch] >= 2) {
                return true;
            }
        }

        return false;
    }

public:
    bool buddyStrings(string s, string goal) {
        if (s.size() != goal.size()) {
            return false;
        }

        if (s == goal) {
            return hasAtLeastOneCharWithFreqGreaterOrEqualTo2(s);
        }

        list<int> mismatchingIndicesList = findMismatchingIndices(s, goal);
        if (mismatchingIndicesList.size() > 2) {
            return false;
        }

        pair<int, int> mismatchingIndicesPair = {mismatchingIndicesList.front(), mismatchingIndicesList.back()};
        return (s.at(mismatchingIndicesPair.first) == goal.at(mismatchingIndicesPair.second))
               && (s.at(mismatchingIndicesPair.second) == goal.at(mismatchingIndicesPair.first));
    }
};
