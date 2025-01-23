// LeetCode-2365: https://leetcode.com/problems/task-scheduler-ii/

#include <vector>
#include <unordered_map>
#include <climits>
#include <queue>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
private:
    unordered_map<int, int> createFreqMap(vector <int>& vec) {
        unordered_map<int, int> freqMap;

        for (int val: vec) {
            freqMap[val]++;
        }

        return freqMap;
    }

    vector <pair <int, int> > createFreqValVec(unordered_map<int, int>& freqMap) {
        int numUniqueItems = freqMap.size();

        vector <pair <int, int> > freqValVec(numUniqueItems);
        int i = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            freqValVec[i++] = {it->second, it->first};
        }

        return freqValVec;
    }



public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int, int> freqMap = createFreqMap(tasks);

        vector <pair <int, int> > freqValVec = createFreqValVec(freqMap);
        sort(freqValVec.begin(), freqValVec.end(), greater<>());
    }
};
