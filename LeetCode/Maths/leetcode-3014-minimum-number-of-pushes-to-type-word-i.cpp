// LeetCode-3014: https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <utility>

#define NUM_KEYS 8

using namespace std;

// Comparator for descending order by second value
struct CompareBySecond {
    bool operator()(const pair<char,int>& a, const pair<char,int>& b) const {
        return a.second < b.second;
        // 'true' means a has lower priority than b
    }
};

class Solution {
private:
    bool debug = false;

    unordered_map<char, int> createCharFreqMap(string word) {
        unordered_map<char, int> charFreqMap;

        for (char ch: word) {
            charFreqMap[ch]++;
        }

        return charFreqMap;
    }

    priority_queue<pair<char,int>, vector<pair<char,int>>, CompareBySecond> buildCharQueByDescreasingFreq(unordered_map<char, int>& charFreqMap) {
        priority_queue<pair<char,int>, vector<pair<char,int>>, CompareBySecond> pQue;

        for (auto it: charFreqMap) {
            pQue.push(make_pair(it.first, it.second));
        }

        return pQue;
    }

    int calculateMinPushes(priority_queue<pair<char,int>, vector<pair<char,int>>, CompareBySecond>& pQue) {
        int totalNumPushes = 0;
        int numDistinctChars = 0;

        while (!pQue.empty()) {
            pair<char,int> p = pQue.top();
            pQue.pop();

            int freq = p.second;
            int numPushesForSingleEntry = (numDistinctChars / NUM_KEYS) + 1;
            int numPushesForFreqEntries = numPushesForSingleEntry * freq;

            totalNumPushes += numPushesForFreqEntries;

            numDistinctChars++;
        }

        return totalNumPushes;
    }

    // ---- debugging ----

    void showCharFreqMap(unordered_map<char, int>& charFreqMap) {
        printf("charFreqMap is:-\n");
        for (auto it: charFreqMap) {
            printf("[%c] -> %d\n", it.first, it.second);
        }
    }

    void showPQue(priority_queue<pair<char,int>, vector<pair<char,int>>, CompareBySecond> pQue) {
        printf("pQue is:-\n");
        while (!pQue.empty()) {
            pair<char,int> p = pQue.top();
            printf("[%c] -> %d\n", p.first, p.second);

            pQue.pop();
        }
    }

public:
    int minimumPushes(string word) {
        int len = word.size();
        if (len <= NUM_KEYS) {
            return len;
        }

        unordered_map<char, int> charFreqMap = createCharFreqMap(word);
        if (debug) {
            showCharFreqMap(charFreqMap);
        }

        priority_queue<pair<char,int>, vector<pair<char,int>>, CompareBySecond> pQue = buildCharQueByDescreasingFreq(charFreqMap);
        if (debug) {
            showPQue(pQue);
        }

        return calculateMinPushes(pQue);
    }
};
