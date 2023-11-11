// LeetCode-2849: https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/
// making all functions 'inline' shaves off LC runtime from 4ms to 2ms
// unnecessary pair<int, int> wrapping should also help bring it down

// WARNING: the edge case is very tricky. (saw it in Editorial)
//  - if start=finish, then we cant reach in time t=1,
//  - but we can still reach for any time t>1 and even t=0

#include <vector>
#include <cassert>
#include <utility>

using namespace std;

class Solution {
private:
    bool areSamePoints(pair<int, int> start, pair<int, int> finish) {
        return (start.first == finish.first) && (start.second == finish.second);
    }

    bool is1DimensionalSeparation(pair<int, int> start, pair<int, int> finish) {
        return (start.first == finish.first) || (start.second == finish.second);
    }

    int findShortestPathLength(pair<int, int> start, pair<int, int> finish) {
        // technically even without this if-block we'll still get the correct answer
        // but it just simplifies reasoning to have it
        if (is1DimensionalSeparation(start, finish)) {
            return abs(finish.first - start.first) + abs(finish.second - start.second);
        }

        /**
         * "geometrically speaking with diagonal moves allowed, shortest distance will be
         * maximum of absolute difference between x or y coordinates"
         * 
         * why?
         * 
         * lets say points are 'vertically separated'
         * (meaning diff b/w y-coordinates > diff b/w x-coordinates)
         *  - then we could always start moving diagonally in vertical direction
         *  - each diagonal move from start to finish will eat away one unit
         *    distance from both x & y separations
         *  - diagonal path would end where we have reached to a point vertically
         *    aligned with finish point, so that further from there we only
         *    need to move vertically (not diagonally)
         *  mathematically it can be seen that no of moves then is equal to
         *  the vertical separation between points 
         */
        return max(abs(finish.first - start.first),
                   abs(finish.second - start.second));
    }

public:
    friend class SolutionTest;

    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        pair<int, int> start = {sx, sy};
        pair<int, int> finish = {fx, fy};

        /**
         * this edge case is very tricky.
         * - if start=finish, then we cant reach in time t=1,
         * - but we can still reach for any time t>1 and even t=0
         */
        if (areSamePoints(start, finish)) {
            return t != 1;
        }

        int shortestPathLength = findShortestPathLength(start, finish);

        /**
         * as long as alloted time is equal to or more than shortest path distance
         * it is possible to reach it in time 't'
         */
        return t >= shortestPathLength;
    }
};

class SolutionTest {
public:
    void testIs1DimensionalSeparation() {
        Solution soln = Solution();
        pair<int, int> start;
        pair<int, int> finish;
        bool outExpected, outComputed;

        start = {0, 0};
        finish = {0, 0};
        outExpected = true;
        outComputed = soln.is1DimensionalSeparation(start, finish);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        outExpected = true;
        outComputed = soln.is1DimensionalSeparation(start, finish);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {1, 19};
        outExpected = false;
        outComputed = soln.is1DimensionalSeparation(start, finish);
        assert(outExpected == outComputed);
    }

    void testFindShortestPathLength() {
        Solution soln = Solution();
        pair<int, int> start;
        pair<int, int> finish;
        int outExpected, outComputed;

        start = {0, 0};
        finish = {0, 0};
        outExpected = 0;
        outComputed = soln.findShortestPathLength(start, finish);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        outExpected = 13;
        outComputed = soln.findShortestPathLength(start, finish);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {1, 19};
        outExpected = 13;
        outComputed = soln.findShortestPathLength(start, finish);
        assert(outExpected == outComputed);
    }

    void testIsReachableAtTime() {
        Solution soln = Solution();
        pair<int, int> start;
        pair<int, int> finish;
        int time;
        bool outExpected, outComputed;

        start = {0, 0};
        finish = {0, 0};
        time = 0;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 0};
        finish = {0, 0};
        time = 1;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 0};
        finish = {0, 0};
        time = 2;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 0};
        finish = {0, 0};
        time = 3;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = 0;
        outExpected = false;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = 11;
        outExpected = false;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = 12;
        outExpected = false;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = 13;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = 14;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = 15;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {0, 19};
        time = INT_MAX;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {1, 19};
        time = 12;
        outExpected = false;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {0, 6};
        finish = {1, 19};
        time = 13;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {2, 4};
        finish = {7, 7};
        time = 6;
        outExpected = true;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);

        start = {3, 1};
        finish = {7, 3};
        time = 3;
        outExpected = false;
        outComputed = soln.isReachableAtTime(start.first, start.second, finish.first, finish.second, time);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testIs1DimensionalSeparation();
    solnTest.testFindShortestPathLength();
    solnTest.testIsReachableAtTime();

    return 0;
}
