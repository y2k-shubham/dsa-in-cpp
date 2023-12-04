// LeetCode-2264: https://leetcode.com/problems/largest-3-same-digit-number-in-string/
// easy but involves several micro-optimization opportunities / decisions
// has some irritating edge cases

#include <string>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    /**
     * Given a 3-digit integer like 354 and a digit like 7
     * 1. remove most significant digit: 3
     * 2. add new digit as least significant digit: 7
     * return the result: 547
     * @param num
     * @param newLsd
     * @return
     */
    inline int stripMsdAndAddLsd(int num, int newLsd) {
        if (num >= 1000) {
            return INT_MIN;
        }

        return ((num % 100) * 10) + newLsd;
    }

    /**
     * good integers are 3-digit numbers having just one unique digit
     * so 000, 111, 222 ... 999
     * this draws inspiration from rabin-carp string matching algorithm / sliding window technique
     * @param num
     * @return
     */
    inline bool isGoodInteger(int num) {
        if (num >= 1000) {
            return false;
        }

        int dig1 = num / 100;
        int dig2 = (num / 10) % 10;
        int dig3 = num % 10;

        return (dig1 == dig2) && (dig2 == dig3);
    }

public:
    friend class SolutionTest;

    string largestGoodInteger(string num) {
        int len = num.size();
        if (len < 3) {
            return "";
        }

        int crr3DigNum = stoi(num.substr(0, 3));
        // cout << crr3DigNum << endl;
        int largestGoodInt = isGoodInteger(crr3DigNum) ? crr3DigNum : INT_MIN;
        for (int i = 3; i < len; i++) {
            int newLsd = num.at(i) - '0';
            int newNum = stripMsdAndAddLsd(crr3DigNum, newLsd);
            // printf("at num[i=%d]=%d, newNum=%d\n", i, newLsd, newNum);

            if (isGoodInteger(newNum) && (newNum > largestGoodInt)) {
                largestGoodInt = newNum;
            }

            crr3DigNum = newNum;
        }

        if (largestGoodInt == INT_MIN) {
            if (num.find("000") == num.npos) {
                return "";
            } else {
                return "000";
            }
        } else if (largestGoodInt == 0) {
            return "000";
        } else {
            return to_string(largestGoodInt);
        }
    }
};

class SolutionTest {
public:
    void testStripMsdAndAddLsd() {
        Solution soln = Solution();
        int num;
        int newLsd;
        int newNumOutExpected, newNumOutComputed;

        num = 456;
        newLsd = 7;
        newNumOutExpected = 567;
        newNumOutComputed = soln.stripMsdAndAddLsd(num, newLsd);
        assert(newNumOutExpected == newNumOutComputed);

        num = 316;
        newLsd = 2;
        newNumOutExpected = 162;
        newNumOutComputed = soln.stripMsdAndAddLsd(num, newLsd);
        assert(newNumOutExpected == newNumOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testStripMsdAndAddLsd();

    return 0;
}
