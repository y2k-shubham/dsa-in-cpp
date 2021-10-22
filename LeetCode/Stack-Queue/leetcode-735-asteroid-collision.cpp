// LeetCode-735: https://leetcode.com/problems/asteroid-collision/

#include <cstdio>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    // not greate performance: runtime 19 %tile, memory 36 %tile
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> finalState;
        stack<int> rightMovingAsteroids;

        for (int i = 0; i < asteroids.size(); i++) {
            int crrAsteroid = asteroids[i];
            bool rightMoving = crrAsteroid > 0;

            if (rightMoving) {
                // right moving asteroids will be added to stack (not immediately moved to final state)
                rightMovingAsteroids.push(crrAsteroid);
            } else {
                // left moving asteroids will continue to hit right moving ones
                while (!rightMovingAsteroids.empty() && (rightMovingAsteroids.top() < abs(crrAsteroid))) {
                    rightMovingAsteroids.pop();
                }

                if (rightMovingAsteroids.empty()) {
                    // if all right-moving asteroids (till now) are gone,
                    // that means left-moving asteroid made it to very left end ->
                    // it will show up in final state
                    finalState.push_back(crrAsteroid);
                } else if (rightMovingAsteroids.top() == abs(crrAsteroid)) {
                    // otherwise if the current right-moving asteroid is same-sized
                    // then that will be eliminated (along with the left-moving one)
                    rightMovingAsteroids.pop();
                } else {
                    // otherwise if the current right-moving asteroid is bigger-sized
                    // then it will sustain (left moving one will be eliminated)
                }
            }
        }

        // the right moving asteroids still left in stack
        // will make it to final state -> but we'll have to invert
        // their order than what is there in the stack
        list<int> remAsteroids;
        while (!rightMovingAsteroids.empty()) {
            remAsteroids.push_back(rightMovingAsteroids.top());
            rightMovingAsteroids.pop();
        }

        // we'll add all remaining right moving asteroids to final state
        while (!remAsteroids.empty()) {
            finalState.push_back(remAsteroids.back());
            remAsteroids.pop_back();
        }

        return finalState;
    }
};
