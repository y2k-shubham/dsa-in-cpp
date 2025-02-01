// LeetCode-2224: https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/

#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    vector <int> jumpMinutes = {60, 15, 5, 1};

    int convertTimeToMinutesInt(string timeStr) {
        // for "12:43", hoursStr = "12" (start from posn=0 & pick n=2 characters)
        string hoursStr = timeStr.substr(0, 2);
        int hoursInt = stoi(hoursStr);

        // for "12:43", minutesStr = "43" (start from posn=3 & pick n=2 characters)
        string minutesStr = timeStr.substr(3, 2);
        int minutesInt = stoi(minutesStr);

        return (hoursInt * 60) + minutesInt;
    }

    /**
     * Returns (finalMinutes, noOfJumps) taken to go from sourceMinutes
     * to targetMinutes with jumps of size jumpSize each
     */
    pair <int, int> jumpTillPossible(int sourceMinutes, int targetMinutes, int jumpSize) {
        int numJumps = (targetMinutes - sourceMinutes) / jumpSize;
        int finalMinutes = sourceMinutes + (numJumps * jumpSize);
        return {finalMinutes, numJumps};
    }

public:
    int convertTime(string current, string correct) {
        if (current == correct) {
            return 0;
        }

        int sourceMinutes = convertTimeToMinutesInt(current);
        int targetMinutes = convertTimeToMinutesInt(correct);

        int totalJumps = 0;
        for (int jumpSize : jumpMinutes) {
            pair <int, int> result = jumpTillPossible(sourceMinutes, targetMinutes, jumpSize);
            sourceMinutes = result.first;
            totalJumps += result.second;

            if (sourceMinutes == targetMinutes) {
                break;
            }
        }

        return totalJumps;
    }
};
