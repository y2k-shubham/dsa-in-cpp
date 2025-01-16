// LeetCode-2406: https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/
// good question: unconventional for a regular Interval based question

#include <map>
#include <vector>

using namespace std;

class Solution {
private:
    map <int, int> createRangeMap(vector <vector <int>>& intervals) {
        map <int, int> rangeMap;

        for (auto vec : intervals) {
            int rangeStart = vec[0];
            int rangeEnd = vec[1];

            rangeMap[rangeStart]++;
            rangeMap[rangeEnd + 1]--;
        }

        return rangeMap;
    }

    int findMaxOverlap(map <int, int>& rangeMap) {
        int maxOverlap = 0;

        int crrOverlap = 0;
        for (auto it = rangeMap.begin(); it != rangeMap.end(); it++) {
            crrOverlap += it->second;
            maxOverlap = max(maxOverlap, crrOverlap);
        }

        return maxOverlap;
    }

public:
    int minGroups(vector <vector <int>>& intervals) {
        map <int, int> rangeMap = createRangeMap(intervals);
        return findMaxOverlap(rangeMap);
    }
};
