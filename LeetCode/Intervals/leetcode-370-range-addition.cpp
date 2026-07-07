// LeetCode-370: https://leetcode.com/problems/range-addition/

#include <vector>

using namespace std;

class Solution {
private:
    void recordRangeUpdate(vector<int>& intervals, int start, int end, int delta) {
        intervals[start] += delta;

        if (end < intervals.size()) {
            intervals[end] -= delta;
        }
    }

    void applyRangeUpdates(vector<int>& intervals) {
        int sum = 0;
        for (int i = 0; i < intervals.size(); i++) {
            sum += intervals[i];
            intervals[i] = sum;
        }
    }

public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> intervals(length, 0);

        int numUpdates = updates.size();
        if (numUpdates <= 0) {
            return intervals;
        }

        for (int i = 0; i < numUpdates; i++) {
            vector<int> update = updates[i];
            recordRangeUpdate(intervals, update[0], update[1] + 1, update[2]);
        }

        applyRangeUpdates(intervals);

        return intervals;
    }
};
