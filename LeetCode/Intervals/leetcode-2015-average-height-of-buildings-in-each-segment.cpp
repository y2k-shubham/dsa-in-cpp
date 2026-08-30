// LeetCode-2015: https://leetcode.com/problems/average-height-of-buildings-in-each-segment/
// Premium
// Medium difficulty, but time consuming to implement
// Almost identical to, though slightly more difficult (requires merging of segments), than LeetCode-1943: https://leetcode.com/problems/describe-the-painting/

#include <vector>
#include <map>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
private:
    void showBuildingsMap(map <int, pair <int, int> >& buildingsMap) {
        printf("buildingsMap is:-\n");

        for (auto it : buildingsMap) {
            printf("%d : [%d] / %d\n", it.first, it.second.first, it.second.second);
        }
    }

    map <int, pair <int, int> > createBuildingsMap(vector<vector<int>>& buildings) {
        map <int, pair <int, int> > buildingsMap;

        for (vector<int>& building : buildings) {
            int start = building[0];
            int end = building[1];
            int height = building[2];

            buildingsMap[start].first += height;
            buildingsMap[start].second++;

            buildingsMap[end].first -= height;
            buildingsMap[end].second--;
        }

        return buildingsMap;
    }

    vector<vector<int>> createAvgHeightOfBuildingsVec(map <int, pair <int, int> >& buildingsMap) {
        vector<vector<int>> avgHeightOfBuildingsVec;

        auto it = buildingsMap.begin();
        int prevMark = it->first;
        int prevHeight = it->second.first;
        int prevNumBuildings = it->second.second;
        for (it++; (it != buildingsMap.end()); it++) {
            int newMark = it->first;
            int newHeight = prevHeight + it->second.first;
            int newNumBuildings = prevNumBuildings + it->second.second;

            if (prevHeight > 0) {
                pair <int, int> spanMarks = {prevMark, newMark};
                int avgHeight = prevHeight / prevNumBuildings;
                vector <int> avgHeightOfBuildingsVal = {spanMarks.first, spanMarks.second, avgHeight};
                avgHeightOfBuildingsVec.push_back(avgHeightOfBuildingsVal);
            }

            prevMark = newMark;
            prevHeight = newHeight;
            prevNumBuildings = newNumBuildings;
        }

        return avgHeightOfBuildingsVec;
    }

    int swallowItemsTillRangesCombine(vector<vector<int>>& avgHeightOfBuildingsVec, int i) {
        int len = avgHeightOfBuildingsVec.size();
        int height = avgHeightOfBuildingsVec[i][2];

        int prevEnd = avgHeightOfBuildingsVec[i][1];
        int j = i + 1;
        while (
            (j < len)                                       // bounds not violated
            && (avgHeightOfBuildingsVec[j][2] == height)    // height is same
            && (avgHeightOfBuildingsVec[j][0] == prevEnd)   // range is contiguous
        ) {
            prevEnd = avgHeightOfBuildingsVec[j][1];
            j++;
        }

        return j;
    }

    vector<vector<int>> combineRanges(vector<vector<int>>& avgHeightOfBuildingsVec) {
        vector<vector<int>> combinedBuildingsVec;

        for (int i = 0; i < avgHeightOfBuildingsVec.size(); i++) {
            pair <int, int> iSpan = {avgHeightOfBuildingsVec[i][0], avgHeightOfBuildingsVec[i][1]};
            int iHeight = avgHeightOfBuildingsVec[i][2];

            int j = swallowItemsTillRangesCombine(avgHeightOfBuildingsVec, i);

            vector <int> span;
            if (j > (i + 1)) {
                // found range [i .. j-1] to be combined
                pair <int, int> jMinus1Span = {avgHeightOfBuildingsVec[j-1][0], avgHeightOfBuildingsVec[j-1][1]};
                pair <int, int> spanMarks = {iSpan.first, jMinus1Span.second};
                span = {spanMarks.first, spanMarks.second, iHeight};

                // jump i to skip all ranges of merged span
                i = j - 1;
            } else {
                span = {iSpan.first, iSpan.second, iHeight};
            }

            combinedBuildingsVec.push_back(span);
        }

        return combinedBuildingsVec;
    }

