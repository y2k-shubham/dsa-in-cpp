// LeetCode-2365: https://leetcode.com/problems/task-scheduler-ii/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int, long long> taskTypeEarliestStartDays;

        long long currentDay = 0;
        for (int i = 0; i < tasks.size(); i++) {
            int taskType = tasks[i];
            long long earliestStartDay = taskTypeEarliestStartDays[taskType];

            if (currentDay >= earliestStartDay) {
                // complete current (ith) task
                taskTypeEarliestStartDays[taskType] = currentDay + space + 1;
                currentDay++;
            } else {
                // jump to earliest day
                currentDay = earliestStartDay;
                // don't 'consume' (complete) current task
                i--;
            }
        }

        return currentDay;
    }
};
