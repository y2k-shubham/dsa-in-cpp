// LeetCode-345: https://leetcode.com/problems/reverse-vowels-of-a-string/
// straight-forward easy problem; please skip

#include <cstdio>
#include <iostream>
#include <climits>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set <char> vowels = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'};
    
    int getNextVowelIdx(string& str, int idx) {
        int len = str.size();
        if (len == 0) {
            return INT_MAX;
        }
        
        for (int i = idx; i < len; i++) {
            if (vowels.find(str.at(i)) != vowels.end()) {
                return i;
            }
        }
        
        return INT_MAX;
    }
    
    int getPrevVowelIdx(string& str, int idx) {
        int len = str.size();
        if (len == 0) {
            return INT_MIN;
        }
        
        for (int i = idx; i >= 0; i--) {
            if (vowels.find(str.at(i)) != vowels.end()) {
                return i;
            }
        }
        
        return INT_MIN;
    }
    
    void swapChars(string& str, int idx1, int idx2) {
        char ch = str.at(idx1);
        str[idx1] = str.at(idx2);
        str[idx2] = ch;
    }
    
public:
    string reverseVowels(string s) {
        int len = s.size();
        
        int iLo = getNextVowelIdx(s, 0);
        int iHi = getPrevVowelIdx(s, len - 1);
        while (iLo < iHi) {
            swapChars(s, iLo, iHi);
            
            iLo = getNextVowelIdx(s, iLo + 1);
            iHi = getPrevVowelIdx(s, iHi - 1);
        }
        
        return s;
    }
};

