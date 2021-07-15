// LeetCode-40: https://leetcode.com/problems/combination-sum-ii/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>  // for std::accumulate(..) https://stackoverflow.com/a/3221813/3679900
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> buildFreqMap(vector<int> vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    vector<int> findSortedUniqueNums(vector<int> vec) {
        unordered_set<int> mSet(vec.begin(), vec.end());

        vector<int> uniqueVec(mSet.begin(), mSet.end());
        sort(uniqueVec.begin(), uniqueVec.end());

        return uniqueVec;
    }

    vector<int> buildSortedVecFromFreqMap(unordered_map<int, int>& freqMap) {
        int numEles = 0;
        for (unordered_map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
            numEles += i->second;
        }

        vector<int> sortedVec(numEles);
        int idx = 0;
        for (unordered_map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
            int ele = i->first;
            int freq = i->second;

            for (int j = 1; j <= freq; j++) {
                sortedVec[idx++] = ele;
            }
        }

        sort(sortedVec.begin(), sortedVec.end());

        return sortedVec;
    }

    void findCombinations(
        vector<int>& uniqVec,
        unordered_map<int, int>& freqMap,
        int targetSum,
        vector<vector<int>>& combs,
        unordered_map<int, int>& usageMap,
        int crrIdx,
        int crrSum) {
        int len = uniqVec.size();
        if (crrIdx >= len) {
            return;
        }

        if (crrSum > targetSum) {
            return;
        }

        int crrEle = uniqVec[crrIdx];
        int crrEleTotalFreq = freqMap[crrEle];
        for (int freq = 0; freq <= crrEleTotalFreq; freq++) {
            usageMap[crrEle] = freq;
            int newSum = crrSum + (freq * crrEle);

            if (newSum < targetSum) {
                findCombinations(
                    uniqVec,
                    freqMap,
                    targetSum,
                    combs,
                    usageMap,
                    crrIdx + 1,
                    newSum);
            } else if (newSum == targetSum) {
                combs.push_back(buildSortedVecFromFreqMap(usageMap));
            } else {
                break;
            }
        }

        usageMap[crrEle] = 0;
    }

   public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        unordered_map<int, int> freqMap = buildFreqMap(candidates);
        vector<int> uniqVec = findSortedUniqueNums(candidates);

        if (target < uniqVec[0]) {
            // target too small to be achieved
            return {};
        }

        int elesSum = accumulate(candidates.begin(), candidates.end(), 0);
        if (elesSum < target) {
            // target too big to be achieved
            return {};
        }

        vector<vector<int>> combs;
        unordered_map<int, int> usageMap;
        findCombinations(
            uniqVec,
            freqMap,
            target,
            combs,
            usageMap,
            0,
            0);

        return combs;
    }
};
