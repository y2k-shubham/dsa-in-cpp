// LeetCode-821: https://leetcode.com/problems/shortest-distance-to-a-character/
// Feb-2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3631/

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_set<int> findCharPosns(string str, char ch) {
        unordered_set<int> posnSet;

        for (int i = 0; i < str.size(); i++) {
            if (str.at(i) == ch) {
                posnSet.insert(i);
            }
        }

        return posnSet;
    }

    vector<int> convertToPosnVec(unordered_set<int> posnSet) {
        int len = posnSet.size();

        vector<int> posnVec(posnSet.begin(), posnSet.end());
        sort(posnVec.begin(), posnVec.end());

        return posnVec;
    }

    int findClosestDist(string& str, char ch, vector<int>& posnVec, int idx) {
        vector<int>::iterator lBound = lower_bound(posnVec.begin(), posnVec.end(), idx);

        int minDist = INT_MAX;
        if (lBound == posnVec.begin()) {
            if ((*lBound) == idx) {
                // idx is first occurence of our char 'c'
                minDist = 0;
            } else {
                // idx is before the first occurence of our char 'c'
                minDist = (*lBound) - idx;
            }
        } else if (lBound == posnVec.end()) {
            // idx is after the last occurence of our char 'c'
            minDist = idx - (*posnVec.rbegin());
        } else {
            if ((*lBound) == idx) {
                // idx is one of the occurences of our char 'c'
                minDist = 0;
            } else {
                // idx lies somewhere in b/w two occurences of 'c'
                int minDistRight = (*lBound) - idx;

                lBound--;
                int minDistLeft = idx - (*lBound);

                minDist = min(minDistLeft, minDistRight);
            }
        }

        return minDist;
    }

    vector<int> buildClosestDistVec(string str, char ch, vector<int> posnVec) {
        int len = str.size();

        vector<int> closestDistVec(len, INT_MAX);
        for (int i = 0; i < len; i++) {
            // this if-else clause is redundant, but added just for extra clarity
            if (str.at(i) == ch) {
                closestDistVec[i] = 0;
            } else {
                closestDistVec[i] = findClosestDist(str, ch, posnVec, i);
            }
        }

        return closestDistVec;
    }

   public:
    vector<int> shortestToChar(string str, char ch) {
        // this check / base-case is redundant, but added just for extra clarity
        if (str.size() == 1) {
            return {0};
        }

        unordered_set<int> posnSet = findCharPosns(str, ch);
        vector<int> posnVec = convertToPosnVec(posnSet);

        return buildClosestDistVec(str, ch, posnVec);
    }
};
