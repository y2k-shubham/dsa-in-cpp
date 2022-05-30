// LeetCode-539: https://leetcode.com/problems/minimum-time-difference/

#include <cstdio>
#include <iostream>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;

#define MIN_DIG '0'
#define MINS_IN_DAY 1440

class Solution {
private:
    int extractInt(string& str, int lo, int hi) {
        int num = 0;

        for (int i = lo; i <= hi; i++) {
            char dig = str.at(i);
            num *= 10;
            num += dig - MIN_DIG;
        }

        return num;
    }

    int convertToMinutes(string& time) {
        int hours = extractInt(time, 0, 1);
        int minutes = extractInt(time, 3, 4);
        // printf("for time=%s, hours=%d, minutes=%d, totalMinutes=%d\n", time.c_str(), hours, minutes, ((hours * 60) + minutes));

        return (hours * 60) + minutes;
    }

    vector<int> convertToMinutePoints(vector<string>& timePoints) {
        int len = timePoints.size();

        vector<int> minutePoints(len);
        for (int i = 0; i < len; i++) {
            minutePoints[i] = convertToMinutes(timePoints[i]);
        }

        return minutePoints;
    }

    int calcDiff(int minutes1, int minutes2) {
        int crrDiff = max(minutes1, minutes2) - min(minutes1, minutes2);
        crrDiff = min(crrDiff, MINS_IN_DAY - crrDiff);
        return crrDiff;
    }

    int findMinConsecDiff(vector<int>& vec) {
        int minConsecDiff = INT_MAX;

        for (int i = 1; i < vec.size(); i++) {
            int crrDiff = calcDiff(vec[i - 1], vec[i]);
            minConsecDiff = min(minConsecDiff, crrDiff);
        }

        return minConsecDiff;
    }

public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutePoints = convertToMinutePoints(timePoints);
        // printf("%d, %d\n", minutePoints[0], minutePoints[1]);

        sort(minutePoints.begin(), minutePoints.end());

        int len = timePoints.size();
        return min(
                findMinConsecDiff(minutePoints),
                calcDiff(minutePoints[0], minutePoints[len - 1]) // wrap around
        );
    }
};
