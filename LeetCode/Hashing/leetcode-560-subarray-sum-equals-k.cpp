// LeetCode-560: https://leetcode.com/problems/subarray-sum-equals-k/
// soln: (4th one of course) https://leetcode.com/problems/subarray-sum-equals-k/solution/

#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showMap(unordered_map<int, int>& freqMap) {
        printf("FreqMap is:-\n");
        for (unordered_map<int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
            printf("[%d] -> %d\n", i->first, i->second);
        }
    }

    // dont know where i was going with this
    int subarraySumWrong(vector<int>& vec, int k) {
        if (vec.empty()) {
            return 0;
        } else {
            map<int, int> cumSumFreq;
            int res = 0;

            int crrSum = 0;
            for (int i = 0; i < vec.size(); i++) {
                crrSum += vec[i];

                int diff = crrSum - k;
                if (crrSum != diff && cumSumFreq.find(diff) != cumSumFreq.end()) {
                    res += cumSumFreq[diff];
                }

                cumSumFreq[crrSum]++;
            }

            return res;
        }
    }

    vector<int> buildPrefSumArray(vector<int>& vec) {
        int len = vec.size();
        vector<int> prefSum(len);

        int sum = 0;
        for (int i = 0; i < len; i++) {
            sum += vec[i];
            prefSum[i] = sum;
        }

        return prefSum;
    }

    // no cant do it: freq-map of cum-sum has to be built alongside computation of subarray counts
    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    // no cant do it (same reason as above)
    int countKSumSubArrs(vector<int>& prefSum, unordered_map<int, int>& freqMap, int k) {
        int count = 0;

        for (int i = 0; i < prefSum.size(); i++) {
            int crrSum = prefSum[i];

            int reqCompSum1 = crrSum - k;
            count += freqMap[reqCompSum1];
            if (this->debug) {
                printf("at prefSum[%d]=%d, reqCompSum1=%d, freqMap[%d]=%d\n", i, crrSum, reqCompSum1, reqCompSum1, freqMap[reqCompSum1]);
            }
        }

        return count;
    }

   public:
    int subarraySum(vector<int>& vec, int k) {
        if (vec.empty()) {
            return 0;
        } else {
            int len = vec.size();
            vector<int> prefSum = buildPrefSumArray(vec);

            unordered_map<int, int> prefSumFreqMap;
            prefSumFreqMap[0] = 1;

            int numSubArrays = 0;
            for (int i = 0; i < len; i++) {
                int crrPrefSum = prefSum[i];

                numSubArrays += prefSumFreqMap[crrPrefSum - k];

                prefSumFreqMap[crrPrefSum]++;
            }

            if (this->debug) {
                showMap(prefSumFreqMap);
            }

            return numSubArrays;
        }
    }
};
