// LeetCode-3111: https://leetcode.com/problems/minimum-rectangles-to-cover-points/

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
private:
    vector <int> getXCoords(vector <vector <int>>& points) {
        int len = points.size();
        vector <int> xCoords(len);

        for (int i = 0; i < len; i++) {
            xCoords[i] = points[i][0];
        }

        return xCoords;
    }

    int swallowPointsTillLimit(vector <int>& xCoords, int startIdx, int limitVal) {
        int i;
        for (i = startIdx; (i < xCoords.size()) && (xCoords[i] <= limitVal); i++) {}

        return i;
    }

public:
    int minRectanglesToCoverPoints(vector <vector <int>>& points, int w) {
        int len = points.size();
        if (len <= 1) {
            return len;
        }

        vector <int> xCoords = getXCoords(points);
        sort(xCoords.begin(), xCoords.end());

        if ((xCoords[len - 1] - xCoords[0]) <= w) {
            return 1;
        }

        int numRectangles = 0;
        int i = 0;
        int limit = xCoords[0] + w;
        while (i < len) {
            int iNew = swallowPointsTillLimit(xCoords, i, limit);

            numRectangles++;
            if (iNew >= len) {
                break;
            }

            limit = xCoords[iNew] + w;
            i = iNew;
        }

        return numRectangles;
    }
};
