// LeetCode-870: https://leetcode.com/problems/advantage-shuffle

/**
 * Wrong answer for following test-case
 * nums1 = [2,0,4,1,2]
 * nums2 = [1,3,0,0,2]
 *
 * expected = [2,0,2,1,4]
 * actual = [2,4,1,2,2]
 */

#include <vector>
#include <map>
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
private:
    void showFreqMap(map <int, int>& freqMap, string when) {
        printf("%s, freqMap is:-\n", when.c_str());
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            printf("[%d] -> %d\n", it->first, it->second);
        }
    }

    map <int, int> buildFreqMap(vector <int>& vec) {
        map <int, int> freqMap;
        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }
        return freqMap;
    }

    void decreaseNumFreq(map <int, int>& freqMap, int ele) {
        if (freqMap.find(ele) == freqMap.end()) {
            return;
        }

        int eleFreq = freqMap[ele];
        if (eleFreq == 1) {
            freqMap.erase(ele);
        } else {
            freqMap[ele] = eleFreq - 1;
        }
    }

    int getJustBiggerNumber(map <int, int>& freqMap, int ele) {
        auto it = freqMap.upper_bound(ele);
        if (it == freqMap.end()) {
            return INT_MIN;
        }

        int upperBoundEle = it->first;
        decreaseNumFreq(freqMap, upperBoundEle);

        return upperBoundEle;
    }

public:
    vector <int> advantageCount(vector <int>& nums1, vector <int>& nums2) {
        int len = nums1.size();
        if (len <= 1) {
            return nums1;
        }

        map <int, int> freqMap1 = buildFreqMap(nums1);
        vector <int> nums1Perm(len);

        for (int i = 0; i < len; i++) {
            int ele1 = nums1[i];
            int ele2 = nums2[i];

            int justBiggerNumber = getJustBiggerNumber(freqMap1, ele2);
            // if (justBiggerNumber == INT_MIN) {
            //     printf("justBiggerNumber = INT_MIN\n");
            // } else {
            //     printf("justBiggerNumber = %d\n", justBiggerNumber);
            // }
            // ostringstream oss;
            // oss << "after iteration i=" << i;
            // showFreqMap(freqMap1, oss.str());

            if (justBiggerNumber == INT_MIN) {
                decreaseNumFreq(freqMap1, ele1);
                nums1Perm[i] = ele1;
            } else {
                nums1Perm[i] = justBiggerNumber;
            }
        }

        return nums1Perm;
    }
};
