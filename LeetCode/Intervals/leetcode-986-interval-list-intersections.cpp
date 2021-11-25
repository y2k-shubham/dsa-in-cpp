// LeetCode-986: https://leetcode.com/problems/interval-list-intersections/
/**
 * edge cases around duplicate events
 * (a) one interval closing & other opening
 * (b) both intervals opening
 * (c) both intervals closing
 * 
 * [[0,2],[5,10],[13,23],[24,25]]
 * [[1,5],[8,12],[15,24],[25,26]]
 * 
 * [[1,3],[5,9]]
 * []
 * 
 * []
 * [[4,8],[10,12]]
 * 
 * [[1,7]]
 * [[3,10]]
 * 
 * [[3,10]]
 * [[5,10]]
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    int fillEvents(vector<vector<int>>& intervals, vector<pair<int, int>>& fusedIntervals, int idxBegin) {
        int idx = idxBegin;

        for (int i = 0; i < intervals.size(); i++) {
            fusedIntervals[idx] = {intervals[i][0], 1};
            fusedIntervals[idx + 1] = {intervals[i][1], -1};
            idx += 2;
        }

        return idx;
    }

    void showFusedIntervals(vector<pair<int, int>>& fusedIntervals) {
        printf("\nfusedIntervals are:-\n");

        for (int i = 0; i < fusedIntervals.size(); i++) {
            printf("%d\t", fusedIntervals[i].first);
        }
        cout << endl;

        for (int i = 0; i < fusedIntervals.size(); i++) {
            printf("%c\t", ((fusedIntervals[i].second > 0) ? '(' : ')'));
        }
        cout << endl;
    }

    vector<vector<int>> findOverlaps(vector<pair<int, int>>& fusedIntervals) {
        vector<vector<int>> overlaps;

        int len = fusedIntervals.size();
        int crrSum = 0;
        pair<int, int> crrOverlap = {-1, -1};
        for (int i = 0; i < len; i++) {
            crrSum += fusedIntervals[i].second;

            if (crrSum > 1) {
                // overlap begin found
                // printf("at [i=%d] = %d -> %c, found overlap begin, crrSum = %d\n", i, fusedIntervals[i].first, '(', crrSum);
                crrOverlap.first = fusedIntervals[i].first;
            } else if ((fusedIntervals[i].second == -1) && (crrSum == 1) && (crrOverlap.first >= 0)) {
                // overlap end found
                // printf("at [i=%d] = %d -> %c, found overlap end, crrSum = %d\n", i, fusedIntervals[i].first, ')', crrSum);
                crrOverlap.second = fusedIntervals[i].first;
                overlaps.push_back({crrOverlap.first, crrOverlap.second});
                crrOverlap = {-1, -1};
            } else {
                // printf("at [i=%d] = %d -> %c, found nothing, crrSum = %d\n", i, fusedIntervals[i].first, ((fusedIntervals[i].second > 0) ? '(' : ')'), crrSum);
            }

            if ((crrSum == 0) && ((i + 1) <= (len - 1)) && (fusedIntervals[i].first == fusedIntervals[i + 1].first)) {
                // overlapping integer found
                // printf("at [i=%d] = %d, found overlaping int, crrSum = %d\n", i, fusedIntervals[i].first, crrSum);
                overlaps.push_back({fusedIntervals[i].first, fusedIntervals[i].first});
            }
        }

        return overlaps;
    }

   public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        int len1 = firstList.size();
        int len2 = secondList.size();
        if (min(len1, len2) <= 0) {
            return {};
        }

        int numEvents = (len1 + len2) * 2;
        vector<pair<int, int>> fusedIntervals(numEvents);

        // fill events from first list
        int idx = fillEvents(firstList, fusedIntervals, 0);
        // fill events from second list
        fillEvents(secondList, fusedIntervals, idx);

        // sort events by time of occurence
        sort(fusedIntervals.begin(), fusedIntervals.end());

        // showFusedIntervals(fusedIntervals);

        // determine overlapping intervals
        return findOverlaps(fusedIntervals);
    }
};
