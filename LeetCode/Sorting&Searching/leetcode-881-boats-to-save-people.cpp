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
            // this pruning also doesn't bring any visible gains
            if (vec[lo] <= ele) {
                int mid = (lo + hi) / 2;

                // this <= condition is necessary for correctness (of this entire program)
                if (vec[mid] <= ele) {
                    return max(mid, findFloorInd(vec, mid + 1, hi, ele));
                } else {
                    return findFloorInd(vec, lo, mid - 1, ele);
                }
            } else {
                return -1;
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
    int numRescueBoats1(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int len = people.size();
        // vector to keep track if the person has already been put in a boat or not
        vector<int> occ(len, 0);

        int numBoats = 0;
        for (int i = len - 1; i >= 0; i--) {
            // proceed only if person hasn't already been put up on a boat
            if (occ[i] != 1) {
                // weight of current person
                int m1Weight = people[i];
                // max weight of other person to enable both of them to cross together
                int maxM2Weight = limit - m1Weight;

                /**
                 * - we try pairing up another person with current (ith) person only if it is possible
                 *   to do so (lightest person should weigh less than or equal to max admissible weight)
                 * - although this 'pruning' doesn't bring any visible performance gain
                 */
                if (people[0] <= maxM2Weight) {
                    // find index of heaviest person possible to pair up with current person
                    int floorInd = findFloorInd(people, 0, i - 1, maxM2Weight);

                    if (floorInd >= 0) {
                        // find the index of heaviest person (still unpaired) that can be put with current one
                        // because of this linear scan, the worst case runtime would be O(n^2)
                        int biggestUnoccInd = findBiggestUnoccInd(occ, floorInd);
                        if (biggestUnoccInd >= 0) {
                            // if there is such a person, pair them up
                            // (so now we have a lesser person to team up)
                            occ[biggestUnoccInd] = 1;
                        }
                    }
                }

                // mark current person as having being put on a boat
                occ[i] = 1;
                // increase no of boats
                numBoats++;
            }
        }

        return numBoats;
    }

    // much better: speed 52 %tile, memory 41 %tile
    // this one is O(nlogn) -> sorting + O(n) -> simple two pointer approach
    int numRescueBoats2(vector<int>& people, int limit) {
        int len = people.size();
        sort(people.begin(), people.end());
        
        int numBoats = 0;
        
        int i = 0;
        int j = len - 1;
        while (i <= j) {
            if (i != j) {
                int lightPWgt = people[i];
                int heavyPWgt = people[j];

                if ((lightPWgt + heavyPWgt) <= limit) {
                    i++;
                }
            }
            
            j--;
            numBoats++;
        }
        
        return numBoats;
    }
    
    int numRescueBoats(vector <int>& people, int limit) {
        return numRescueBoats2(people, limit);
    }

};
