// LeetCode-1768: https://leetcode.com/problems/merge-strings-alternately/

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();

        ostringstream oss;
        int i1 = 0;
        int i2 = 0;

        // pick one character from word1 & word2 alternatively
        while ((i1 < len1) && (i2 < len2)) {
            char ch1 = word1.at(i1);
            oss << ch1;
            i1++;

            char ch2 = word2.at(i2);
            oss << ch2;
            i2++;
        }

        // pick all remaining characters from word1
        while (i1 < len1) {
            char ch1 = word1.at(i1);
            oss << ch1;
            i1++;
        }

        // pick all remaining characters from word2
        while (i2 < len2) {
            char ch2 = word2.at(i2);
            oss << ch2;
            i2++;
        }

        return oss.str();
    }
};
