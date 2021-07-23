// LeetCode-1338: https://leetcode.com/problems/reduce-array-size-to-the-half/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3804/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> buildEleFreqMap(vector<int>& vec) {
        int len = vec.size();

        unordered_map<int, int> eleFreqMap;
        for (int i = 0; i < len; i++) {
            int ele = vec[i];
            eleFreqMap[ele]++;
        }

        return eleFreqMap;
    }

    vector<int> retrieveValues(unordered_map<int, int>& eleFreqMap) {
        int len = eleFreqMap.size();

        vector<int> vec(len);

        int i = 0;
        for (unordered_map<int, int>::iterator it = eleFreqMap.begin(); it != eleFreqMap.end(); it++) {
            vec[i++] = it->second;
        }

        return vec;
    }

    int findNumElesToHalfSum(int sum, vector<int>& vec) {
        sort(vec.begin(), vec.end(), greater<int>());

        int i;
        int crrSum = 0;
        for (i = 0; i < vec.size(); i++) {
            int newSum = crrSum + vec[i];
            if (newSum >= (sum / 2)) {
                break;
            }

            crrSum = newSum;
        }

        return min(i + 1, (int)vec.size());
    }

   public:
    int minSetSize(vector<int>& arr) {
        int len = arr.size();

        unordered_map<int, int> eleFreqMap = buildEleFreqMap(arr);
        int numInts = eleFreqMap.size();

        if (numInts == 1) {
            return 1;
        }

        vector<int> freqsVec = retrieveValues(eleFreqMap);

        return findNumElesToHalfSum(len, freqsVec);
    }
};
