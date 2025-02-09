// LeetCode-692: https://leetcode.com/problems/top-k-frequent-words/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map <string, int> buildFreqMap(vector <string>& words) {
        unordered_map <string, int> freqMap;

        for (string word : words) {
            freqMap[word]++;
        }

        return freqMap;
    }

    vector <pair <int, string>> convertToPairVec(unordered_map <string, int>& freqMap) {
        int len = freqMap.size();
        vector <pair <int, string>> pairVec(len);

        int i = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            pairVec[i++] = {-it->second, it->first};
        }

        return pairVec;
    }

    vector <string> getFirstKWords(vector <pair <int, string>>& pairVec, int k) {
        vector <string> firstKWords(k);

        for (int i = 0; i < k; i++) {
            firstKWords[i] = pairVec[i].second;
        }

        return firstKWords;
    }

public:
    vector <string> topKFrequent(vector <string>& words, int k) {
        if (k >= words.size()) {
            sort(words.begin(), words.end());
            return words;
        }

        unordered_map <string, int> freqMap = buildFreqMap(words);

        vector <pair <int, string>> pairVec = convertToPairVec(freqMap);
        sort(pairVec.begin(), pairVec.end());

        return getFirstKWords(pairVec, k);
    }
};
