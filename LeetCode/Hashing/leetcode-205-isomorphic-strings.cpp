// LeetCode-205: https://leetcode.com/problems/isomorphic-strings/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3811/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
   // LC-submission speed: 12 %tile, memory: 6 %tile
    vector<int> reduceToIntVec(string str) {
        int len = str.size();

        vector<int> vec(len);
        unordered_map<char, int> charIdxMap;

        int idx = 0;
        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);
            if (charIdxMap.find(ch) == charIdxMap.end()) {
                charIdxMap[ch] = idx++;
            }

            vec[i] = charIdxMap[ch];
        }

        return vec;
    }

   public:
    bool isIsomorphic(string s, string t) {
        vector<int> vecS = reduceToIntVec(s);
        vector<int> vecT = reduceToIntVec(t);

        return vecS == vecT;
    }
};
