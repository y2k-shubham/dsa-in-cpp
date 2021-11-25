// LeetCode-697: https://leetcode.com/problems/degree-of-an-array/
// current soln is suboptimal is quite complex; certainly not an Easy category soln

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    int findMaxFreq(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        int maxFreq = 0;
        for (int i = 0; i < vec.size(); i++) {
            int crrEle = vec[i];

            freqMap[crrEle]++;
            maxFreq = max(maxFreq, freqMap[crrEle]);
        }

        return maxFreq;
    }

    pair<int, int> findShortestWindow(vector<int>& vec, int reqFreq) {
        int len = vec.size();

        unordered_map<int, int> eleFreqMap;
        map<int, unordered_set<int> > freqElesMap;

        // important: these initializations are critical to correctness
        int shortestWinLen = len;
        pair<int, int> shortestWinIdxs = {0, len - 1};

        int iLo = 0;
        int iHi = 0;
        while (iHi < len) {
            int inEle = vec[iHi];

            // update frequency of incoming element
            int crrFreq = 0;
            if (eleFreqMap.find(inEle) != eleFreqMap.end()) {
                crrFreq = eleFreqMap[inEle];
                freqElesMap[crrFreq].erase(inEle);
            }

            int newFreq = crrFreq + 1;
            eleFreqMap[inEle] = newFreq;
            freqElesMap[newFreq].insert(inEle);

            // find max frequency of all elements in current window
            int maxFreq = freqElesMap.rbegin()->first;
            // shrink window till it's maxFreq equals the overall maxFreq of entire array
            while ((iLo < iHi) && (maxFreq == reqFreq)) {
                // update shortest window
                int crrWinLen = iHi - iLo + 1;
                if (crrWinLen < shortestWinLen) {
                    // printf("found window vec[iLo=%d]=%d .. vec[iHi=%d]=%d of len=%d with maxFreq=%d, updating shortestWinLen=%d..\n", iLo, vec[iLo], iHi, vec[iHi], crrWinLen, maxFreq, shortestWinLen);

                    shortestWinLen = crrWinLen;
                    shortestWinIdxs = {iLo, iHi};
                } else {
                    // printf("found window vec[iLo=%d]=%d .. vec[iHi=%d]=%d of len=%d with maxFreq=%d, not updating shortestWinLen=%d..\n", iLo, vec[iLo], iHi, vec[iHi], crrWinLen, maxFreq, shortestWinLen);
                }

                int outEle = vec[iLo];

                // update frequency of outgoing element
                int crrFreq = eleFreqMap[outEle];
                freqElesMap[crrFreq].erase(outEle);
                // important condn: this is the crux of this soln
                if (freqElesMap[crrFreq].empty()) {
                    freqElesMap.erase(crrFreq);
                }

                int newFreq = crrFreq - 1;
                if (newFreq == 0) {
                    eleFreqMap.erase(outEle);
                } else {
                    eleFreqMap[outEle] = newFreq;
                    freqElesMap[newFreq].insert(outEle);
                }

                // find max frequency of all elements in current window
                maxFreq = freqElesMap.rbegin()->first;

                iLo++;
            }

            iHi++;
        }

        return shortestWinIdxs;
    }

   public:
    int findShortestSubArray(vector<int>& nums) {
        int maxFreq = findMaxFreq(nums);
        // important condn: do NOT miss this (or we'll get wrong answer for [2,1] test-case)
        if (maxFreq == 1) {
            return 1;
        }

        pair<int, int> shortestWindow = findShortestWindow(nums, maxFreq);
        // printf("shortestWindow = %d .. %d, len = %d\n", shortestWindow.first, shortestWindow.second, (shortestWindow.second - shortestWindow.first + 1));
        return shortestWindow.second - shortestWindow.first + 1;
    }
};
