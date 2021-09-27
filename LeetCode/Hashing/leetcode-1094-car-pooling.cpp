// LeetCode-1094: https://leetcode.com/problems/car-pooling/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> prepareTransitMap(vector<vector<int>>& trips, int idx) {
        unordered_map<int, int> transitMap;

        for (int i = 0; i < trips.size(); i++) {
            int numPassengers = trips[i][0];
            int stop = trips[i][idx];

            transitMap[stop] += numPassengers;
        }

        return transitMap;
    }

    vector<int> prepareStopsVec(vector<vector<int>>& trips) {
        // converting this to (ordered) set increases LC submission runtime by ~ 33%
        unordered_set<int> stopsSet;

        for (int i = 0; i < trips.size(); i++) {
            stopsSet.insert(trips[i][1]);
            stopsSet.insert(trips[i][2]);
        }

        vector<int> stopsVec(stopsSet.begin(), stopsSet.end());
        sort(stopsVec.begin(), stopsVec.end());

        return stopsVec;
    }

   public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        unordered_map<int, int> boardingMap = prepareTransitMap(trips, 1);
        unordered_map<int, int> deboardingMap = prepareTransitMap(trips, 2);

        vector<int> stopsVec = prepareStopsVec(trips);

        int numPassengers = 0;
        for (int i = 0; i < stopsVec.size(); i++) {
            int stop = stopsVec[i];
            numPassengers -= deboardingMap[stop];
            numPassengers += boardingMap[stop];

            if (numPassengers > capacity) {
                return false;
            }
        }

        return true;
    }
};
