// LeetCode-97: https://leetcode.com/problems/interleaving-string/
// wrong: can't be done using backtracking

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    int findCommonPrefixLen(string& str1, int i1, string& str2, int i2) {
        int len = 0;

        int len1 = str1.size();
        int len2 = str2.size();
        while ((i1 < len1) && (i2 < len2) && (str1.at(i1) == str2.at(i2))) {
            i1++;
            i2++;

            len++;
        }

        return len;
    }

    bool isInterleaveBacktrack(
            string str,
            int i,
            string& str1,
            int i1,
            string& str2,
            int i2
    ) {
        int len = str.size();
        int len1 = str1.size();
        int len2 = str2.size();

        printf("at str[i=%d]=%c, str1[i1=%d]=%c, str2[i2=%d]=%c\n", i, str.at(i), i1, str1.at(i1), i2, str2.at(i2));

        if (((len1 + len2) != len) || (len1 - i1 + len2 - i2 != len - i)) {
            return false;
        }

        int prefLen1 = (i1 >= len1) ? 0 : findCommonPrefixLen(str1, i1, str, i);
        int prefLen2 = (i2 >= len2) ? 0 : findCommonPrefixLen(str2, i2, str, i);
        if (prefLen1 > prefLen2) {
            return isInterleaveBacktrack(str, i + prefLen1, str1, i1 + prefLen1, str2, i2);
        } else if (prefLen1 < prefLen2) {
            return isInterleaveBacktrack(str, i + prefLen2, str1, i1, str2, i2 + prefLen2);
        } else if (max(prefLen1, prefLen2) > 0) {
            return isInterleaveBacktrack(str, i + prefLen1, str1, i1 + prefLen1, str2, i2) ||
                   isInterleaveBacktrack(str, i + prefLen1, str1, i1, str2, i2 + prefLen2);
        } else {
            return i >= len;
        }
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        return isInterleaveBacktrack(s3, 0, s1, 0, s2, 0);
    }
};
