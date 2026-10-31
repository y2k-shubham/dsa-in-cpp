// LeetCode-2274: https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/
// smart simplification done here

#include <queue>
#include <functional>
#include <vector>

using namespace std;

class Solution {
private:
    priority_queue<int, vector<int>, greater<int>> createMinHeap(vector <int>& mVec) {
        priority_queue<int, vector<int>, greater<int>> minHeap(mVec.begin(), mVec.end());
        return minHeap;
    }

    int diff(int smallVal, int bigVal) {
        if ((smallVal == INT_MIN) || (bigVal == INT_MAX)) {
            return 0;
        }

        return bigVal - smallVal;
    }

public:
    int maxConsecutive(int bottom, int top, vector<int>& special) {
        priority_queue<int, vector<int>, greater<int>> specialFloorsMinHeap = createMinHeap(special);
        // clever simplification to model floors (below) bottom and (above) top also as special floors
        specialFloorsMinHeap.push(bottom - 1);
        specialFloorsMinHeap.push(top + 1);

        int maxConsecLen = 0;
        int prev = INT_MIN;
        while (!specialFloorsMinHeap.empty()) {
            int crr = specialFloorsMinHeap.top();

            // note the - 1 adjustment : because both prev and crr floor themselves are excluded
            int crrConsecLen = diff(prev, crr) - 1;
            maxConsecLen = max(maxConsecLen, crrConsecLen);

            prev = crr;
            specialFloorsMinHeap.pop();
        }

        return maxConsecLen;
    }
};
