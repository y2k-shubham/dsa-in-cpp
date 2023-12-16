// LeetCode-1503: https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/
// AlgoMasster: https://algo.monster/liteproblems/1503

#include <vector>

using namespace std;

class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int minPosRightMovingAnts = right.empty() ? INT_MAX : *min_element(right.begin(), right.end());
        int maxPosLeftMovingAnts = left.empty() ? INT_MIN : *max_element(left.begin(), left.end());

        int maxTimeRightMovingAnts = (minPosRightMovingAnts == INT_MAX) ? 0 : (n - minPosRightMovingAnts);
        int maxTimeLeftMovingAnts = (maxPosLeftMovingAnts == INT_MIN) ? 0 : maxPosLeftMovingAnts;

        return max(maxTimeLeftMovingAnts, maxTimeRightMovingAnts);
    }
};


