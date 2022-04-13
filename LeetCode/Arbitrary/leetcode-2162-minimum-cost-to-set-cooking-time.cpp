// LeetCode-2162: https://leetcode.com/problems/minimum-cost-to-set-cooking-time/

#include <cstdio>
#include <iostream>
#include <utility>
#include <list>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

#define SECS_IN_MIN 60
#define MAX_VAL 99

class Solution {
private:
    void showList(list<pair<int, int> >& mList) {
        printf("List is:-\n");
        for (list<pair<int, int> >::iterator it = mList.begin(); it != mList.end(); it++) {
            printf("(%d, %d) ", it->first, it->second);
        }
        cout << endl;
    }

    list<pair<int, int> > findBreakups(int targetSeconds) {
        list<pair<int, int> > breakups;
        if (targetSeconds < SECS_IN_MIN) {
            breakups.push_back({0, targetSeconds});
        } else {
            int targetMinutes = targetSeconds / SECS_IN_MIN;
            int residualSeconds = targetSeconds % SECS_IN_MIN;

//            if (targetSeconds < MAX_VAL) {
//                breakups.push_back({0, targetSeconds});
//            }

            // this if expression is needed only for last few test cases (check tests below)
            if (targetMinutes <= MAX_VAL) {
                breakups.push_back({targetMinutes, residualSeconds});
            }
            if (residualSeconds <= (MAX_VAL - SECS_IN_MIN)) {
                breakups.push_back({targetMinutes - 1, residualSeconds + SECS_IN_MIN});
            }
        }

        return breakups;
    }

    list<int> getDigits(int num) {
        list<int> digits;

        while (num > 0) {
            int digit = num % 10;
            digits.push_back(digit);
            num /= 10;
        }

        reverse(digits.begin(), digits.end());
        return digits;
    }

    list<int> getDoubleDigits(int num) {
        if (num < 10) {
            return {0, num};
        } else {
            return getDigits(num);
        }
    }

    int calcSinglePunchCost(int startAt, int reachTo, int moveCost, int pushCost) {
        int totalCost = 0;

        if (startAt != reachTo) {
            totalCost += moveCost;
        }
        totalCost += pushCost;

        return totalCost;
    }

    int calcTotalPunchCost(int startAt, int moveCost, int pushCost, pair<int, int> p) {
        int minutes = p.first;
        int seconds = p.second;

        // cost to punch in minutes (possibly zero)
        int minutesCost = 0;
        list<int> minuteDigits = getDigits(minutes);
        for (auto it = minuteDigits.begin(); it != minuteDigits.end(); it++) {
            minutesCost += calcSinglePunchCost(startAt, *it, moveCost, pushCost);
            startAt = *it;
        }

        // cost to punch in seconds (never zero)
        int secondsCost = 0;
        list<int> secondDigits = (minutes > 0) ? getDoubleDigits(seconds) : getDigits(seconds);
        for (auto it = secondDigits.begin(); it != secondDigits.end(); it++) {
            secondsCost += calcSinglePunchCost(startAt, *it, moveCost, pushCost);
            startAt = *it;
        }

        int totalCost = minutesCost + secondsCost;
        return totalCost;
    }

public:
    friend class SolutionTest;

    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        list<pair<int, int> > breakups = findBreakups(targetSeconds);

        int minCost = INT_MAX;
        for (auto it = breakups.begin(); it != breakups.end(); it++) {
            int crrCost = calcTotalPunchCost(startAt, moveCost, pushCost, *it);
            minCost = min(minCost, crrCost);
        }

        return minCost;
    }
};

class SolutionTest {
public:
    void testFindBreakups() {
        Solution soln = Solution();
        int targetSecondsIn;
        list<pair<int, int> > breakupsOutExpected;
        list<pair<int, int> > breakupsOutComputed;

        targetSecondsIn = 0;
        breakupsOutExpected = {{0, 0}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 59;
        breakupsOutExpected = {{0, 59}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 60;
        breakupsOutExpected = {{1, 0},
                               {0, 60}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 99;
        breakupsOutExpected = {{1, 39},
                               {0, 99}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
//        soln.showList(breakupsOutComputed);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 100;
        breakupsOutExpected = {{1, 40}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 119;
        breakupsOutExpected = {{1, 59}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 120;
        breakupsOutExpected = {{2, 0},
                               {1, 60}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 121;
        breakupsOutExpected = {{2, 1},
                               {1, 61}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 159;
        breakupsOutExpected = {{2, 39},
                               {1, 99}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 160;
        breakupsOutExpected = {{2, 40}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 6000;
        breakupsOutExpected = {{99, 60}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
//        soln.showList(breakupsOutComputed);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 6008;
        breakupsOutExpected = {{99, 68}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
        assert(breakupsOutExpected == breakupsOutComputed);

        targetSecondsIn = 6039;
        breakupsOutExpected = {{99, 99}};
        breakupsOutComputed = soln.findBreakups(targetSecondsIn);
//        soln.showList(breakupsOutComputed);
        assert(breakupsOutExpected == breakupsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindBreakups();

    return 0;
}
