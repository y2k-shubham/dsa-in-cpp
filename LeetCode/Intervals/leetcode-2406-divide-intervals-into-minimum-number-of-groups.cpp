// LeetCode-2406: https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/
// good question: unconventional for a regular Interval based question

#include <map>
#include <vector>

using namespace std;

#define MAX_LEN 1000002

class Solution {
private:
    // ---------- Solution-1: using Map : 262 ms ------------

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

    int solution1Map(vector <vector <int>>& intervals) {
        map <int, int> rangeMap = createRangeMap(intervals);
        return findMaxOverlap(rangeMap);
    }

    // ---------- Solution-2: using Vector : 144 ms ------------

    vector <int> createRangeVec(vector <vector <int>>& intervals) {
        vector <int> rangeVec(MAX_LEN, 0);

        for (auto vec : intervals) {
            int rangeStart = vec[0];
            int rangeEnd = vec[1];

            rangeVec[rangeStart]++;
            rangeVec[rangeEnd + 1]--;
        }

        return rangeVec;
    }

    int findMaxOverlap(vector <int>& rangeVec) {
        int maxOverlap = 0;

        int crrOverlap = 0;
        for (auto it = rangeVec.begin(); it != rangeVec.end(); it++) {
            crrOverlap += *it;
            maxOverlap = max(maxOverlap, crrOverlap);
        }

        return maxOverlap;
    }

    int solution2Vector(vector <vector <int>>& intervals) {
        vector <int> rangeVec = createRangeVec(intervals);
        return findMaxOverlap(rangeVec);
    }

public:
    int minGroups(vector <vector <int>>& intervals) {
        // return solution1Map(intervals);
        return solution2Vector(intervals);
    }
};
