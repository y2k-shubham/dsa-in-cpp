// LeetCode-2126: https://leetcode.com/problems/destroying-asteroids/
// extremely dumb problem; please skip looking (humble request)

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());

        long long massLong = mass;
        for (int i = 0; i < asteroids.size(); i++) {
            if (massLong >= asteroids[i]) {
                massLong += asteroids[i];
            } else {
                return false;
            }
        }

        return true;
    }
};
