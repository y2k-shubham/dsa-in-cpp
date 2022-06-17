// LeetCode-387: https://leetcode.com/problems/first-unique-character-in-a-string/

#include <vector>
#include <climits>
#include <string>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'z'

class Solution {
public:
    int firstUniqChar(string s) {
        int numChars = END_CHAR - BEGIN_CHAR + 1;

        vector<bool> hasOccurred(END_CHAR + 1, false);
        vector<bool> isNonRepeating(END_CHAR + 1, true);
        vector<int> firstIdx(END_CHAR + 1, INT_MAX);

        for (int i = 0; i < s.size(); i++) {
            char ch = s.at(i);

            if (hasOccurred[ch]) {
                isNonRepeating[ch] = false;
            } else {
                hasOccurred[ch] = true;
                firstIdx[ch] = i;
            }
        }

        int firstNonRepeatingIdx = INT_MAX;
        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            if (isNonRepeating[ch]) {
                firstNonRepeatingIdx = min(firstNonRepeatingIdx, firstIdx[ch]);
            }
        }

        if (firstNonRepeatingIdx == INT_MAX) {
            return -1;
        } else {
            return firstNonRepeatingIdx;
        }
    }
};
