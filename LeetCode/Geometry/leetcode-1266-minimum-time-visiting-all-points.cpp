// LeetCode-1266: https://leetcode.com/problems/minimum-time-visiting-all-points/

#include <vector>
#include <utility>

using namespace std;

class Solution {
private:
    // ------calculate using pair (without inline); LC runtime 33ms ------
    int calcMoveSteps(pair<int, int> p1, pair<int, int> p2) {
        return max(abs(p1.first - p2.first), abs(p1.second - p2.second));
    }

    int calcMinTimeToVisitAllPointsUsingPairs(vector<vector<int>>& points) {
        int totalSteps = 0;

        for (int i = 1; i < points.size(); i++) {
            totalSteps += calcMoveSteps(
                    {points[i - 1][0], points[i - 1][1]},
                    {points[i][0], points[i][1]}
            );
        }

        return totalSteps;
    }

    // ------ calculate using vector (with inline); LC runtime 3ms ------
    inline int calcMoveSteps(vector<int>& p1, vector<int>& p2) {
        return max(abs(p1[0] - p2[0]), abs(p1[1] - p2[1]));
    }

    int calcMinTimeToVisitAllPointsUsingVectors(vector<vector<int>>& points) {
        int totalSteps = 0;

        for (int i = 1; i < points.size(); i++) {
            totalSteps += calcMoveSteps(points[i - 1], points[i]);
        }

        return totalSteps;
    }

public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        // return calcMinTimeToVisitAllPointsUsingPairs(points);
        return calcMinTimeToVisitAllPointsUsingVectors(points);
    }
};
