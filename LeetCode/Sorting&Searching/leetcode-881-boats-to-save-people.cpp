// LeetCode-881: https://leetcode.com/problems/boats-to-save-people/
// Jan 2021 challenge: https://leetcode.com/explore/featured/card/january-leetcoding-challenge-2021/580/week-2-january-8th-january-14th/3602/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findFloorInd(vector<int>& vec, int lo, int hi, int ele) {
        int len = hi - lo + 1;

        if (len <= 0) {
            return -1;
        } else if (len == 1) {
            if (vec[lo] <= ele) {
                return lo;
            } else {
                return -1;
            }
        } else if (len == 2) {
            if (vec[hi] <= ele) {
                return hi;
            } else if (vec[lo] <= ele) {
                return lo;
            } else {
                return -1;
            }
        } else {
            int mid = (lo + hi) / 2;

            if (vec[mid] <= ele) {
                return max(mid, findFloorInd(vec, mid + 1, hi, ele));
            } else {
                return findFloorInd(vec, lo, mid - 1, ele);
            }
        }
    }

    int findBiggestUnoccInd(vector<int>& occ, int ind) {
        while (ind >= 0 && occ[ind] == 1) {
            ind--;
        }

        return ind;
    }

    // barely accepted: speed 5 %tile, memory 7 %tile
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int len = people.size();
        vector<int> occ(len, 0);

        int numBoats = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (occ[i] != 1) {
                int m1Weight = people[i];
                int maxM2Weight = limit - m1Weight;

                int floorInd = findFloorInd(people, 0, i - 1, maxM2Weight);
                if (floorInd >= 0) {
                    int biggestUnoccInd = findBiggestUnoccInd(occ, floorInd);
                    if (biggestUnoccInd >= 0) {
                        occ[biggestUnoccInd] = 1;
                    }
                }

                occ[i] = 1;
                numBoats++;
            }
        }

        return numBoats;
    }
};
