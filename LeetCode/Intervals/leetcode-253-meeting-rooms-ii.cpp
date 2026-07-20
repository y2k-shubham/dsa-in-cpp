// LeetCode-253: https://leetcode.com/problems/meeting-rooms-ii/

// Premium
// Companies: [Google][Amazon][Bloomberg][JPMorgan Chase][Microsoft][Meta][Apple][TikTok][IBM][Oracle][Uber][Atlassian][Netflix][Snap][Hubspot][Waymo][WorldQuant][Adobe][Cisco][Citadel][Splunk]

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
private:
    pair <vector<int>, vector<int>> createStartAndEndTimeVecs(vector<vector<int>>& intervals) {
        int len = intervals.size();

        vector<int> startTimes(len);
        vector<int> endTimes(len);

        for (int i = 0; i < len; i++) {
            startTimes[i] = intervals[i][0];
            endTimes[i] = intervals[i][1];
        }

        return {startTimes, endTimes};
    }

    int calcMaxOverlap(vector <int>& startTimesVec, vector <int>& endTimesVec) {
        int len = startTimesVec.size();

        int iS = 0, iE = 0;
        int maxOverlap = 1;
        while (iS < len) {
            if (startTimesVec[iS] < endTimesVec[iE]) {
                iS++;

                int crrOverlap = iS - iE;
                maxOverlap = max(maxOverlap, crrOverlap);
            } else {
                iE++;
            }
        }

        return maxOverlap;
    }

public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if (len <= 1) {
            return len;
        }

        pair <vector<int>, vector<int>> startAndEndTimeVecs = createStartAndEndTimeVecs(intervals);
        vector <int> startTimesVec = startAndEndTimeVecs.first;
        vector <int> endTimesVec = startAndEndTimeVecs.second;

        sort(startTimesVec.begin(), startTimesVec.end());
        sort(endTimesVec.begin(), endTimesVec.end());

        return calcMaxOverlap(startTimesVec, endTimesVec);
    }
};
