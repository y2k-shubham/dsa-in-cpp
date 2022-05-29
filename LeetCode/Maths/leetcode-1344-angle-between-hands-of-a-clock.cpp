// LeetCode-1344: https://leetcode.com/problems/angle-between-hands-of-a-clock/

#include <iostream>
#include <cmath>

using namespace std;

class Solution {
public:
    // solution by GitHub CoPilot (runtime 0 ms)
    double angleClock1(int hour, int minutes) {
        double hour_angle = (hour % 12 + minutes / 60.0) * 30;
        double minute_angle = minutes * 6;
        double angle = abs(hour_angle - minute_angle);
        return min(angle, 360 - angle);
    }

    // own solution (runtime 3 ms)
    double angleClock2(int hour, int minutes) {
        double minuteAngle = (minutes / 60.0) * 360;

        double hourAngle = (hour == 12) ? 0 : ((hour / 12.0) * 360);
        hourAngle += (minutes / 60.0) * 30;

        double delta = abs(minuteAngle - hourAngle);
        return min(delta, 360 - delta);
    }

    double angleClock(int hour, int minutes) {
        return angleClock2(hour, minutes);
    }
};
