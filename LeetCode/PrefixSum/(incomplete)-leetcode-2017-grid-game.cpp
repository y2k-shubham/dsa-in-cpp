// LeetCode-2017: https://leetcode.com/problems/grid-game/
// incomplete: approach is correct; probably integer overflow somewhere (fails in only the biggest test cases)

#include <vector>
#include <climits>

#define NUM_ROWS 2

using namespace std;

class Solution {
private:
    vector<long long> buildPrefixSumVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {vec[0]};
        }

        vector<long long> prefSum(len);

        prefSum[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefSum[i] = prefSum[i - 1] + vec[i];
        }

        return prefSum;
    }

    vector<long long> buildSuffixSumVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {vec[0]};
        }

        vector<long long> suffSum(len);

        suffSum[len - 1] = vec[len - 1];
        for (int i = len - 2; i >= 0; i--) {
            suffSum[i] = suffSum[i + 1] + vec[i];
        }

        return suffSum;
    }

    vector<vector<long long> > buildPrefixSumGrid(vector<vector<int>>& grid) {
        vector<vector<long long>> prefSumGrid(NUM_ROWS);

        for (int i = 0; i < NUM_ROWS; i++) {
            vector<long long> prefSumVec = buildPrefixSumVec(grid[i]);
            prefSumGrid[i] = prefSumVec;
        }

        return prefSumGrid;
    }

    vector<vector<long long> > buildSuffixSumGrid(vector<vector<int>>& grid) {
        vector<vector<long long>> suffSumGrid(NUM_ROWS);

        for (int i = 0; i < NUM_ROWS; i++) {
            vector<long long> suffSumVec = buildSuffixSumVec(grid[i]);
            suffSumGrid[i] = suffSumVec;
        }

        return suffSumGrid;
    }

public:
    long long gridGame(vector<vector<int>>& grid) {
        vector<vector<long long> > prefSumGrid = buildPrefixSumGrid(grid);
        vector<vector<long long> > suffSumGrid = buildSuffixSumGrid(grid);

        int numCols = grid[0].size();
        long long minBScore = INT_MAX;

        for (int i = 0; i < numCols; i++) {
            // here we assume that A will jump from 1st row to 2nd row at column i

            long long bScoreBottomLeft = (i == 0) ? 0 : prefSumGrid[NUM_ROWS - 1][i - 1];
            long long bScoreTopRight = (i >= (numCols - 1)) ? 0 : suffSumGrid[0][i + 1];
            long long biggerBScore = max(bScoreBottomLeft, bScoreTopRight);

            minBScore = min(minBScore, biggerBScore);
        }

        return minBScore;
    }
};
