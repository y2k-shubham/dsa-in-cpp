// LeetCode-2063: https://leetcode.com/problems/vowels-of-all-substrings/

#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    vector<bool> isVowelVec;

    void setVowelIdxs() {
        vector<bool> isVowelVec(150, false);

        isVowelVec['a'] = true;
        isVowelVec['e'] = true;
        isVowelVec['i'] = true;
        isVowelVec['o'] = true;
        isVowelVec['u'] = true;

        this->isVowelVec = isVowelVec;
    }

public:
    long long countVowels(string word) {
        setVowelIdxs();

        int len = word.size();
        long long numVowels = 0;
        for (int i = 0; i < len; i++) {
            if (isVowelVec[word.at(i)]) {
                numVowels += (i + 1) * ((long long) (len - i));
            }
        }

        return numVowels;
    }
};

