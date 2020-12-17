// LeetCode-647: https://leetcode.com/problems/palindromic-substrings/
// GFG-1 https://www.geeksforgeeks.org/count-palindrome-sub-strings-string/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int countSubstrings(string s) {
    int len = s.size();

    vector<vector<bool> > memoMat(len);
    for (int i = 0; i < len; i++) {
        vector<bool> vec(len, false);
        vec[i] = true;
        memoMat[i] = vec;
    }

    int numPalinSubstrings = len;
    int rLo = 0;
    int cHi = len - 1;

    for (int l = 2; l <= len; l++) {
        int rBegin = rLo;
        int cEnd = rBegin + l - 1;

        while (cEnd <= cHi) {
            if (s.at(rBegin) == s.at(cEnd)) {
                if (l == 2 || memoMat[rBegin + 1][cEnd - 1]) {
                    numPalinSubstrings++;
                    memoMat[rBegin][cEnd] = true;
                }
            }

            rBegin++;
            cEnd++;
        }
    }

    return numPalinSubstrings;
}

int main() {
    cout << countSubstrings("abaab") << endl;
    cout << countSubstrings("abbaeae") << endl;
    return 0;
}
