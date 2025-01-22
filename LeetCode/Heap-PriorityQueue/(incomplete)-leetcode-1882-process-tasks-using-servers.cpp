// LeetCode-1882: https://leetcode.com/problems/process-tasks-using-servers
// incomplete

#include <vector>
#include <map>
#include <utility>
#include <queue>

using namespace std;

// priority que with custom comparator https://stackoverflow.com/a/35538318/3679900
bool pQueComparator(pair<int, int>& p1, pair<int, int>& p2) {
    if (p1.second < p2.second) {
        return true;
    } else if (p1.second > p2.second) {
        return false;
    } else {
        return p1.first < p2.first;
    }
}

class Solution {
private:
    map <int, priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&pQueComparator)>> createFreeTimeToServerMap(vector <int>& servers) {
        map <int, priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&pQueComparator)>> freeTimeToServerMap;

        for (int i = 0; i < servers.size(); i++) {
            freeTimeToServerMap[0].push({i, servers[i]});
        }

        return freeTimeToServerMap;
    }

    int scheduleTaskAndReturnServerId(
        map <int, priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&pQueComparator)>>& freeTimeToServerMap,
        int taskArrivalTime,
        int taskDuration) {
        auto it = freeTimeToServerMap.begin();
        // extra-safety: advance iterator till we have an valid entry in map
        while ((it != freeTimeToServerMap.end()) && (it->second.empty())) {
            ++it;
        }

        if (it == freeTimeToServerMap.end()) {
            // no servers are available; should never happen
            return -1;
        }

        // retrieve server to which the task will be assigned from heap
        pair <int, int> assignedServer = it->second.top();
        it->second.pop();

        // delete key from map if heap becomes empty
        if (it->second.empty()) {
            freeTimeToServerMap.erase(it);
        }

        // determine start & end time of task
        int taskStartTime = max(taskArrivalTime, it->first);
        int taskEndTime = taskStartTime + taskDuration;

        // insert server with updated free time in map
        freeTimeToServerMap[taskEndTime].push(assignedServer);

        // return id of assigne server
        return assignedServer.first;
    }

public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        map <int, priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&pQueComparator)>> freeTimeToServerMap = createFreeTimeToServerMap(servers);

        int numTasks = tasks.size();
        vector<int> serverIds(numTasks);

        for (int i = 0; i < tasks.size(); i++) {
            serverIds[i] = scheduleTaskAndReturnServerId(freeTimeToServerMap, i, tasks[i]);
        }

        return serverIds;
    }
};
