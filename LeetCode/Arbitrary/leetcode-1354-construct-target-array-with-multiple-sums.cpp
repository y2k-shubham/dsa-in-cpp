// LeetCode-1354: https://leetcode.com/problems/construct-target-array-with-multiple-sums/
// May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3737/

// pretty much impossible to solve;
// - maths involved
// - plus too many edge cases
// and still barely passes; LC submission speed 6 %tile, memory 8 %tile

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   private:
    map<int, int> buildFreqMap(vector<int>& vec) {
        map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    int extractBiggestEle(map<int, int>& freqMap) {
        if (freqMap.empty()) {
            return -1;
        }

        map<int, int>::reverse_iterator it = freqMap.rbegin();

        int ele = it->first;

        freqMap[ele]--;
        if (freqMap[ele] == 0) {
            freqMap.erase(ele);
        }

        return ele;
    }

    int sumOfEles(vector<int>& vec) {
        long long int sum = 0;

        for (int i = 0; i < vec.size(); i++) {
            sum += vec[i];
        }

        return sum;
    }

   // still barely passes; LC submission speed 6 %tile, memory 8 %tile
    bool isReducible(vector<int>& vec) {
        int len = vec.size();

        // this one overflows
        // long long int crrSum  = accumulate(vec.begin(), vec.end(), 0);
        long long int crrSum = sumOfEles(vec);

        map<int, int> freqMap = buildFreqMap(vec);

        bool canReduce = true;
        do {
            int largestEle = extractBiggestEle(freqMap);
            if (largestEle == 1) {
                return true;
            }

            long long int residualSum = crrSum - largestEle;
            if (residualSum == 1) {
                // possible only in case of 2-ele array when one ele becomes 1
                return true;
            }
            if (residualSum == 0) {
                // possible only in single-ele array (meaning that it is pretty much impossible)
                return false;
            }

            // this is correct, but leads to TLE when the largest number
            // is extremely big compared to residualSum (like largestNum=10^9, residualSum=2)
            // int replacementEle = largestEle - residualSum;
            // if (replacementEle <= 0) {
            //     return false;
            // }

            // so as an improvement, we can simply do modulo as explained here
            // Cat Racket: https://www.youtube.com/watch?v=OKRkQ1YT_2s
            int replacementEle = largestEle % residualSum;
            if ((replacementEle == 0) || (largestEle <= residualSum)) {
                return false;
            }

            freqMap[replacementEle]++;

            long long int reducedSum = ((long long int)(crrSum - largestEle)) + replacementEle;
            crrSum = reducedSum;

            canReduce = (crrSum > len);
        } while (canReduce);

        // all elements must've become 1
        return (freqMap.size() == 1) && (extractBiggestEle(freqMap) == 1);
    }

   public:
    bool isPossible(vector<int>& target) {
        int len = target.size();
        if (len == 1) {
            return target[0] == 1;
        }

        return isReducible(target);
    }
};
