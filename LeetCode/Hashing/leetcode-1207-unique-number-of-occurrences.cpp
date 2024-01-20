// LeetCode-1207: https://leetcode.com/problems/unique-number-of-occurrences
// easy problem; dont bother looking

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_map<int, int> createFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;
        for (auto it = vec.begin(); it != vec.end(); it++) {
            freqMap[*it]++;
        }

        return freqMap;
    }

    bool hasUniqueFreqs(unordered_map<int, int>& freqMap) {
        unordered_set<int> freqVals;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            int freq = it->second;
            if (freqVals.find(freq) != freqVals.end()) {
                return false;
            }

            freqVals.insert(freq);
        }

        return true;
    }

public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> freqMap = createFreqMap(arr);
        return hasUniqueFreqs(freqMap);
    }
};
