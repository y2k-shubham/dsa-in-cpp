// LeetCode-532: https://leetcode.com/problems/k-diff-pairs-in-an-array/

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   private:
    map<int, int> createFreqMap(vector<int>& vec) {
        map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

   public:
    int findPairs(vector<int>& nums, int k) {
        map<int, int> freqMap = createFreqMap(nums);

        int numPairs = 0;
        if (k == 0) {
            for (map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
                if (it->second > 1) {
                    numPairs += 1;
                }
            }
        } else {
            for (map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
                int minusKFreq = freqMap[it->first - k];
                numPairs += (minusKFreq >= 1) ? 1 : 0;
            }
        }

        return numPairs;
    }
};
