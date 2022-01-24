// LeetCode-520: https://leetcode.com/problems/detect-capital/

#include <cstdio>
#include <iostream>

using namespace std;

#define pBool(mBool) (mBool ? "true" : "false")

class Solution {
   public:
    bool detectCapitalUse(string word) {
        if (word.size() <= 1) {
            return true;
        } else {
            bool firstCap = ('A' <= word.at(0)) && (word.at(0) <= 'Z');

            bool hasCap = false;
            bool hasSmall = false;
            for (int i = 1; i < word.size(); i++) {
                char ch = word.at(i);
                if ('A' <= ch && ch <= 'Z') {
                    hasCap = true;
                } else {
                    hasSmall = true;
                }

                // printf("at s[%d] = '%c', firstCap = %s, hasCap = %s, hasSmall = %s\n", i, ch, pBool(firstCap), pBool(hasCap), pBool(hasSmall));
                if ((hasCap && hasSmall) || (!firstCap && hasCap)) {
                    return false;
                }
            }

            return true;
        }
    }
};
