// can also be categorized as a 'Hashing' problem
// LeetCode-791: https://leetcode.com/problems/custom-sort-string/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/609/week-2-july-8th-july-14th/3813/

#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

class Solution {
   private:
    unordered_map<char, int> buildCharRankMap(string order) {
        unordered_map<char, int> charRankMap;

        for (int i = 0; i < order.size(); i++) {
            char ch = order.at(i);
            // we need not check for repetitions since
            // order string is composed of unique chars
            charRankMap[ch] = i;
        }

        return charRankMap;
    }

    map<int, char> invertCharRankMap(unordered_map<char, int> charRankMap) {
        map<int, char> rankCharMap;

        for (unordered_map<char, int>::iterator it = charRankMap.begin(); it != charRankMap.end(); it++) {
            rankCharMap[it->second] = it->first;
        }

        return rankCharMap;
    }

    unordered_map<char, int> buildCharFreqMap(string str) {
        unordered_map<char, int> charFreqMap;

        for (int i = 0; i < str.size(); i++) {
            charFreqMap[str.at(i)]++;
        }

        return charFreqMap;
    }

   public:
    string customSortString(string order, string str) {
        unordered_map<char, int> charRankMap = buildCharRankMap(order);
        map<int, char> rankCharMap = invertCharRankMap(charRankMap);
        unordered_map<char, int> charFreqMap = buildCharFreqMap(str);

        string customSortString;

        // fill characters in 'order' string (in that same sequence + frequency)
        for (map<int, char>::iterator i = rankCharMap.begin(); i != rankCharMap.end(); i++) {
            char ch = i->second;
            int freq = charFreqMap[ch];

            for (int j = 1; j <= freq; j++) {
                customSortString += ch;
            }
        }

        // fill characters NOT in 'order' (just matching frequency)
        for (unordered_map<char, int>::iterator i = charFreqMap.begin(); i != charFreqMap.end(); i++) {
            char ch = i->first;
            int freq = i->second;

            if (charRankMap.find(ch) == charRankMap.end()) {
                // this char does NOT occur in 'order' string
                for (int j = 1; j <= freq; j++) {
                    customSortString += ch;
                }
            }
        }

        return customSortString;
    }
};
