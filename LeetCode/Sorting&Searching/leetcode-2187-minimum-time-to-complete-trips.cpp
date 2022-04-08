// LeetCode-2187: https://leetcode.com/problems/minimum-time-to-complete-trips/

#include <vector>
#include <map>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    map<int, int> buildFreqMap(vector<int>& vec) {
        map<int, int> freqMap;
        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    long long calcRoughUpperBoundTime(map<int, int>& timeFreqMap, int totalTrips) {
        map<int, int>::iterator it = timeFreqMap.begin();
        int fastestBusTime = it->first;
        int fastestBusCount = it->second;

        long long numTripBatches = (long long) ceil((totalTrips * 1.0) / fastestBusCount);
        int timePerTripBatch = fastestBusTime;
        return numTripBatches * timePerTripBatch;
    }

    bool canTakeNumTripsInTime(map<int, int>& timeFreqMap, long long time, long long reqNumTripsTotal) {
        long long achievedNumTripsTotal = 0;
        for (map<int, int>::iterator it = timeFreqMap.begin(); it != timeFreqMap.end(); it++) {
            int crrBusTime = it->first;
            int crrBusCount = it->second;

            long long crrBusNumTripBatches = (long long) floor((time * 1.0) / crrBusTime);
            long long crrBusNumTrips = crrBusNumTripBatches * crrBusCount;

            achievedNumTripsTotal += crrBusNumTrips;
            if (achievedNumTripsTotal >= reqNumTripsTotal) {
                return true;
            }
        }

        return (achievedNumTripsTotal >= reqNumTripsTotal);
    }

public:
    friend class SolutionTest;

    // barely accepted; speed 5 %tile, memory 5 %tile
    long long minimumTime(vector<int>& time, int totalTrips) {
        map<int, int> timeFreqMap = buildFreqMap(time);

        long long fastestBusTime = timeFreqMap.begin()->first;
        long long roughMaxTime = calcRoughUpperBoundTime(timeFreqMap, totalTrips);

        long long minActualTime = LONG_MAX;
        long long loTime = fastestBusTime;
        long long hiTime = roughMaxTime;
        while (loTime <= hiTime) {
            long long midTime = (loTime + hiTime) / 2;
            if (canTakeNumTripsInTime(timeFreqMap, midTime, totalTrips)) {
                minActualTime = min(minActualTime, midTime);
                hiTime = midTime - 1;
            } else {
                loTime = midTime + 1;
            }
        }

        return minActualTime;
    }
};

class SolutionTest {
public:
    void testCalcRoughUpperBoundTime() {
        Solution soln = Solution();
        map<int, int> freqMapIn;
        int totalTripsIn;
        long long ubOutExpected, ubOutComputed;

        freqMapIn = {{3, 4}};
        totalTripsIn = 1;
        ubOutExpected = 3;
        ubOutComputed = soln.calcRoughUpperBoundTime(freqMapIn, totalTripsIn);
        assert(ubOutExpected == ubOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcRoughUpperBoundTime();

    return 0;
}
