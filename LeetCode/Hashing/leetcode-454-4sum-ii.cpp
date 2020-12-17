// LeetCode-454: https://leetcode.com/problems/4sum-ii/
// Space: O(n^2), Time: O(n^2) [amortized; otherwise (n^2)logn]

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<int, int> preparePairwiseSumFreqMap(vector<int>& vec1, vector<int>& vec2) {
    unordered_map<int, int> freqMap;

    for (int i = 0; i < vec1.size(); i++) {
        for (int j = 0; j < vec2.size(); j++) {
            freqMap[vec1[i] + vec2[j]]++;
        }
    }

    return freqMap;
}

int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    int numTuples = 0;

    unordered_map<int, int> pairwiseSumFreqMap = preparePairwiseSumFreqMap(A, B);
    for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < D.size(); j++) {
            int crrSum = C[i] + D[j];
            numTuples += pairwiseSumFreqMap[-crrSum];
        }
    }

    return numTuples;
}
