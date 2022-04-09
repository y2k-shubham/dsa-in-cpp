// LeetCode-347: https://leetcode.com/problems/top-k-frequent-elements/

#include <unordered_map>
#include <vector>
#include <queue>
#include <map>
//#include <utility>

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

    priority_queue<pair<int, int> > pushValsToHeap(unordered_map<int, int>& mMap) {
        priority_queue<pair<int, int> > maxHeap;

        for (unordered_map<int, int>::iterator it = mMap.begin(); it != mMap.end(); it++) {
            maxHeap.push({it->second, it->first});
        }

        return maxHeap;
    }

    vector<int> retrieveTopKItems(priority_queue<pair<int, int> >& pQue, int k) {
        vector<int> vec(k);

        for (int i = 1; i <= k; i++) {
            vec[i - 1] = pQue.top().second;
            pQue.pop();
        }

        return vec;
    }

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap = buildFreqMap(nums);

        priority_queue<pair<int, int> > freqMaxHeap = pushValsToHeap(freqMap);

        vector<int> topKFreqItems = retrieveTopKItems(freqMaxHeap, k);
        return topKFreqItems;
    }
};
