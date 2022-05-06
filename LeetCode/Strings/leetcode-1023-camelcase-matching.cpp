// LeetCode-1023: https://leetcode.com/problems/camelcase-matching/

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#define BEGIN_UCHAR 'A'
#define END_UCHAR 'Z'

class Solution {
private:
    string extractUpperCaseChars(string& str) {
        ostringstream oss;
        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);
            if ((BEGIN_UCHAR <= ch) && (ch <= END_UCHAR)) {
                oss << ch;
            }
        }

        return oss.str();
    }

    bool isSubsequence(string s, string t) {
        int lenS = s.size();
        int lenT = t.size();

        if (lenS == 0) {
            return true;
        }
        if (lenT < lenS) {
            return false;
        }

        int iS = 0;
        int iT = 0;
        while ((iS < lenS) && (iT < lenT)) {
            if (s.at(iS) == t.at(iT)) {
                iS++;
            }

            iT++;
        }

        return (iS >= lenS);
    }

public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        string patternUpperCaseMask = extractUpperCaseChars(pattern);
        bool patternHasUpperCaseChars = !patternUpperCaseMask.empty();

        int len = queries.size();

        vector<bool> answer(len, false);
        for (int i = 0; i < len; i++) {
            string query = queries[i];

            // this is NOT just an optimization

            // simple subsequence match can't be used as the problem says that
            // only lowercase characters can be inserted. therefore for uppercase
            // characters, we ough to perform this check
            if (patternHasUpperCaseChars) {
                string queryUpperCaseMask = extractUpperCaseChars(query);
                if (patternUpperCaseMask != queryUpperCaseMask) {
                    continue;
                }
            }

            answer[i] = isSubsequence(pattern, query);
        }

        return answer;
    }
};
