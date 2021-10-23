// LeetCode-1776: https://leetcode.com/problems/car-fleet-ii/
// wrong soln

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int len = cars.size();

        vector<double> collisionTimes(len, -1.0);

        vector<int> finalSpeed(len, 0);
        finalSpeed[len - 1] = cars[len - 1][1];

        for (int i = len - 2; i >= 0; i--) {
            int carsInitialDistance = cars[i + 1][0] - cars[i][0];
            int crrCarSpeed = cars[i][1];
            int nextCarInitialSpeed = cars[i + 1][1];
            int nextCarFinalSpeed = finalSpeed[i + 1];
            int initialSpeedDiff = crrCarSpeed - nextCarInitialSpeed;
            int finalSpeedDiff = crrCarSpeed - nextCarFinalSpeed;

            if (crrCarSpeed > nextCarFinalSpeed) {
                // there will be a collision
                if (initialSpeedDiff < 0) {
                    // collision b/w i & i+1th cars will happen after collision b/w i+1th & i+2th cars
                    double totalDistance = carsInitialDistance + (abs(initialSpeedDiff) * collisionTimes[i + 1]);
                    collisionTimes[i] = totalDistance / crrCarSpeed;
                } else {
                    /**
                     * here we could have either of 2 cases
                     * 1. (tougher) either the collision b/w i & i+1th cars will happen after collision b/w i+1th & i+2th cars
                     * 2. (easier) or the collision b/w i & i+1th cars will happen before (or together) collision b/w i+1th & i+2th cars
                     */

                    double initialcollisionTime = (initialSpeedDiff == 0) ? INT_MAX : ((carsInitialDistance * 1.0) / initialSpeedDiff);
                    if (initialSpeedDiff == finalSpeedDiff) {
                        // collision b/w i & i+1th cars will happen in simplest way because speed of i+1th car is not changing with time
                        collisionTimes[i] = initialcollisionTime;
                    } else {
                        // it necessarily means that finalSpeedDiff < initialSpeedDiff
                        // (since the reverse is impossible as cars never speed up -> they only slow down)
                        if ((collisionTimes[i + 1] < 0) || (initialcollisionTime <= collisionTimes[i + 1])) {
                            // simple: collision b/w i & i+1th cars will happen before (or together) collision b/w i+1th & i+2th cars
                            collisionTimes[i] = initialcollisionTime;
                        } else {
                            // tough: collision b/w i & i+1th cars will happen after collision b/w i+1th & i+2th cars
                            double nextCarCollisionTime = collisionTimes[i + 1];

                            double extraDistance = nextCarCollisionTime * initialSpeedDiff;
                            double remainingDistance = carsInitialDistance - extraDistance;

                            double crrCarcollisionTime = nextCarCollisionTime + (remainingDistance / finalSpeedDiff);
                            collisionTimes[i] = crrCarcollisionTime;
                        }
                    }
                }

                finalSpeed[i] = nextCarFinalSpeed;
            } else {
                // no collision
            }
        }

        return collisionTimes;
    }
};
