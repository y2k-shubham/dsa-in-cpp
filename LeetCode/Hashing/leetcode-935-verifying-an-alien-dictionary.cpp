// LeetCode-935: https://leetcode.com/problems/verifying-an-alien-dictionary/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3702/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<char, int> charRankMap;

    void buildCharRankMap(string order) {
        for (int i = 0; i < order.size(); i++) {
            char ch = order.at(i);
            this->charRankMap[ch] = i;
        }
    }

    int getRank(char ch) {
        return this->charRankMap[ch];
    }

    int compareWords(string word1, string word2) {
        if (word1 == word2) {
            return 0;
        }

        int len1 = word1.size();
        int len2 = word2.size();

        int i = 0;
        while (i < min(len1, len2)) {
            char ch1 = word1.at(i);
            char ch2 = word2.at(i);

            int rank1 = getRank(ch1);
            int rank2 = getRank(ch2);

            if (rank1 < rank2) {
                return -1;
            }
            if (rank1 > rank2) {
                return 1;
            }

            i++;
        }

        if (i < len1) {
            return 1;
        }
        if (i < len2) {
            return -1;
        }
        return 0;
    }

   public:
    bool isAlienSorted(vector<string>& words, string order) {
        buildCharRankMap(order);

        for (int i = 1; i < words.size(); i++) {
            string word1 = words[i - 1];
            string word2 = words[i];

            if (compareWords(word1, word2) > 0) {
                return false;
            }
        }

        return true;
    }
};
