// LeetCode-1099: https://leetcode.com/problems/two-sum-less-than-k/
// Premium
// Companies: [Amazon]

// definitely NOT an easy question as per current solution
// and it shows : barely accepted; LC runtime 4.5 %tile

#include <vector>
#include <map>

using namespace std;

class Solution {
private:
    map <int, int> createFreqMap(vector <int>& vec) {
        map <int, int> freqMap;

        for (int val : vec) {
            freqMap[val]++;
        }

        return freqMap;
    }

    vector <int> createCumulativeFreqVec(map<int, int>& freqMap) {
        int numUniqueVals = freqMap.size();
        vector <int> vec(numUniqueVals, 0);

        int cumulativeFreq = 0;
        int i = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
            cumulativeFreq += it->second;
            vec[i++] = cumulativeFreq;
        }

        return vec;
    }

    bool hasNoSuchPair(map<int, int>& freqMap, int k) {
        int smallVal1 = freqMap.begin()->first;
        int smallVal2 = (freqMap.begin()->second > 1) ? smallVal1 : (++freqMap.begin())->first;

        return (smallVal1 + smallVal2) >= k;
    }

    pair <bool, int> hasAllSuchPairs(map<int, int>& freqMap, int k) {
        int bigVal1 = freqMap.rbegin()->first;
        int bigVal2 = (freqMap.rbegin()->second > 1) ? bigVal1 : (++freqMap.rbegin())->first;
        int bigValsSum = bigVal1 + bigVal2;

        if (bigValsSum < k) {
            return make_pair(true, bigValsSum);
        } else {
            return make_pair(false, -1);
        }
    }

public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        int len = nums.size();
        if (len <= 1) {
            return -1;
        }

        map <int, int> freqMap = createFreqMap(nums);
        vector <int> cumulativeFreqVec = createCumulativeFreqVec(freqMap);

        if (hasNoSuchPair(freqMap, k)) {
            return -1;
        }

        pair <bool, int> hasAllSuchPairsRes = hasAllSuchPairs(freqMap, k);
        if (hasAllSuchPairsRes.first) {
            return hasAllSuchPairsRes.second;
        }

        int maxSum = -1;
        for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
            // first number
            int num1 = it->first;

            // max theoretical value of second number such that sum < k
            int num2MaxVal = k - num1 - 1;
            // upper-bound will try to find value greater than theoretical max
            // (we picked upper-bound instead of lower-bound to simplify impl :
            // even in lower_bound we would have to handle the upper_bound case anyway)
            auto num2MaxIt = freqMap.upper_bound(num2MaxVal);

            if (num2MaxIt == freqMap.begin()) {
                // even the smallest element is greater than the theoretical max,
                // so no feasible solution
                return maxSum;
                // continue;
            }

            // if (num2MaxIt == freqMap.end()) {
            // // we reached end, implying every value is less than or equal to theoretical max
            // }

            // decrement iterator to get to a value less than or equal to theoretical max
            num2MaxIt--;
            // read the second number's value
            int num2 = num2MaxIt->first;

            if ((num1 == num2) && (num2MaxIt->second < 2)) {
                // if that second number is same as first, check whether frequency is < 2
                // if so then we can't pick it, we'll need to decrement iterator once more
                if (num2MaxIt == freqMap.begin()) {
                    // but before decrementing iterator we first need to chek if we're already at beginning of map
                    // if yes then nothing else to do in this iteration : its infeasible and we can try a different value of num1
                    continue;
                }

                // otherwise decrement iterator
                num2MaxIt--;
                // then read the updated second number (num2)
                num2 = num2MaxIt->first;
            }

            // calculate current sum
            int crrSum = num1 + num2;
            // update max sum
            maxSum = max(maxSum, crrSum);
        }

        return maxSum;
    }
};
