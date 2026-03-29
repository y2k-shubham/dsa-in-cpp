// LeetCode-2839: https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i

#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
    bool haveSameChars(string& str1, string& str2, int idx) {
        return haveSameChars(str1, str2, idx, idx);
    }

    bool haveSameChars(string& str1, string& str2, int idx1, int idx2) {
        return str1.at(idx1) == str2.at(idx2);
    }

    bool haveSameCharsWithoutSwapping(string& str1, string& str2, int p1, int p2) {
        return haveSameChars(str1, str2, p1) && haveSameChars(str1, str2, p2);
    }

    bool canHaveSameCharsBySwapping(string& str1, string& str2, int idx1, int idx2) {
        return haveSameChars(str1, str2, idx1, idx2) && haveSameChars(str1, str2, idx2, idx1);
    }

public:
    bool canBeEqual(string s1, string s2) {
        // printf("haveSameCharsWithoutSwapping(s1, s2, 0, 2) = %s", (haveSameCharsWithoutSwapping(s1, s2, 0, 2) ? "true" : "false"));
        // cout << endl;
        // printf("canHaveSameCharsBySwapping(s1, s2, 0, 2) = %s", (canHaveSameCharsBySwapping(s1, s2, 0, 2) ? "true" : "false"));
        // cout << endl;
        // printf("haveSameCharsWithoutSwapping(s1, s3, 1, 3) = %s", (haveSameCharsWithoutSwapping(s1, s2, 1, 3) ? "true" : "false"));
        // cout << endl;
        // printf("canHaveSameCharsBySwapping(s1, s3, 1, 3) = %s", (canHaveSameCharsBySwapping(s1, s2, 1, 3) ? "true" : "false"));
        // cout << endl;

        return
            (haveSameCharsWithoutSwapping(s1, s2, 0, 2) || canHaveSameCharsBySwapping(s1, s2, 0, 2))
            && (haveSameCharsWithoutSwapping(s1, s2, 1, 3) || canHaveSameCharsBySwapping(s1, s2, 1, 3));
    }
};
