// LeetCode-1054: https://leetcode.com/problems/distant-barcodes/

#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> createFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    priority_queue<pair<int, int>> createFreqHeap(unordered_map<int, int>& freqMap) {
        int len = freqMap.size();

        vector<pair<int, int>> freqVec(len);
        int i = 0;
        for (unordered_map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            freqVec[i++] = {it->second, it->first};
        }

        priority_queue<pair<int, int>> pQue(freqVec.begin(), freqVec.end());
        return pQue;
    }

   public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int len = barcodes.size();
        if (len <= 1) {
            return barcodes;
        }

        unordered_map<int, int> freqMap = createFreqMap(barcodes);
        priority_queue<pair<int, int>> freqHeap = createFreqHeap(freqMap);

        vector<int> rearrangedBarcodes(len);

        int i = 0;
        int prevItem = INT_MIN;
        while (!freqHeap.empty()) {
            // take highest freq item
            pair<int, int> tuple1 = freqHeap.top();
            int item1 = tuple1.second;
            int freq1 = tuple1.first;
            freqHeap.pop();

            if (item1 == prevItem) {
                // highest freq item can't be placed
                // take 2nd highest freq item
                pair<int, int> tuple2 = freqHeap.top();
                int item2 = tuple2.second;
                int freq2 = tuple2.first;
                freqHeap.pop();

                // put it into output vector
                rearrangedBarcodes[i++] = item2;
                prevItem = item2;

                // put back 2nd highest freq item into heap (if left)
                freq2--;
                if (freq2 > 0) {
                    freqHeap.push({freq2, item2});
                }
            } else {
                // highest freq item can be placed
                // put it into output vector
                rearrangedBarcodes[i++] = item1;
                prevItem = item1;

                freq1--;
            }

            // put back highest freq item into heap (if left)
            if (freq1 > 0) {
                freqHeap.push({freq1, item1});
            }
        }

        return rearrangedBarcodes;
    }
};
