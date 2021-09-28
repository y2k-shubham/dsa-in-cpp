// LeetCode-1631: https://leetcode.com/problems/path-with-minimum-effort/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug;

    void enableDebug() {
        this->debug = true;
    }

    void disableDebug() {
        this->debug = false;
    }

    bool shouldDebug() {
        return this->debug;
    }

    void showMat(vector<vector<int>>& mat, string name) {
        int rows = mat.size();
        int cols = mat[0].size();

        printf("\n%s mat is:-\n", name.c_str());

        printf("\t");
        for (int i = 0; i < cols; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = 0; i < rows; i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] == INT_MAX) {
                    printf("-\t");
                } else {
                    printf("%d\t", mat[i][j]);
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void showMat(vector<vector<bool>>& mat, string name) {
        int rows = mat.size();
        int cols = mat[0].size();

        printf("\n%s mat is:-\n", name.c_str());

        printf("\t");
        for (int i = 0; i < cols; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = 0; i < rows; i++) {
            printf("[%d]\t", i);
            for (int j = 0; j < cols; j++) {
                if (mat[i][j]) {
                    printf("T\t");
                } else {
                    printf(".\t");
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void showPQue(
        vector<vector<int>>& heights,
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pQue) {
        printf("\npQue is:-\n");
        while (!pQue.empty()) {
            int sortingDist;
            int r, c;

            tie(sortingDist, r, c) = pQue.top();
            pQue.pop();

            printf("%d: [%d][%d] = %d\n", sortingDist, r, c, heights[r][c]);
        }
    }

    vector<vector<bool>> preparePushedMat(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<bool>> pushedMat(rows);
        for (int i = 0; i < rows; i++) {
            vector<bool> pushedVec(cols, false);
            pushedMat[i] = pushedVec;
        }

        return pushedMat;
    }

    vector<vector<int>> prepareEffortMat(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<int>> effortMat(rows);
        for (int i = 0; i < rows; i++) {
            vector<int> effortVec(cols, INT_MAX);
            effortMat[i] = effortVec;
        }

        return effortMat;
    }

    int findSum(int val1, int val2) {
        if (max(val1, val2) == INT_MAX) {
            return INT_MAX;
        }

        return val1 + val2;
    }

    int findAbsDiff(int val1, int val2) {
        if (max(val1, val2) == INT_MAX) {
            return INT_MAX;
        }

        return abs(val1 - val2);
    }

    int findMinEffortToReach(vector<vector<int>>& heights, vector<vector<int>>& effortMat, int r, int c) {
        int rows = heights.size();
        int cols = heights[0].size();

        int minEffort = effortMat[r][c];

        // from left
        if (c > 0) {
            minEffort = min(minEffort, max(effortMat[r][c - 1], findAbsDiff(heights[r][c], heights[r][c - 1])));
        }
        // from right
        if (c < (cols - 1)) {
            minEffort = min(minEffort, max(effortMat[r][c + 1], findAbsDiff(heights[r][c], heights[r][c + 1])));
        }
        // from top
        if (r > 0) {
            minEffort = min(minEffort, max(effortMat[r - 1][c], findAbsDiff(heights[r][c], heights[r - 1][c])));
        }
        // from bottom
        if (r < (rows - 1)) {
            minEffort = min(minEffort, max(effortMat[r + 1][c], findAbsDiff(heights[r][c], heights[r + 1][c])));
        }

        return minEffort;
    }

    void pushAdjCellsToQue(
        vector<vector<int>>& heights,
        vector<vector<int>>& effortMat,
        vector<vector<bool>>& pushedMat,
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>>& pQue,
        int r,
        int c) {
        int rows = heights.size();
        int cols = heights[0].size();

        int cellDist = effortMat[r][c];
        int cellHeight = heights[r][c];
        int newDist;

        // push left
        if ((c > 0) && !pushedMat[r][c - 1] && (newDist = max(cellDist, findAbsDiff(cellHeight, heights[r][c - 1])) < effortMat[r][c - 1])) {
            pushedMat[r][c - 1] = true;
            pQue.push({newDist, r, c - 1});
        }
        // push right
        if ((c < (cols - 1)) && !pushedMat[r][c + 1] && (newDist = max(cellDist, findAbsDiff(cellHeight, heights[r][c + 1])) < effortMat[r][c + 1])) {
            pushedMat[r][c + 1] = true;
            pQue.push({newDist, r, c + 1});
        }
        // push top
        if ((r > 0) && !pushedMat[r - 1][c] && (newDist = max(cellDist, findAbsDiff(cellHeight, heights[r - 1][c])) < effortMat[r - 1][c])) {
            pushedMat[r - 1][c] = true;
            pQue.push({newDist, r - 1, c});
        }
        // push bottom
        if ((r < (rows - 1)) && !pushedMat[r + 1][c] && (newDist = max(cellDist, findAbsDiff(cellHeight, heights[r + 1][c])) < effortMat[r + 1][c])) {
            pushedMat[r + 1][c] = true;
            pQue.push({newDist, r + 1, c});
        }
    }

   public:
    friend class SolutionTest;

    int minimumEffortPath(vector<vector<int>>& heights) {
        if (heights.empty()) {
            return 0;
        }

        vector<vector<bool>> pushedMat = preparePushedMat(heights);
        vector<vector<int>> effortMat = prepareEffortMat(heights);

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pQue;

        effortMat[0][0] = 0;
        pQue.push({0, 0, 0});
        pushedMat[0][0] = true;

        if (shouldDebug()) {
            printf("\n--------\n");
            printf("after init\n");
            showMat(heights, "heights");
            showMat(effortMat, "effortMat");
            showMat(pushedMat, "pushedMat");
            showPQue(heights, pQue);
        }

        while (!pQue.empty()) {
            int sortingDist;
            int r, c;

            tie(sortingDist, r, c) = pQue.top();
            pQue.pop();
            pushedMat[r][c] = false;

            // note that using sortingDist in place of newDist gives wrong answer (maybe some corner cases are left-out)
            int newDist = findMinEffortToReach(heights, effortMat, r, c);
            if ((newDist < effortMat[r][c]) || (newDist == 0)) {
                effortMat[r][c] = newDist;
                pushAdjCellsToQue(heights, effortMat, pushedMat, pQue, r, c);
            }

            if (shouldDebug()) {
                printf("\n--------\n");
                showMat(heights, "heights");
                showMat(effortMat, "effortMat");
                showMat(pushedMat, "pushedMat");
                showPQue(heights, pQue);
            }
        }

        int rows = heights.size();
        int cols = heights[0].size();
        return effortMat[rows - 1][cols - 1];
    }
};

class SolutionTest {
   public:
    void testMinimumEffortPath() {
        Solution soln = Solution();
        vector<vector<int>> heights;
        int effOutExpected, effOutComputed;

        heights = {};
        effOutExpected = 0;
        effOutComputed = soln.minimumEffortPath(heights);
        assert(effOutExpected == effOutComputed);

        // soln.enableDebug();
        heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
        effOutExpected = 2;
        effOutComputed = soln.minimumEffortPath(heights);
        assert(effOutExpected == effOutComputed);
        // soln.disableDebug();

        heights = {{1, 2, 3}, {3, 8, 4}, {5, 3, 5}};
        effOutExpected = 1;
        effOutComputed = soln.minimumEffortPath(heights);
        assert(effOutExpected == effOutComputed);

        heights = {{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}};
        effOutExpected = 0;
        effOutComputed = soln.minimumEffortPath(heights);
        assert(effOutExpected == effOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testMinimumEffortPath();
    return 0;
}
