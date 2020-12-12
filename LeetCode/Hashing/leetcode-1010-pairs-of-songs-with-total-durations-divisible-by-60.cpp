// LeetCode-1010: https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/
// Binary-Beast: https://www.youtube.com/watch?v=TzIuVm1npgw

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int numPairsDivisibleBy60(vector<int>& time) {
    unordered_map<int, int> modEleCounts;

    int pairsCount = 0;
    for (int i = 0; i < time.size(); i++) {
        int crrEle = time[i];
        int crrEleRem = crrEle % 60;

        int reqComplementRem = (crrEleRem > 0) ? (60 - crrEleRem) : 0;
        pairsCount += modEleCounts[reqComplementRem];

        modEleCounts[crrEleRem]++;
    }

    return pairsCount;
}
