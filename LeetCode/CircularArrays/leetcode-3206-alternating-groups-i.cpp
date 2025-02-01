// LeetCode-3206: https://leetcode.com/problems/alternating-groups-i

#include <vector>
#include <cassert>
#include <unordered_set>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

#define WINDOW_SIZE 3

class Solution {
private:
    unordered_set <string> alternatingGroups;
    bool debug = false;

    void init() {
        this->alternatingGroups = {"101", "010"};
    }

    char convertToCharNum(int num) {
        return static_cast <char>('0' + num);
    }

    bool isAlternatingGroup(string numStr) {
        return alternatingGroups.count(numStr) > 0;
    }

    string createStr(vector <int>& vec, int startIdx, int numValues) {
        string str;

        for (int i = startIdx; i < (startIdx + numValues); i++) {
            str += convertToCharNum(vec[i]);
        }

        return str;
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class SolutionTest;

    int numberOfAlternatingGroups(vector <int>& colors) {
        init();

        int len = colors.size();
        int numAlternatingGroups = 0;

        string str = createStr(colors, 0, WINDOW_SIZE);
        if (isAlternatingGroup(str)) {
            numAlternatingGroups++;
        }
        // if (debug) {
        //     printf("at i=2, first str=%s, numAlternatingGroups=%d\n", str.c_str(), numAlternatingGroups);
        // }

        for (int i = (WINDOW_SIZE % len); i != (WINDOW_SIZE - 1); i = (i + 1) % len) {
            str = str.substr(1) + convertToCharNum(colors[i]);
            if (isAlternatingGroup(str)) {
                numAlternatingGroups++;
            }
            // if (debug) {
            //     printf("at i=%d, str=%s, numAlternatingGroups=%d\n", i, str.c_str(), numAlternatingGroups);
            // }
        }

        return numAlternatingGroups;
    }
};

class SolutionTest {
public:
    void testNumberOfAlternatingGroups() {
        Solution soln = Solution();
        vector <int> colorsIn;
        int numOutExpected, numOutComputed;

        // soln.enableDebug();
        colorsIn = {1, 1, 1};
        numOutExpected = 0;
        numOutComputed = soln.numberOfAlternatingGroups(colorsIn);
        assert(numOutExpected == numOutComputed);
        // soln.disableDebug();

        colorsIn = {0, 1, 0, 0, 1};
        numOutExpected = 3;
        numOutComputed = soln.numberOfAlternatingGroups(colorsIn);
        assert(numOutExpected == numOutComputed);

        colorsIn = {0, 1, 0};
        numOutExpected = 1;
        numOutComputed = soln.numberOfAlternatingGroups(colorsIn);
        assert(numOutExpected == numOutComputed);

        colorsIn = {0, 1, 1};
        numOutExpected = 1;
        numOutComputed = soln.numberOfAlternatingGroups(colorsIn);
        assert(numOutExpected == numOutComputed);

        colorsIn = {1, 1, 0};
        numOutExpected = 1;
        numOutComputed = soln.numberOfAlternatingGroups(colorsIn);
        assert(numOutExpected == numOutComputed);

        colorsIn = {1, 0, 0};
        numOutExpected = 1;
        numOutComputed = soln.numberOfAlternatingGroups(colorsIn);
        assert(numOutExpected == numOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testNumberOfAlternatingGroups();

    return 0;
}
