// LeetCode-475: https://leetcode.com/problems/heaters/

#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    void showVec(vector <int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    /**
     * Fuses positions of houses and heaters into a zingle list
     * @param houses positions of houses
     * @param heaters positions of heaters
     * @return a list of tuple[int, bool] where
     *         - int denotes position
     *         - bool = True means house and False means heater
     */
    vector <pair <int, bool>> createFusedVec(vector <int>& houses, vector <int>& heaters) {
        int numHouses = houses.size();
        int numHeaters = heaters.size();
        vector <pair <int, bool>> fusedVec(numHouses + numHeaters);

        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        int iFused = 0;
        int iHouses = 0;
        int iHeaters = 0;
        while ((iHouses < numHouses) && (iHeaters < numHeaters)) {
            if (houses[iHouses] <= heaters[iHeaters]) {
                fusedVec[iFused++] = {houses[iHouses++], true};
            } else {
                fusedVec[iFused++] = {heaters[iHeaters++], false};
            }
        }
        while (iHouses < numHouses) {
            fusedVec[iFused++] = {houses[iHouses++], true};
        }
        while (iHeaters < numHeaters) {
            fusedVec[iFused++] = {heaters[iHeaters++], false};
        }

        return fusedVec;
    }

    vector <int> createNextHeaterOnRightPosns(vector <pair <int, bool>>& housesAndHeatersPosns) {
        int len = housesAndHeatersPosns.size();
        vector <int> nextHeaterOnRightPosns(len);

        int nextHeaterOnRightPosn = INT_MAX;
        for (int i = len - 1; i >= 0; i--) {
            int crrPosn = housesAndHeatersPosns[i].first;

            if (!housesAndHeatersPosns[i].second) {
                nextHeaterOnRightPosn = crrPosn;
            }
            nextHeaterOnRightPosns[i] = nextHeaterOnRightPosn;
        }

        return nextHeaterOnRightPosns;
    }

    int calculateDistance(int posn1, int posn2) {
        int maxPosn = max(posn1, posn2);
        int minPosn = min(posn1, posn2);
        if (maxPosn == INT_MAX) {
            return INT_MAX;
        } else if (minPosn == INT_MIN) {
            return INT_MAX;
        } else {
            return (maxPosn - minPosn);
        }
    }

public:
    friend class SolutionTest;

    int findRadius(vector <int>& houses, vector <int>& heaters) {
        int numHouses = houses.size();
        int numHeaters = heaters.size();
        int totalLen = numHouses + numHeaters;

        vector <pair <int, bool>> housesAndHeatersPosns = createFusedVec(houses, heaters);
        vector <int> nextHeaterOnRightPosns = createNextHeaterOnRightPosns(housesAndHeatersPosns);

        int maxDistanceFromNearestHeater = INT_MIN;

        int prevHeaterOnLeftPosn = INT_MIN;
        for (int i = 0; i < totalLen; i++) {
            int crrPosn = housesAndHeatersPosns[i].first;
            if (!housesAndHeatersPosns[i].second) {
                prevHeaterOnLeftPosn = crrPosn;
                continue;
            }

            int distanceFromNearestHeaterOnLeft = calculateDistance(prevHeaterOnLeftPosn, crrPosn);
            int distanceFromNearestHeaterOnRight = calculateDistance(crrPosn, nextHeaterOnRightPosns[i]);
            int distanceFromNearestHeater = min(distanceFromNearestHeaterOnLeft, distanceFromNearestHeaterOnRight);

            maxDistanceFromNearestHeater = max(maxDistanceFromNearestHeater, distanceFromNearestHeater);
        }

        return maxDistanceFromNearestHeater;
    }
};

class SolutionTest {
public:
    void testCreateFusedVec() {
        Solution soln = Solution();
        vector <int> housesIn, heatersIn;
        vector <pair <int, bool>> housesAndHeatersPosnsOutExpected, housesAndHeatersPosnsOutComputed;


        housesIn = {1, 2, 3};
        heatersIn = {2};
        housesAndHeatersPosnsOutExpected = {
            {1, true},
            {2, true},
            {2, false},
            {3, true}
        };
        housesAndHeatersPosnsOutComputed = soln.createFusedVec(housesIn, heatersIn);
        assert(housesAndHeatersPosnsOutExpected == housesAndHeatersPosnsOutComputed);

        housesIn = {1, 2, 3, 4};
        heatersIn = {1, 4};
        housesAndHeatersPosnsOutExpected = {
            {1, true},
            {1, false},
            {2, true},
            {3, true},
            {4, true},
            {4, false}
        };
        housesAndHeatersPosnsOutComputed = soln.createFusedVec(housesIn, heatersIn);
        assert(housesAndHeatersPosnsOutExpected == housesAndHeatersPosnsOutComputed);

        housesIn = {1, 5};
        heatersIn = {2};
        housesAndHeatersPosnsOutExpected = {
            {1, true},
            {2, false},
            {5, true},
        };
        housesAndHeatersPosnsOutComputed = soln.createFusedVec(housesIn, heatersIn);
        assert(housesAndHeatersPosnsOutExpected == housesAndHeatersPosnsOutComputed);
    }

    void testCreateNextHeaterOnRightPosns() {
        Solution soln = Solution();
        vector <pair <int, bool>> housesAndHeatersPosnsIn;
        vector <int> nextHeaterOnRightPosnsOutExpected, nextHeaterOnRightPosnsOutComputed;

        housesAndHeatersPosnsIn = {
            {1, true},
            {2, true},
            {2, false},
            {3, true}
        };
        nextHeaterOnRightPosnsOutExpected = {2, 2, 2, INT_MAX};
        nextHeaterOnRightPosnsOutComputed = soln.createNextHeaterOnRightPosns(housesAndHeatersPosnsIn);
        assert(nextHeaterOnRightPosnsOutExpected == nextHeaterOnRightPosnsOutComputed);

        housesAndHeatersPosnsIn = {
            {1, true},
            {1, false},
            {2, true},
            {3, true},
            {4, true},
            {4, false}
        };
        nextHeaterOnRightPosnsOutExpected = {1, 1, 4, 4, 4, 4};
        nextHeaterOnRightPosnsOutComputed = soln.createNextHeaterOnRightPosns(housesAndHeatersPosnsIn);
        // soln.showVec(nextHeaterOnRightPosnsOutExpected, "nextHeaterOnRightPosnsOutExpected");
        // soln.showVec(nextHeaterOnRightPosnsOutComputed, "nextHeaterOnRightPosnsOutComputed");
        assert(nextHeaterOnRightPosnsOutExpected == nextHeaterOnRightPosnsOutComputed);

        housesAndHeatersPosnsIn = {
            {1, true},
            {2, false},
            {5, true},
        };
        nextHeaterOnRightPosnsOutExpected = {2, 2, INT_MAX};
        nextHeaterOnRightPosnsOutComputed = soln.createNextHeaterOnRightPosns(housesAndHeatersPosnsIn);
        assert(nextHeaterOnRightPosnsOutExpected == nextHeaterOnRightPosnsOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateFusedVec();
    solnTest.testCreateNextHeaterOnRightPosns();

    return 0;
}
