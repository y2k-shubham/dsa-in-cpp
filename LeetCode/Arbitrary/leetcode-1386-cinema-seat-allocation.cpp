// LeetCode-1386: https://leetcode.com/problems/cinema-seat-allocation/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showVec(vector<int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            printf("%d ", vec[i]);
        }
        cout << endl;
    }

    map<int, vector<int>> prepareRevSeatsMap(vector<vector<int>>& reservedSeats) {
        map<int, vector<int>> revSeatsMap;

        for (int i = 0; i < reservedSeats.size(); i++) {
            revSeatsMap[reservedSeats[i][0]].push_back(reservedSeats[i][1]);
        }

        return revSeatsMap;
    }

    // unused fn: misunderstood the problem (assumed that there are no aisle)
    int findMaxGroupsInRowMisunderstood(vector<int>& reservedSeats) {
        int numReservedSeats = reservedSeats.size();
        if (numReservedSeats >= 7) {
            return 0;
        }

        int numGroups = 0;
        int prevReservedSeat = 0;
        for (int i = 0; i < numReservedSeats; i++) {
            int crrReservedSeat = reservedSeats[i];

            int gap = crrReservedSeat - prevReservedSeat - 1;
            if (gap >= 4) {
                numGroups = gap / 4;
            }

            prevReservedSeat = crrReservedSeat;
        }

        return numGroups;
    }

    int findMaxGroupsInRow(vector<int>& reservedSeats) {
        vector<bool> row(11, true);

        for (int i = 0; i < reservedSeats.size(); i++) {
            row[reservedSeats[i]] = false;
        }

        int numGroups = 0;

        // check if group can be placed across 1st aisle
        bool firstAisle = row[2] && row[3] && row[4] && row[5];
        if (firstAisle) {
            numGroups++;
        }

        // check if group can be placed across 2nd aisle
        bool secondAisle = row[6] && row[7] && row[8] && row[9];
        if (secondAisle) {
            numGroups++;
        }

        // check ig group can be placed across middle section
        bool middleSection = !firstAisle && !secondAisle && (row[4] && row[5] && row[6] && row[7]);
        if (middleSection) {
            numGroups++;
        }

        return numGroups;
    }

    int findMaxGroupsInCinema(int totalRows, map<int, vector<int>>& revSeatsMap) {
        int maxGroups = 0;

        int prevReservedRow = 0;
        for (
            map<int, vector<int>>::iterator it = revSeatsMap.begin();
            it != revSeatsMap.end();
            it++) {
            int crrReservedRow = it->first;
            if (debug) {
                printf("\n--------\n");
                printf("at row=%d\n", crrReservedRow);
                showVec(it->second);
                cout << endl;
            }

            // all 'fully' empty rows since last reserved row (row having at least 1 reserved seat)
            // will each be able to take in 2 groups of 4-persons each
            int numFullyEmptyRows = crrReservedRow - prevReservedRow - 1;
            maxGroups += numFullyEmptyRows * 2;
            if (debug) {
                printf("contrib of fullyEmptyRows = %d x 2 = %d\n", numFullyEmptyRows, (2 * numFullyEmptyRows));
            }

            // determine no of groups that can be placed in current row
            maxGroups += findMaxGroupsInRow(it->second);
            if (debug) {
                printf("contrib of current row = %d\n", findMaxGroupsInRow(it->second));
                printf("totalGroups = %d\n", maxGroups);
            }

            // update prevReservedRow
            prevReservedRow = crrReservedRow;
        }

        if (prevReservedRow < totalRows) {
            // all 'fully' empty rows since last reserved row (row having at least 1 reserved seat)
            // will each be able to take in 2 groups of 4-persons each
            maxGroups += (totalRows - prevReservedRow) * 2;
            if (debug) {
                printf("\n--------\n");
                printf("at the end\n");
                printf("contrib of fullyEmptyRows = %d x 2 = %d\n", (totalRows - prevReservedRow), ((totalRows - prevReservedRow) * 2));
                printf("totalGroups = %d\n", maxGroups);
            }
        }

        return maxGroups;
    }

   public:
    friend class SolutionTest;

    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        sort(reservedSeats.begin(), reservedSeats.end());

        map<int, vector<int>> revSeatsMap = prepareRevSeatsMap(reservedSeats);
        return findMaxGroupsInCinema(n, revSeatsMap);
    }
};

class SolutionTest {
   public:
    void testMaxNumberOfFamilies() {
        Solution soln = Solution();
        int inN;
        vector<vector<int>> inReservedSeats;
        int outExpected, outComputed;

        // soln.debug = true;
        inN = 3;
        inReservedSeats = {{1, 2}, {1, 3}, {1, 8}, {2, 6}, {3, 1}, {3, 10}};
        outExpected = 4;
        outComputed = soln.maxNumberOfFamilies(inN, inReservedSeats);
        assert(outExpected == outComputed);
        // soln.debug = false;

        inN = 2;
        inReservedSeats = {{2, 1}, {1, 8}, {2, 6}};
        outExpected = 2;
        outComputed = soln.maxNumberOfFamilies(inN, inReservedSeats);
        assert(outExpected == outComputed);

        inN = 4;
        inReservedSeats = {{4, 3}, {1, 4}, {4, 6}, {1, 7}};
        outExpected = 4;
        outComputed = soln.maxNumberOfFamilies(inN, inReservedSeats);
        assert(outExpected == outComputed);

        // soln.debug = true;
        inN = 5;
        inReservedSeats = {{4, 7}, {4, 1}, {3, 1}, {5, 9}, {4, 4}, {3, 7}, {1, 3}, {5, 5}, {1, 6}, {1, 8}, {3, 9}, {2, 9}, {1, 4}, {1, 9}, {1, 10}};
        outExpected = 2;
        outComputed = soln.maxNumberOfFamilies(inN, inReservedSeats);
        assert(outExpected == outComputed);
        // soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxNumberOfFamilies();

    return 0;
}
