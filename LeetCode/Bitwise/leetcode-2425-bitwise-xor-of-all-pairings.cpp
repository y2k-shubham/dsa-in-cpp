// LeetCode-2425: https://leetcode.com/problems/bitwise-xor-of-all-pairings/

/**
 * Observations
 * 1. we only need to keep odd-freq elements from both input vectors and can throw away even-freq ones since they will cancel out in final XOR answer
 * 2. Even odd-freq elements will only contribute once, i.e., freq=1 to our final XOR answer
 * .
 * by implementing 1 & 2, our problem statement will simplify as follows
 * given arr1 = {...}, arr2 = {...}
 * we'll create oddFreqEles1 = { .. <odd-freq-elements of arr1> .. } and oddFreqEles2 = { .. <odd-freq-elements of arr2> .. }
 * .
 * more observation
 * - since we are taking pair-wise XORs across both arrays, so if length of one array is even,
 *   then by virtue of that contributions of all elements in other array towards final XOR answer will cancel out
 * from above we decipher following logic
 * .
 * given len1 = sizeof(oddFreqEles1) and len2 = sizeof(oddFreqEles2)
 * 1. if both len1 & len2 are even answer will be zero
 * 2. if either of len1 or len2 are even then answer will be xor of all elements of that even-length set
 *    why?
 *    if len1 is even and len2 is odd, that would mean contribution of all elements of oddFreqEles2 will cancel out
 *    hence we'll be left with only contribution of oddFreqEles1
 * 3. otherwise if both len1 and len2 are odd then answer will (xor of all elements of oddFreqEles1) ^ (xor of all elements of oddFreqEles2)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_map<int, int> createFreqMap(vector<int>& nums) {
        unordered_map<int, int> freqMap;
        for (auto it = nums.begin(); it != nums.end(); it++) {
            freqMap[*it]++;
        }

        return freqMap;
    }

    unordered_set<int> getOddFreqEles(unordered_map<int, int>& freqMap) {
        unordered_set<int> oddFreqEles;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if ((it->second & 1) == 1) {
                oddFreqEles.insert(it->first);
            }
        }

        return oddFreqEles;
    }

    int calcXor(unordered_set<int>& eles) {
        int _xor = 0;
        for (auto it = eles.begin(); it != eles.end(); it++) {
            _xor ^= *it;
        }
        return _xor;
    }

public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> freqMap1 = createFreqMap(nums1);
        unordered_set<int> oddFreqEles1 = getOddFreqEles(freqMap1);
        bool hasEvenNoOfEles1 = (oddFreqEles1.size() & 1) == 0;

        unordered_map<int, int> freqMap2 = createFreqMap(nums2);
        unordered_set<int> oddFreqEles2 = getOddFreqEles(freqMap2);
        bool hasEvenNoOfEles2 = (oddFreqEles2.size() & 1) == 0;

        if (hasEvenNoOfEles1 && hasEvenNoOfEles2) {
            return 0;
        } else if (hasEvenNoOfEles1) {
            return calcXor(oddFreqEles1);
        } else if (hasEvenNoOfEles2) {
            return calcXor(oddFreqEles2);
        } else {
            return calcXor(oddFreqEles1) ^ calcXor(oddFreqEles2);
        }
    }
};
