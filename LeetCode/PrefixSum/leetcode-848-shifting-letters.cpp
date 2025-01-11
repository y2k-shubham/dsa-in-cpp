// LeetCode-848: https://leetcode.com/problems/shifting-letters/
// do read the IMPORTANT comment below (dont forget the integer range of ['a', 'z'])

#include <vector>
#include <string>
#include <numeric>
#include <cassert>

using namespace std;

#define MIN_ALPHABET 'a'
#define MAX_ALPHABET 'z'
#define NUM_ALPHABETS 26

class Solution {
private:
    char shiftChar(char c, long long int shift) {
        int netShift = (int)(shift % NUM_ALPHABETS);
        if (netShift == 0) {
            return c;
        }

        // IMPORTANT: this needs to be int
        int shiftedC_int = c + netShift;
        // printf("after netShift=%d, c=%c (int=%d) became shiftedC=%c (int=%d)\n", netShift, c, ((int) c), shiftedC, ((int) shiftedC));
        if (shiftedC_int > MAX_ALPHABET) {
            // printf("since shiftedC=%c (int=%d) > z, setting it to a + (%d - %d -1) = %c\n\n", shiftedC, ((int) shiftedC), ((int) shiftedC), ((int) MAX_ALPHABET), ((char) (MIN_ALPHABET + (shiftedC - MAX_ALPHABET - 1))));
            return (char)(MIN_ALPHABET + (shiftedC_int - MAX_ALPHABET - 1));
        }

        return (char)shiftedC_int;
    }

public:
    friend class SolutionTest;

    string shiftingLetters(string s, vector <int>& shifts) {
        int len = s.size();

        long long int totalShifts = accumulate(shifts.begin(), shifts.end(), 0L);
        if (totalShifts <= 0) {
            return s;
        }

        vector <char> shiftedSVec(len);
        for (int i = 0; i < len; i++) {
            char ch = s.at(i);
            char shiftedCh = shiftChar(ch, totalShifts);
            // printf("ch=%c, totalShifts=%lld, netShift=%d, shiftedCh=%c\n", ch, totalShifts, (int)(totalShifts % NUM_ALPHABETS), shiftedCh);

            shiftedSVec[i] = shiftedCh;
            totalShifts -= shifts[i];
        }

        return string(shiftedSVec.begin(), shiftedSVec.end());
    }
};

class SolutionTest {
public:
    void testShiftChar() {
        Solution soln = Solution();

        assert(soln.shiftChar('a', 1) == 'b');
        assert(soln.shiftChar('a', 25) == 'z');
        assert(soln.shiftChar('a', 26) == 'a');
        assert(soln.shiftChar('a', 26000015) == 'p');
        assert(soln.shiftChar('z', 1) == 'a');
        assert(soln.shiftChar('z', 2600) == 'z');
        assert(soln.shiftChar('z', 2600000) == 'z');
        assert(soln.shiftChar('z', 2600001) == 'a');
        assert(soln.shiftChar('z', 5200002) == 'b');
        assert(soln.shiftChar('z', 7800003) == 'c');
        assert(soln.shiftChar('z', 10400004) == 'd');
    }

    void testShiftingLetters() {
        Solution soln = Solution();
        vector <int> shifts;
        string strIn, shiftedStrOutExpected, shiftedStrOutComputed;

        strIn = "abc";
        shifts = {3, 5, 9};
        shiftedStrOutExpected = "rpl";
        shiftedStrOutComputed = soln.shiftingLetters(strIn, shifts);
        assert(shiftedStrOutExpected == shiftedStrOutComputed);

        strIn = "aaa";
        shifts = {1, 2, 3};
        shiftedStrOutExpected = "gfd";
        shiftedStrOutComputed = soln.shiftingLetters(strIn, shifts);
        assert(shiftedStrOutExpected == shiftedStrOutComputed);

        strIn = "abc";
        shifts = {31, 5, 9};
        shiftedStrOutExpected = "tpl";
        shiftedStrOutComputed = soln.shiftingLetters(strIn, shifts);
        assert(shiftedStrOutExpected == shiftedStrOutComputed);

        strIn = "ruu";
        shifts = {26, 9, 7};
        shiftedStrOutExpected = "hkb";
        shiftedStrOutComputed = soln.shiftingLetters(strIn, shifts);
        // printf("computed=%s\n", shiftedStrOutComputed.c_str());
        assert(shiftedStrOutExpected == shiftedStrOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest test = SolutionTest();

    test.testShiftChar();
    test.testShiftingLetters();

    return 0;
}
