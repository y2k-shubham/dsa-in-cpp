// LeetCode-2141: https://leetcode.com/problems/maximum-running-time-of-n-computers/
// wrong approach

#include <queue>
#include <map>
#include <set>
#include <climits>
#include <functional>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    priority_queue<int> createMaxHeap(vector<int>& vec, int from, int to) {
        priority_queue<int> maxHeap(vec.begin() + from, vec.begin() + to);
        return maxHeap;
    }

    priority_queue<int, vector<int>, greater<int>> createMinHeap(vector<int>& vec, int from, int to) {
        priority_queue<int, vector<int>, greater<int>> minHeap(vec.begin() + from, vec.begin() + to);
        return minHeap;
    }

    int extractMinEle(priority_queue<int, vector<int>, greater<int>>& minHeap) {
        if (minHeap.empty()) {
            return INT_MIN;
        }

        int minEle = minHeap.top();
        minHeap.pop();

        return minEle;
    }

    int extractMaxEle(priority_queue<int>& maxHeap) {
        if (maxHeap.empty()) {
            return INT_MIN;
        }

        int maxEle = maxHeap.top();
        maxHeap.pop();

        return maxEle;
    }

public:
    friend class SolutionTest;

    long long maxRunTime(int n, vector<int>& batteries) {
        int numBatteries = batteries.size();
        if (numBatteries < n) {
            return 0;
        }

        // sort in descending order of capacity: https://stackoverflow.com/q/9025084/3679900
        sort(batteries.rbegin(), batteries.rend());

        // create min-heap of batteries currently in use
        priority_queue<int, vector<int>, greater<int>> usedBatteries = createMinHeap(batteries, 0, n);
        // create max-heap of unused batteries
        priority_queue<int> unusedBatteries = createMaxHeap(batteries, n, numBatteries);

        long long totalRuntime = 0;
        while (usedBatteries.size() == n) {
            int minUsedBatteryMinutes = extractMinEle(usedBatteries);

            int numMinSizeUsedBatteries = 1;
            while (usedBatteries.top() == minUsedBatteryMinutes) {
                extractMinEle(usedBatteries);
                numMinSizeUsedBatteries++;
            }

            totalRuntime += minUsedBatteryMinutes;

            if (unusedBatteries.size() < numMinSizeUsedBatteries) {
                break;
            }

            for (int i = 1; i <= numMinSizeUsedBatteries; i++) {
                int maxUnusedBatteryMinutes = extractMaxEle(unusedBatteries);
                usedBatteries.push(maxUnusedBatteryMinutes);
            }
        }

        return totalRuntime;
    }
};

class SolutionTest {
public:
    void testMaxRunTime() {
        Solution soln = Solution();
        int nIn;
        vector<int> batteriesIn;
        long long outExpected, outComputed;

        nIn = 2;
        batteriesIn = {3, 3, 3};
        outExpected = 4;
        outComputed = soln.maxRunTime(nIn, batteriesIn);
        assert(outExpected == outComputed);

        nIn = 2;
        batteriesIn = {1, 1, 1, 1};
        outExpected = 2;
        outComputed = soln.maxRunTime(nIn, batteriesIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxRunTime();

    return 0;
}
