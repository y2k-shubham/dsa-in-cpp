// LeetCode-763: https://leetcode.com/problems/partition-labels/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildLastIdxVec(string& str) {
        vector<int> lastIdxVec(26, -1);

        for (int i = 0; i < str.size(); i++) {
            lastIdxVec[str.at(i) - 'a'] = i;
        }

        return lastIdxVec;
    }

    int findPartitionEndIdx(
        string& str,
        vector<int>& lastIdxVec,
        int partitionBeginIdx) {
        int len = str.size();

        int i = partitionBeginIdx;
        int partitionEndIdx = lastIdxVec[str.at(i) - 'a'];
        while ((i < len) && (i <= partitionEndIdx)) {
            char ch = str.at(i);
            partitionEndIdx = max(partitionEndIdx, lastIdxVec[ch - 'a']);

            i++;
        }

        return partitionEndIdx;
    }

    vector<int> buildPartitionSizesVec(string& str, vector<int>& lastIdxVec) {
        vector<int> partitionSizes;
        int len = str.size();

        int partitionBeginIdx;
        for (partitionBeginIdx = 0; partitionBeginIdx < len;) {
            int partitionEndIdx = findPartitionEndIdx(str, lastIdxVec, partitionBeginIdx);
            partitionSizes.push_back(partitionEndIdx - partitionBeginIdx + 1);

            partitionBeginIdx = partitionEndIdx + 1;
        }

        // partitionSizes.push_back(len - partitionBeginIdx + 1);
        return partitionSizes;
    }

   public:
    vector<int> partitionLabels(string s) {
        vector<int> lastIdxVec = buildLastIdxVec(s);
        return buildPartitionSizesVec(s, lastIdxVec);
    }
};
