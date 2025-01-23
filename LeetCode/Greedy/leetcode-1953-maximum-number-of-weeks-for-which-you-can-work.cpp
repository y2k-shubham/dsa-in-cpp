// LeetCode-2365: https://leetcode.com/problems/task-scheduler-ii/

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    long long numberOfWeeks(vector <int>& milestones) {
        sort(milestones.begin(), milestones.end(), greater <>());

        long long maxMilestones = milestones[0];

        long long totalMilestones = accumulate(milestones.begin(), milestones.end(), 0L);
        long long totalMilestonesWithoutMaxMilestones = totalMilestones - maxMilestones;

        if ((maxMilestones - 1) <= totalMilestonesWithoutMaxMilestones) {
            return totalMilestones;
        } else {
            return (totalMilestonesWithoutMaxMilestones * 2) + 1;
        }
    }
};
