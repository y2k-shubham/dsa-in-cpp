// LeetCode-350: https://leetcode.com/problems/intersection-of-two-arrays-ii/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
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

    unordered_map<int, int> buildIntersectFreqMap(
        unordered_map<int, int>& freqMap1,
        unordered_map<int, int>& freqMap2) {
        unordered_map<int, int> intersectFreqMap;
        for (unordered_map<int, int>::iterator it = freqMap1.begin(); it != freqMap1.end(); it++) {
            int ele = it->first;
            int freq1 = it->second;
            int freq2 = freqMap2[ele];

            int minFreq = min(freq1, freq2);
            if (minFreq > 0) {
                intersectFreqMap[ele] = minFreq;
            }
        }

        return intersectFreqMap;
    }

    vector<int> buildExplodedVec(unordered_map<int, int>& freqMap) {
        int totalEles = 0;
        for (unordered_map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            int freq = it->second;
            totalEles += freq;
        }

        vector<int> vec(totalEles);
        int i = 0;
        for (unordered_map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            int ele = it->first;
            int freq = it->second;

            for (int j = 1; j <= freq; j++) {
                vec[i++] = ele;
            }
        }

        return vec;
    }

   public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> freqMap1 = buildFreqMap(nums1);
        unordered_map<int, int> freqMap2 = buildFreqMap(nums2);

        unordered_map<int, int> intersectFreqMap = buildIntersectFreqMap(freqMap1, freqMap2);

        vector<int> vec = buildExplodedVec(intersectFreqMap);
        return vec;
    }
};
