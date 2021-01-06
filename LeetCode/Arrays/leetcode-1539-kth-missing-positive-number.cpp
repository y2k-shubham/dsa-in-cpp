// LeetCode-1539: https://leetcode.com/problems/kth-missing-positive-number/
// LC Jan 2021 challenge: https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3594/

#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int extraSpaceSoln(vector<int>& arr, int k) {
        int len = arr.size();

        unordered_set<int> nums;
        nums.insert(arr.begin(), arr.end());

        cout << nums.size() << endl;

        int i, missIdx;
        for (i = 1, missIdx = 0; missIdx < k; i++) {
            if (nums.find(i) == nums.end()) {
                missIdx++;

                if (missIdx == k) {
                    break;
                }
            }
        }

        if (missIdx == k) {
            return i;
        } else {
            return -1;
        }
    }

    int noSpaceSoln(vector<int>& arr, int k) {
        int len = arr.size();

        int ctr = 0;
        int missIdx = 0;
        int arrIdx = 0;
        while (missIdx < k) {
            ctr++;

            if (arrIdx <= len - 1) {
                // elements still left in array
                int crrEle = arr[arrIdx];

                if (ctr < crrEle) {
                    // we are in a 'hole' (a gap b/w consecutive elements in array)
                    // so we dont increment array pointer, just note down that we've seen a missed elemtn
                    missIdx++;
                } else if (ctr == crrEle) {
                    // skip the element
                    arrIdx++;
                } else {
                    // inconsitent state
                    return -1;
                }
            } else {
                // we have already consumed the array
                missIdx++;
            }
        }

        return ctr;
    }

    int findKthPositive(vector<int>& arr, int k) {
        return noSpaceSoln(arr, k);
    }
};
