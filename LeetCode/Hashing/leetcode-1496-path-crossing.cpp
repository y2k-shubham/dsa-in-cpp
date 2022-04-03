// LeetCode-1496: https://leetcode.com/problems/path-crossing/

#include <iostream>
#include <unordered_set>
#include <sstream>

using namespace std;

class Solution {
private:
    string convertToStr(ostringstream& oss, pair<int, int> p) {
        oss.str("");
        oss << p.first << "," << p.second;
        return oss.str();
    }

public:
    bool isPathCrossing(string path) {
        ostringstream oss;
        unordered_set<string> visitedPoints;

        pair<int, int> crrPoint = {0, 0};
        visitedPoints.insert(convertToStr(oss, crrPoint));

        for (int i = 0; i < path.size(); i++) {
            switch (path.at(i)) {
                case 'E':
                    crrPoint.second++;
                    break;

                case 'W':
                    crrPoint.second--;
                    break;

                case 'N':
                    crrPoint.first++;
                    break;

                case 'S':
                    crrPoint.first--;
                    break;

                default:
                    break;
            }

            string crrPointStr = convertToStr(oss, crrPoint);
            if (visitedPoints.find(crrPointStr) != visitedPoints.end()) {
                return true;
            }

            visitedPoints.insert(crrPointStr);
        }

        return false;
    }
};
