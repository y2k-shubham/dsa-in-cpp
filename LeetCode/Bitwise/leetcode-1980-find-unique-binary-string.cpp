// LeetCode-1980: https://leetcode.com/problems/find-unique-binary-string/

#include <iostream>
#include <cassert>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <cassert>
#include <sstream>
#include <random>
#include <unordered_set>

using namespace std;

class Solution {
private:
    bool debug = false;

    int convertToInt(string& binStr) {
        int binInt = 0;

        for (int i = 0; i < binStr.size(); i++) {
            binInt <<= 1;
            if (debug) {
                printf("---------\n");
                printf("done left shift, became %d\n", binInt);
            }

            char ch = binStr.at(i);
            if (ch == '1') {
                binInt |= 1;
                if (debug) {
                    printf("took | with 1, became %d\n", binInt);
                }
            }
        }

        return binInt;
    }

    string convertToStr(int numBits, int binInt) {
        ostringstream oss;
        for (int i = 1; i <= numBits; i++) {
            oss << '0';
        }

        string binStr = oss.str();

        for (int i = 0; i < numBits; i++) {
            if ((binInt & (1 << i)) > 0) {
                binStr[numBits - i - 1] = '1';
                if (debug) {
                    printf("at i=%d, set binStr[numBits=%d - i=%d - 1] = binStr[%d] = 1, binStr became %s\n", i,
                           numBits, i, (numBits - i - 1), binStr.c_str());
                }
            } else {
                if (debug) {
                    printf("at i=%d, skipped setting bit\n", i);
                }
            }
        }

        return binStr;
    }

public:
    friend class SolutionTest;

    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums[0].size();

        int exp2n = (int) pow(2, n);
        vector<bool> numExists(exp2n, false);

        // random number generation: https://stackoverflow.com/a/13445752/3679900
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distExp2n(0,
                                                                           exp2n - 1); // distribution in range [1, 6]

        // record existence of each number
        for (auto it = nums.begin(); it != nums.end(); it++) {
            string binStr = *it;
            int binInt = convertToInt(binStr);

            numExists[binInt] = true;
        }

        // find first non-existing number
        while (true) {
            int randInt = distExp2n(rng);
            if (!numExists[randInt]) {
                return convertToStr(n, randInt);
            }
        }

        return "";
    }
};

class SolutionTest {
public:
    void testConvertToInt() {
        Solution soln = Solution();
        string strIn;
        int intOutExpected, intOutComputed;

        strIn = "";
        intOutExpected = 0;
        intOutComputed = soln.convertToInt(strIn);
        assert(intOutExpected == intOutComputed);

        strIn = "0";
        intOutExpected = 0;
        intOutComputed = soln.convertToInt(strIn);
        assert(intOutExpected == intOutComputed);

//        soln.debug = true;
        strIn = "1";
        intOutExpected = 1;
        intOutComputed = soln.convertToInt(strIn);
        assert(intOutExpected == intOutComputed);
//        soln.debug = false;

        strIn = "10";
        intOutExpected = 2;
        intOutComputed = soln.convertToInt(strIn);
        assert(intOutExpected == intOutComputed);

        strIn = "1011";
        intOutExpected = 11;
        intOutComputed = soln.convertToInt(strIn);
        assert(intOutExpected == intOutComputed);
    }

    void testConvertToStr() {
        Solution soln = Solution();
        int intIn;
        int numBitsIn;
        string strOutExpected, strOutComputed;

        intIn = 0;
        numBitsIn = 4;
        strOutExpected = "0000";
        strOutComputed = soln.convertToStr(numBitsIn, intIn);
        assert(strOutExpected == strOutComputed);

//        soln.debug = true;
        intIn = 6;
        numBitsIn = 4;
        strOutExpected = "0110";
        strOutComputed = soln.convertToStr(numBitsIn, intIn);
        assert(strOutExpected == strOutComputed);
//        soln.debug = false;

        intIn = 15;
        numBitsIn = 4;
        strOutExpected = "1111";
        strOutComputed = soln.convertToStr(numBitsIn, intIn);
        assert(strOutExpected == strOutComputed);
    }

    void testFindDifferentBinaryString() {
        Solution soln = Solution();
        vector<string> vecIn;
        unordered_set<string> strsOutExpected;
        string strOutComputed;

        vecIn = {"01", "10"};
        strsOutExpected = {"00", "11"};
        strOutComputed = soln.findDifferentBinaryString(vecIn);
        assert(strsOutExpected.find(strOutComputed) != strsOutExpected.end());

        vecIn = {"00", "01"};
        strsOutExpected = {"10", "11"};
        strOutComputed = soln.findDifferentBinaryString(vecIn);
        assert(strsOutExpected.find(strOutComputed) != strsOutExpected.end());

        vecIn = {"111", "011", "001"};
        strsOutExpected = {"000", "010", "100", "101", "110"};
        strOutComputed = soln.findDifferentBinaryString(vecIn);
        assert(strsOutExpected.find(strOutComputed) != strsOutExpected.end());
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testConvertToInt();
    solnTest.testConvertToStr();
    solnTest.testFindDifferentBinaryString();

    return 0;
}
