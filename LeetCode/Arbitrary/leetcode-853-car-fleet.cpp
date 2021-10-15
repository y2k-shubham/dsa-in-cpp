// LeetCode-853: https://leetcode.com/problems/car-fleet/

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    int target;
    int precFactor;      // unused
    int precMultiplier;  // unused
    pair<int, int> zeroFract;
    pair<int, int> infFract;

    void init(int target) {
        this->target = target;
        this->precFactor = 4;                                   // unused
        this->precMultiplier = (int)pow(10, this->precFactor);  // unused
        this->zeroFract = {0, 1};
        this->infFract = {1, 0};
    }

    // unused
    float roundf(float num, int prec) {
        // https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
        float addend = 5 * pow(10, -(prec + 1));
        num += addend;

        float multiplier = pow(10, prec + 1);

        num *= multiplier;
        num = floor(num);
        num /= multiplier;

        return num;
    }

    int hcf(int n1, int n2) {
        int big = max(n1, n2);
        int small = min(n1, n2);

        int rem = (big % small);
        if (rem == 0) {
            return small;
        } else {
            return hcf(small, rem);
        }
    }

    pair<int, int> maxFract(pair<int, int> p1, pair<int, int> p2) {
        float f1 = ((float)p1.first) / p1.second;
        float f2 = ((float)p2.first) / p2.second;
        return (f1 > f2) ? p1 : p2;
    }

    pair<int, int> divFract(int numr, int denr) {
        int hcfVal = hcf(numr, denr);
        int reducedNumr = numr / hcfVal;
        int reducedDenr = denr / hcfVal;
        return {reducedNumr, reducedDenr};
    }

    pair<int, int> findPrecTime(int pos, int speed) {
        if (pos == this->target) {
            return this->zeroFract;
        }
        if (speed == 0) {
            return this->infFract;
        }

        int dist = this->target - pos;
        return divFract(dist, speed);
    }

    vector<pair<int, int> > findSortedPosSpeed(vector<int>& position, vector<int>& speed) {
        int len = position.size();
        vector<pair<int, int> > zippedVec(len);

        for (int i = 0; i < len; i++) {
            zippedVec[i] = {position[i], speed[i]};
        }

        sort(zippedVec.begin(), zippedVec.end());

        return zippedVec;
    }

   public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        init(target);

        int len = position.size();

        set<pair<int, int> > reachTimesSet;
        vector<pair<int, int> > reachTimesVec(len, this->infFract);

        // zip together positions & speeds and sort by positions
        vector<pair<int, int> > zippedVec = findSortedPosSpeed(position, speed);

        // determine reach time of last car (having highest posn + speed)
        pair<int, int> lastCarReachTime = findPrecTime(zippedVec[len - 1].first, zippedVec[len - 1].second);
        // update it's reach time in vector & set
        reachTimesVec[len - 1] = lastCarReachTime;
        reachTimesSet.insert(lastCarReachTime);

        // starting from forward-most car and going backwards
        for (int i = len - 2; i >= 0; i--) {
            // determine expected reach time of current car
            pair<int, int> crrCarExpectedReachTime = findPrecTime(zippedVec[i].first, zippedVec[i].second);
            // read calculated reach-time of next car (just ahead of it)
            pair<int, int> nextCarReachTime = reachTimesVec[i + 1];
            /**
             * - if next car is reaching early, then current car cant catch-up: so it's actual
             *   reach time will be same as expected reach time
             * - if next car is reaching later, then current car will catch-up. but still, final
             *   reach time of both cars will be same as the that of next one (higher)
             * - if next car is reaching at same time, then nothing to do
             * .
             * overall, actual reach time of current car will be maximum of it's expected reach time
             * and actual reach time of next car
             */
            pair<int, int> crrCarActualReachTime = maxFract(crrCarExpectedReachTime, nextCarReachTime);
            // update it's reach time in vector & set
            reachTimesVec[i] = crrCarActualReachTime;
            reachTimesSet.insert(crrCarActualReachTime);
        }

        // find no of unique reach times (we'll have those many different 'fleets' of car)
        int numReachTimes = reachTimesSet.size();
        // if we have infinite reach time (some sets of car had zero speed), then we'll exclude
        // all those cars (all those cars together will form a single fleet -> because when one
        // car stops, all others behind it will also have to stop)
        bool hasInfReachTime = reachTimesSet.find(this->infFract) != reachTimesSet.end();
        int numActualReachTimes = numReachTimes - (hasInfReachTime ? 1 : 0);

        return numActualReachTimes;
    }
};
