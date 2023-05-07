// LeetCode-2446: https://leetcode.com/problems/determine-if-two-events-are-conflicting/
// pretty dumb problem; only substring & string to int conversion syntax need to be looked up

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

#define MINUTES_IN_HOUR 60

class Solution {
private:
    int convert24HourTimeToMinutes(string time) {
        string hourStr = time.substr(0, 2);
        int hourInt = stoi(hourStr);

        string minuteStr = time.substr(3, 2);
        int minuteInt = stoi(minuteStr);

        return (hourInt * MINUTES_IN_HOUR) + minuteInt;
    }

public:
    friend class SolutionTest;

    bool haveConflict(vector<string> &event1, vector<string> &event2) {
        int event1Start = convert24HourTimeToMinutes(event1[0]);
        int event1End = convert24HourTimeToMinutes(event1[1]);

        int event2Start = convert24HourTimeToMinutes(event2[0]);
        int event2End = convert24HourTimeToMinutes(event2[1]);

        if (event1Start < event2Start) {
            return event2Start <= event1End;
        } else {
            return event1Start <= event2End;
        }
    }
};

class SolutionTest {
public:
    void testConvert24HourTimeToMinutes() {
        Solution soln = Solution();

        assert(soln.convert24HourTimeToMinutes("00:00") == 0);
        assert(soln.convert24HourTimeToMinutes("00:01") == 1);
        assert(soln.convert24HourTimeToMinutes("00:59") == 59);
        assert(soln.convert24HourTimeToMinutes("01:00") == 60);
        assert(soln.convert24HourTimeToMinutes("04:15") == 255);
        assert(soln.convert24HourTimeToMinutes("11:17") == 677);
        assert(soln.convert24HourTimeToMinutes("19:21") == 1161);
        assert(soln.convert24HourTimeToMinutes("23:59") == 1439);
        assert(soln.convert24HourTimeToMinutes("24:00") == 1440);
    }

    void testHaveConflict() {
        Solution soln = Solution();
        vector<string> event1;
        vector<string> event2;

        // test case 1

        event1 = {"00:00", "00:00"};
        event2 = {"00:00", "00:00"};
        assert(soln.haveConflict(event1, event2) == true);

        // test case 2

        event1 = {"00:00", "00:00"};
        event2 = {"00:01", "00:02"};
        assert(soln.haveConflict(event1, event2) == false);

        event2 = {"00:01", "00:02"};
        event1 = {"00:00", "00:00"};
        assert(soln.haveConflict(event1, event2) == false);

        // test case 3

        event1 = {"01:15", "02:00"};
        event2 = {"02:00", "03:00"};
        assert(soln.haveConflict(event1, event2) == true);

        event2 = {"02:00", "03:00"};
        event1 = {"01:15", "02:00"};
        assert(soln.haveConflict(event1, event2) == true);

        // test case 4

        event1 = {"01:15", "02:00"};
        event2 = {"02:01", "03:00"};
        assert(soln.haveConflict(event1, event2) == false);

        event2 = {"02:01", "03:00"};
        event1 = {"01:15", "02:00"};
        assert(soln.haveConflict(event1, event2) == false);

        // test case 5

        event1 = {"01:00", "02:00"};
        event2 = {"01:20", "03:00"};
        assert(soln.haveConflict(event1, event2) == true);

        event2 = {"01:20", "03:00"};
        event1 = {"01:00", "02:00"};
        assert(soln.haveConflict(event1, event2) == true);

        // test case 6

        event2 = {"10:00", "11:00"};
        event1 = {"14:00", "15:00"};
        assert(soln.haveConflict(event1, event2) == false);

        event1 = {"14:00", "15:00"};
        event2 = {"10:00", "11:00"};
        assert(soln.haveConflict(event1, event2) == false);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testConvert24HourTimeToMinutes();
    solnTest.testHaveConflict();

    return 0;
}
