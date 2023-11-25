// LeetCode-1033: https://leetcode.com/problems/moving-stones-until-consecutive

#include <tuple>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
private:
    tuple<int, int, int> sortPoints(int a, int b, int c) {
        int maxVal = max(max(a, b), c);
        int minVal = min(min(a, b), c);
        int midVal = (a + b + c) - (maxVal + minVal);
        return {minVal, midVal, maxVal};
    }

    int findMinGap(tuple<int, int, int> points) {
        return max(
                0,
                min(
                        get<1>(points) - get<0>(points),
                        get<2>(points) - get<1>(points)
                ) - 1
        );
    }

    int findMaxGap(tuple<int, int, int> points) {
        return max(
                0,
                max(
                        get<1>(points) - get<0>(points),
                        get<2>(points) - get<1>(points)
                ) - 1
        );
    }

public:
    vector<int> numMovesStones(int a, int b, int c) {
        tuple<int, int, int> points = sortPoints(a, b, c);
        int minGap = findMinGap(points);
        int maxGap = findMaxGap(points);

        if (maxGap <= 0) {
            return {0, 0};
        }

        /**
         * calculating min-moves
         * - if there's a 1-place separation between two points, that can be filled-up in 1-move only
         * - otherwise it'll take 2 moves: say we we have (a, b, c), we have multiple ways solving
         *   1. move c to b-1, so that we have (a, b-1, b) and then move a to b-2
         *   2. move c to b+1 and a to b-1
         */
        int minMoves = (minGap >= 2) ? 2 : 1;

        /**
         * calculating max-moves
         * for max-moves we'll always move edge stones just 1 posn at a time
         * so that effectively total no of moves will be just sum of total
         * separation -> total no of empty spaces b/w a & b + empty spaces b/w b & c
         */
        int maxMoves = minGap + maxGap;

        return {minMoves, maxMoves};
    }
};
