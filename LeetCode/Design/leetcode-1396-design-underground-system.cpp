// LeetCode-1396: https://leetcode.com/problems/design-underground-system/
// extremely lame problem; dont bother looking

#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

class UndergroundSystem {
   private:
    map<pair<string, string>, pair<int, int> > stationAggTimes;
    unordered_map<int, pair<string, int> > customerCheckinTimes;

   public:
    UndergroundSystem() {
    }

    void checkIn(int id, string stationName, int t) {
        this->customerCheckinTimes[id] = {stationName, t};
    }

    void checkOut(int id, string stationName, int t) {
        pair<string, int> checkinTuple = this->customerCheckinTimes[id];
        string srcStation = checkinTuple.first;
        int checkinTime = checkinTuple.second;

        int travTime = t - checkinTime;

        pair<string, string> stationTuple = {srcStation, stationName};
        pair<int, int> crrAgg = this->stationAggTimes[stationTuple];

        this->stationAggTimes[{srcStation, stationName}] = {
            crrAgg.first + travTime,
            crrAgg.second + 1};
    }

    double getAverageTime(string startStation, string endStation) {
        pair<string, string> stationTuple = {startStation, endStation};
        pair<int, int> crrAgg = this->stationAggTimes[stationTuple];

        return ((double)crrAgg.first) / crrAgg.second;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
