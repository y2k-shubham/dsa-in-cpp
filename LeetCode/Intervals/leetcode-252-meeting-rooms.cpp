// LeetCode-252: https://leetcode.com/problems/meeting-rooms/

// Companies: [Amazon][Apple][Google][Meta][Microsoft][TikTok][Oracle][Bloomberg][Uber][Palo Alto Networks]

#include <vector>
#include <utility>

using namespace std;

bool mComparator(const pair<int, int>& p1, const pair<int, int>& p2) {
    if (p1.first < p2.first) {
        return true;
    } else if (p1.first == p2.first) {
        return (p1.second >= p2.second);
    } else {
        return false;
    }
}

class Solution {
private:
    vector<pair<int, int>> convertToPairVec(vector<vector<int>>& vec) {
        int len = vec.size();

        vector<pair<int, int>> pairVec(len);

        for (int i = 0; i < len; i++) {
            pair<int, int> mPair = {vec[i][0], vec[i][1]};
            pairVec[i] = mPair;
        }

        return pairVec;
    }

    bool canAttendMeetings(vector <pair<int, int>>& intervals) {
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i - 1].second > intervals[i].first) {
                return false;
            }
        }

        return true;
    }

public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1) {
            return true;
        }

        vector<pair<int, int>> pairVec = convertToPairVec(intervals);
        sort(pairVec.begin(), pairVec.end(), mComparator);

        return canAttendMeetings(pairVec);
    }
};