public:
    friend class SolutionTest;

    vector<vector<int>> averageHeightOfBuildings(vector<vector<int>>& buildings) {
        int numBuildings = buildings.size();
        if (numBuildings <= 1) {
            return buildings;
        }

        map <int, pair <int, int> > buildingsMap = createBuildingsMap(buildings);
        // showBuildingsMap(buildingsMap);

        vector<vector<int>> avgHeightOfBuildingsVec = createAvgHeightOfBuildingsVec(buildingsMap);

        vector<vector<int>> combinedBuildingsVec = combineRanges(avgHeightOfBuildingsVec);
        return combinedBuildingsVec;
    }
};

class SolutionTest {
public:
    void testCreateBuildingsMap() {
        Solution soln = Solution();
        vector<vector<int>> buildingsIn;
        map <int, pair <int, int> > buildingsMapOutExpected, buildingsMapOutComputed;

        buildingsIn = {{1,4,2},{3,9,4}};
        buildingsMapOutExpected = {
            {1, {2, 1}},
            {3, {4, 1}},
            {4, {-2, -1}},
            {9, {-4, -1}}
        };
        buildingsMapOutComputed = soln.createBuildingsMap(buildingsIn);
        assert(buildingsMapOutExpected == buildingsMapOutComputed);

        buildingsIn = {{1,3,2},{2,5,3},{2,8,3}};
        buildingsMapOutExpected = {
            {1, {2, 1}},
            {2, {6, 2}},
            {3, {-2, -1}},
            {5, {-3, -1}},
            {8, {-3, -1}}
        };
        buildingsMapOutComputed = soln.createBuildingsMap(buildingsIn);
        assert(buildingsMapOutExpected == buildingsMapOutComputed);

        buildingsIn = {{1,2,1},{5,6,1}};
        buildingsMapOutExpected = {
            {1, {1, 1}},
            {2, {-1, -1}},
            {5, {1, 1}},
            {6, {-1, -1}}
        };
        buildingsMapOutComputed = soln.createBuildingsMap(buildingsIn);
        assert(buildingsMapOutExpected == buildingsMapOutComputed);
    }

    void testCombineRanges() {
        Solution soln = Solution();
        vector<vector<int>> rangesIn;
        vector<vector<int>> rangesOutExpected, rangesOutComputed;

        rangesIn = {{1,3,2},{3,4,3},{4,9,4}};
        rangesOutExpected = {{1,3,2},{3,4,3},{4,9,4}};
        rangesOutComputed = soln.combineRanges(rangesIn);
        assert(rangesOutExpected == rangesOutComputed);

        rangesIn = {{1, 2, 2}, {2, 3, 2}, {3, 5, 3}, {5, 8, 3}};
        rangesOutExpected = {{1, 3, 2}, {3, 8, 3}};
        rangesOutComputed = soln.combineRanges(rangesIn);
        assert(rangesOutExpected == rangesOutComputed);

        rangesIn = {{1,2,1},{5,6,1}};
        rangesOutExpected = {{1,2,1},{5,6,1}};
        rangesOutComputed = soln.combineRanges(rangesIn);
        assert(rangesOutExpected == rangesOutComputed);
    }

    void testAverageHeightOfBuildingsVec() {
        Solution soln = Solution();
        vector<vector<int>> buildingsIn;
        vector<vector<int>> avgHeightOfBuildingsVecOutExpected, avgHeightOfBuildingsVecOutComputed;

        buildingsIn = {{1,4,2},{3,9,4}};
        avgHeightOfBuildingsVecOutExpected = {{1,3,2},{3,4,3},{4,9,4}};
        avgHeightOfBuildingsVecOutComputed = soln.averageHeightOfBuildings(buildingsIn);
        assert(avgHeightOfBuildingsVecOutExpected == avgHeightOfBuildingsVecOutComputed);

        buildingsIn = {{1,3,2},{2,5,3},{2,8,3}};
        avgHeightOfBuildingsVecOutExpected = {{1, 3, 2}, {3, 8, 3}};
        avgHeightOfBuildingsVecOutComputed = soln.averageHeightOfBuildings(buildingsIn);
        assert(avgHeightOfBuildingsVecOutExpected == avgHeightOfBuildingsVecOutComputed);

        buildingsIn = {{1,2,1},{5,6,1}};
        avgHeightOfBuildingsVecOutExpected = {{1,2,1},{5,6,1}};
        avgHeightOfBuildingsVecOutComputed = soln.averageHeightOfBuildings(buildingsIn);
        assert(avgHeightOfBuildingsVecOutExpected == avgHeightOfBuildingsVecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateBuildingsMap();
    solnTest.testCombineRanges();
    solnTest.testAverageHeightOfBuildingsVec();

    return 0;
}
