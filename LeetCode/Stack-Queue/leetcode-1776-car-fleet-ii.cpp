// LeetCode-1776: https://leetcode.com/problems/car-fleet-ii/
// Cherry-Coding: https://www.youtube.com/watch?v=SVW1bD_PN6A
// extremely hard problem

#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int len = cars.size();
        vector<double> collisionTimes(len, -1);
        stack<int> prevCarsStack;

        /**
         * note that we are taking all cars, starting from the very last car -> even though technically entire computation will get
         * skipped for it; this is so because we at least need to put last car into the stak
         */
        for (int i = len - 1; i >= 0; i--) {
            int crrCar = i;
            int crrCarPosn = cars[crrCar][0];
            int crrCarSpeed = cars[crrCar][1];

            // pop out all cars with which crrCar can never collide (directly)
            while (!prevCarsStack.empty() && (cars[prevCarsStack.top()][1] >= crrCarSpeed)) {
                prevCarsStack.pop();
            }

            // pop out all cars which will themselves collide with cars ahead before crrCar could collide with them
            while (!prevCarsStack.empty()) {
                int nextCar = prevCarsStack.top();
                int nextCarPosn = cars[nextCar][0];
                int nextCarSpeed = cars[nextCar][1];
                double nextCarCollisionTime = collisionTimes[nextCar];

                bool willNextCarCollideWithSomeCarAhead = nextCarCollisionTime >= 0;
                if (!willNextCarCollideWithSomeCarAhead) {
                    // if next car is not gonna collide with any other car, then that's the car
                    // with which we must calculate collision time
                    break;
                }

                int nextCarPosnDiff = nextCarPosn - crrCarPosn;
                int nextCarSpeedDiff = crrCarSpeed - nextCarSpeed;
                double crrCarCollisionTime = ((double)nextCarPosnDiff) / nextCarSpeedDiff;

                bool willCrrCarCollideWithNextCarBeforeNextCarHasCollidedWithSomeCarAhead = crrCarCollisionTime < nextCarCollisionTime;
                if (willCrrCarCollideWithNextCarBeforeNextCarHasCollidedWithSomeCarAhead) {
                    // if next car's collision with the car ahead is gonna happen aftet it's collision with crrCar
                    // then also that's the car with which we must calculate collision time
                    break;
                }

                prevCarsStack.pop();
            }

            // calculate collision time of crrCar with the next car of the remaining lot (if any)
            if (!prevCarsStack.empty()) {
                int nextCar = prevCarsStack.top();
                int nextCarPosn = cars[nextCar][0];
                int nextCarSpeed = cars[nextCar][1];

                int nextCarPosnDiff = nextCarPosn - crrCarPosn;
                int nextCarSpeedDiff = crrCarSpeed - nextCarSpeed;

                double crrCarCollisionTime = ((double)nextCarPosnDiff) / nextCarSpeedDiff;
                collisionTimes[crrCar] = crrCarCollisionTime;
            }

            // put crrCar in stack
            prevCarsStack.push(crrCar);
        }

        return collisionTimes;
    }
};
