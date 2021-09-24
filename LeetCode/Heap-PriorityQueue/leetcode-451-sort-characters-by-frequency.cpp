// LeetCode-451: https://leetcode.com/problems/sort-characters-by-frequency/
// useless problem (dont read)
// Heap can always be substituted with map

#include <cstdio>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <utility>

using namespace std;

class Solution {
   private:
    unordered_map<char, int> buildFreqMap(string str) {
        unordered_map<char, int> freqMap;

        for (int i = 0; i < str.size(); i++) {
            freqMap[str.at(i)]++;
        }

        return freqMap;
    }

    priority_queue<pair<int, char> > buildFreqPQue(unordered_map<char, int>& freqMap) {
        priority_queue<pair<int, char> > pQue;

        for (unordered_map<char, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            pQue.push({it->second, it->first});
        }

        return pQue;
    }

    string buildFreqSortedStr(priority_queue<pair<int, char> >& pQue) {
        ostringstream oss;

        while (!pQue.empty()) {
            pair<int, char> tup = pQue.top();
            pQue.pop();

            string str(tup.first, tup.second);
            oss << str;
        }

        return oss.str();
    }

   public:
    string frequencySort(string s) {
        unordered_map<char, int> freqMap = buildFreqMap(s);

        priority_queue<pair<int, char> > pQue = buildFreqPQue(freqMap);

        return buildFreqSortedStr(pQue);
    }
};
