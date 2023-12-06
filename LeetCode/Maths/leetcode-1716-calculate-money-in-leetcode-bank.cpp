// LeetCode-1716: https://leetcode.com/problems/calc-money-in-leetcode-bank/
// application of Arithmetic Progression

#include <utility>
#include <cassert>

using namespace std;

#define DAYS_IN_WEEK 7
#define AMOUNT_FIRST_MONDAY 1
#define AMOUNT_DELTA_EACH_WEEKDAY 1
#define AMOUNT_STEP_UP_EACH_MONDAY 1

class Solution {
private:
    bool debug;
    int firstWeekAmount;
    int eachWeekTotalStepUpAmount;

    pair<int, int> calcNumFullWeeksAndRemDays(int totalDays) {
        return {
                totalDays / DAYS_IN_WEEK,
                totalDays % DAYS_IN_WEEK
        };
    }

    int apNthTerm(int firstTerm, int commonDifference, int n) {
        return firstTerm + (n - 1) * commonDifference;
    }

    int apSum(int firstTerm, int commonDifference, int numTerms) {
        return (numTerms * ((2 * firstTerm) + (numTerms - 1) * commonDifference)) / 2;
    }

    // n <= 7 and spans within a single week
    // (that is starting and ending day fall within a single week and are not spread across multiple weeks)
    int calcNDaysTotalAmount(int n, int startingAmount) {
        return apSum(startingAmount, AMOUNT_DELTA_EACH_WEEKDAY, n);
    }

    void calcFirstWeekAmount() {
        if (this->firstWeekAmount == 0) {
            this->firstWeekAmount = calcNDaysTotalAmount(DAYS_IN_WEEK, AMOUNT_FIRST_MONDAY);
        }
    }

    void calcEachWeekTotalStepUpAmount() {
        if (this->eachWeekTotalStepUpAmount == 0) {
            this->eachWeekTotalStepUpAmount = DAYS_IN_WEEK;
        }
    }

    int calcNWeeksTotalAmount(int n) {
        if (n <= 0) {
            return 0;
        }

        calcFirstWeekAmount();
        if (n == 1) {
            return firstWeekAmount;
        }

        calcEachWeekTotalStepUpAmount();
        return apSum(firstWeekAmount, eachWeekTotalStepUpAmount, n);
    }

    int calcNthWeekStartingMondayAmount(int n) {
        if (n == 1) {
            return AMOUNT_FIRST_MONDAY;
        }
        return apNthTerm(AMOUNT_FIRST_MONDAY, AMOUNT_STEP_UP_EACH_MONDAY, n);
    }

public:
    friend class SolutionTest;

    int totalMoney(int n) {
        pair<int, int> fullWeeksAndRemDays = calcNumFullWeeksAndRemDays(n);
        int numFullWeeks = fullWeeksAndRemDays.first;
        int numRemDays = fullWeeksAndRemDays.second;

        int fullWeeksTotalAmount = calcNWeeksTotalAmount(numFullWeeks);

        int lastWeekStartingMondayAmount = calcNthWeekStartingMondayAmount(numFullWeeks + 1);
        int remDaysTotalAmount = calcNDaysTotalAmount(numRemDays, lastWeekStartingMondayAmount);

        if (debug) {
            printf("{numFullWeeks=%d, numRemDays=%d}\n", numFullWeeks, numRemDays);
            printf("fullWeeksTotalAmount = %d\n", fullWeeksTotalAmount);
            printf("lastWeekStartingMondayAmount = %d\n", lastWeekStartingMondayAmount);
            printf("remDaysTotalAmount = %d\n", remDaysTotalAmount);
            printf("totalAmount = %d\n", fullWeeksTotalAmount + remDaysTotalAmount);
        }

        return fullWeeksTotalAmount + remDaysTotalAmount;
    }
};

class SolutionTest {
public:
    void testTotalMoney() {
        Solution soln = Solution();
        int n;
        int outExpected, outComputed;

//        soln.debug = true;
        n = 1;
        outExpected = 1;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);
//        soln.debug = false;

        n = 2;
        outExpected = 3;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 3;
        outExpected = 6;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 4;
        outExpected = 10;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 5;
        outExpected = 15;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 6;
        outExpected = 21;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 7;
        outExpected = 28;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 8;
        outExpected = 30;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 9;
        outExpected = 33;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 10;
        outExpected = 37;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 20;
        outExpected = 96;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

//        soln.debug = true;
        n = 21;
        outExpected = 105;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 22;
        outExpected = 109;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 23;
        outExpected = 114;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 24;
        outExpected = 120;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 25;
        outExpected = 127;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);

        n = 26;
        outExpected = 135;
        outComputed = soln.totalMoney(n);
        assert(outExpected == outComputed);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testTotalMoney();

    return 0;
}
