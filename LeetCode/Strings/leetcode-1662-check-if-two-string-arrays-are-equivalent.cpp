// LeetCode-1662: https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/
// lame question

#include <vector>
#include <sstream>

using namespace std;

class Solution {
private:
    string concatStrs(vector<string>& words) {
        ostringstream oss;
        for (vector<string>::iterator w = words.begin(); w != words.end(); w++) {
            oss << *w;
        }

        return oss.str();
    }

public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        return concatStrs(word1) == concatStrs(word2);
    }
};
