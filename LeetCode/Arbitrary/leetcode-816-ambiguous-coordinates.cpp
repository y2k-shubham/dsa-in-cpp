// stinky question (unsolved)
// LeetCode-816: https://leetcode.com/problems/ambiguous-coordinates/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3741/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int findZerosSuffixBeginInd(string str) {
        int len = str.size();

        for (int i = len - 1; i >= 0; i--) {
            if (str.at(i) != '0') {
                return i + 1;
            }
        }

        return 0;
    }

    vector<string> buildCombs(string str) {
        int len = str.size();
        if (len == 1) {
            return {str};
        }

        vector<string> vec;

        if (str.at(0) == '0') {
            vec.push_back("0." + str.substr(1));
        } else {
            vec.push_back(str);

            int zerosSuffixBeginInd = findZerosSuffixBeginInd(str);
            if (zerosSuffixBeginInd < len - 1) {
                vec.push_back(str.substr(0, len - 2 + 1) + ".0");
            } else {
                for (int i = 0; i < len - 1; i++) {
                    vec.push_back(str.substr(0, i + 1) + "." + str.substr(i + 1));
                }
            }
        }

        return vec;
    }

   public:
    vector<string> ambiguousCoordinates(string s) {
    }

    friend class SolutionTest;
};

class SolutionTest {
   public:
    void testBuildCombs() {
        Solution soln = Solution();
        vector<string> vecOutExpected;
        vector<string> vecOutComputed;
        string str;

        str = "0";
        vecOutExpected = {"0"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        // this is not allowed -> input is invalid
        str = "00";
        vecOutExpected = {"0.0"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "001";
        vecOutExpected = {"0.01"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "021";
        vecOutExpected = {"0.21"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "5";
        vecOutExpected = {"5"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "54";
        vecOutExpected = {"54", "5.4"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "540";
        vecOutExpected = {"540", "5.40", "54.0"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "5400";
        vecOutExpected = {"5400", "540.0"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "54000";
        vecOutExpected = {"54000", "5400.0"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "5491";
        vecOutExpected = {"5491", "5.491", "54.91", "549.1"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);

        str = "54910";
        vecOutExpected = {"54910", "5491.0"};
        vecOutComputed = soln.buildCombs(str);
        assert(vecOutExpected == vecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildCombs();

    return 0;
}
