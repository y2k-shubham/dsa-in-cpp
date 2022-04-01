// LeetCode-541: https://leetcode.com/problems/reverse-string-ii/

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
private:
    string getRevSubstr(string& str, int lo, int hi) {
        int len = hi - lo;
        string subString = str.substr(lo, len);

        reverse(subString.begin(), subString.end());

        return subString;
    }

public:
    string reverseStr(string s, int k) {
        int len = s.size();
        if (len <= k) {
            reverse(s.begin(), s.end());
            return s;
        }

        ostringstream oss;
        for (int i = 0; i < len; i += (2 * k)) {
            int lo = i;
            int hi = lo + k;
            oss << getRevSubstr(s, lo, hi);

            if (hi < len) {
                oss << s.substr(hi, k);
            }
        }

        return oss.str();
    }
};
