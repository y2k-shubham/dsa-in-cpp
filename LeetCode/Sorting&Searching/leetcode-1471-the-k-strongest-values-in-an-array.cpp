// LeetCode-1471: https://leetcode.com/problems/the-k-strongest-values-in-an-array/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int len = arr.size();
        if (k == len) {
            return arr;
        }

        sort(arr.begin(), arr.end());
        // note that the fucking defition of median has been changed in question (fucktards)
        int median = arr[(len - 1) / 2];

        vector<int> strongestVals(k);
        int j = 0;

        int ctr = 0;
        int iLo = 0;
        int iHi = len - 1;
        while ((ctr < k) && (iLo < iHi)) {
            int deltaLo = abs(arr[iLo] - median);
            int deltaHi = abs(arr[iHi] - median);

            if (deltaLo > deltaHi) {
                strongestVals[j++] = arr[iLo++];
            } else {
                // note that as per problem statement, if deltaLo = deltaHi, then we
                // must pick deltaHi as arr[iHi] > arr[iLo] (pick bigger element)
                strongestVals[j++] = arr[iHi--];
            }

            ctr++;
        }

        return strongestVals;
    }
};
