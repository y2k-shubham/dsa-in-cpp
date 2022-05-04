// LeetCode-1679: https://leetcode.com/problems/max-number-of-k-sum-pairs/

// conventional frequency map based solution (implemented here) is trivial;
// but that only lands us in bottom 30 %tile (runtime) & bottom 50 %tile (memory)

#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class Solution {
private:
    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    int countPairs(unordered_map<int, int>& freqMap, int k) {
        int totalNumPairs = 0;

        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            int crrNum = it->first;
            int crrNumFreq = it->second;

            // we could use this slight optimization if map was ordered
            // if (crrNum > k) {
            //     break;
            // }

            if (crrNumFreq <= 0) {
                continue;
            }

            int reqNum = k - crrNum;
            if (freqMap.find(reqNum) != freqMap.end()) {
                // IMPORTANT: handle crrNum = reqNum
                int reqNumFreq = (crrNum == reqNum) ? (freqMap[reqNum] / 2) : freqMap[reqNum];

                int crrNumPairs = min(crrNumFreq, reqNumFreq);
                if (crrNumPairs <= 0) {
                    continue;
                }

                totalNumPairs += crrNumPairs;

                freqMap[crrNum] -= crrNumPairs;
                freqMap[reqNum] -= crrNumPairs;
            }
        }

        return totalNumPairs;
    }

public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap = buildFreqMap(nums);
        return countPairs(freqMap, k);
    }
};
