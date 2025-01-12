// LeetCode-2381: https://leetcode.com/problems/shifting-letters-ii/

#include <vector>
#include <cassert>

using namespace std;

#define MIN_ALPHABET 'a'
#define MAX_ALPHABET 'z'
#define ALPHABET_LEN (MAX_ALPHABET - MIN_ALPHABET + 1)

class Solution {
private:
    char moveAlphabetForward(char ch, int steps) {
        int effectiveSteps = steps % ALPHABET_LEN;

        if ((ch + effectiveSteps) > MAX_ALPHABET) {
            effectiveSteps -= (MAX_ALPHABET - ch + 1);
            ch = MIN_ALPHABET;
        }

        return (char)(ch + effectiveSteps);
    }

    char moveAlphabetBackward(char ch, int steps) {
        int effectiveSteps = steps % ALPHABET_LEN;

        if ((ch - effectiveSteps) < MIN_ALPHABET) {
            effectiveSteps -= (ch - MIN_ALPHABET + 1);
            ch = MAX_ALPHABET;
        }

        return (char)(ch - effectiveSteps);
    }

    char moveAlphabet(char ch, int steps) {
        if (steps < 0) {
            return moveAlphabetBackward(ch, -steps);
        } else if (steps == 0) {
            return ch;
        } else {
            return moveAlphabetForward(ch, steps);
        }
    }

    vector <int> createTotalShiftsVec(int len, vector <vector <int>>& shifts) {
        vector <int> totalShifts(len, 0);

        for (vector <int> shift : shifts) {
            int start = shift[0];
            int end = shift[1];
            int dir = shift[2];

            if (dir == 1) {
                totalShifts[start]++;
                // IMPORTANT: don't forget this range check for end & len
                if (end < (len - 1)) {
                    totalShifts[end + 1]--;
                }
            } else {
                totalShifts[start]--;
                // IMPORTANT: don't forget this range check for end & len
                if (end < (len - 1)) {
                    totalShifts[end + 1]++;
                }
            }
        }

        return totalShifts;
    }

    void fillTotalShiftsVec(vector <int>& totalShifts) {
        int len = totalShifts.size();
        for (int i = 1; i < len; i++) {
            totalShifts[i] += totalShifts[i - 1];
        }
    }

    string shiftLetters(string& str, vector <int>& totalShifts) {
        int len = str.size();
        vector <char> shiftedStrVec(len);

        for (int i = 0; i < len; i++) {
            int shifts = totalShifts[i];
            shiftedStrVec[i] = moveAlphabet(str[i], shifts);
        }

        return string(shiftedStrVec.begin(), shiftedStrVec.end());
    }

public:
    friend class SolutionTest;

    string shiftingLetters(string str, vector <vector <int>>& shifts) {
        vector <int> totalShifts = createTotalShiftsVec(str.size(), shifts);
        fillTotalShiftsVec(totalShifts);

        return shiftLetters(str, totalShifts);
    }
};

class SolutionTest {
public:
    void testMoveAlphabet() {
        Solution soln = Solution();
        vector <pair <pair <char, int>, char>> testCases = {
            // positive steps
            {{'a', 0}, 'a'},
            {{'a', 26}, 'a'},
            {{'a', 1}, 'b'},
            {{'a', 25}, 'z'},
            {{'a', 26}, 'a'},
            {{'a', 27}, 'b'},
            {{'a', 26051}, 'z'},
            {{'z', 1}, 'a'},
            {{'z', 25}, 'y'},
            {{'z', 26}, 'z'},
            {{'z', 27}, 'a'},
            {{'z', 28}, 'b'},
            {{'z', 26051}, 'y'},

            // negative steps
            {{'a', 0}, 'a'},
            {{'a', -26}, 'a'},
            {{'a', -1}, 'z'},
            {{'a', -25}, 'b'},
            {{'a', -26}, 'a'},
            {{'a', -27}, 'z'},
            {{'a', -26051}, 'b'},
            {{'z', -1}, 'y'},
            {{'z', -25}, 'a'},
            {{'z', -26}, 'z'},
            {{'z', -27}, 'y'},
            {{'z', -28}, 'x'},
            {{'z', -26051}, 'a'},
        };

        for (auto testCase : testCases) {
            assert(soln.moveAlphabet(testCase.first.first, testCase.first.second) == testCase.second);
        }
    }

    void testCreateTotalShiftsVec() {
        Solution soln = Solution();
        vector <vector <int>> shiftsIn;
        int lenIn;
        vector <int> totalShiftsOutExpected, totalShiftsOutComputed;

        shiftsIn = {
            {0, 1, 1}
        };
        lenIn = 4;
        totalShiftsOutExpected = {1, 0, -1, 0};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);

        shiftsIn = {
            {0, 1, -1}
        };
        lenIn = 4;
        totalShiftsOutExpected = {-1, 0, 1, 0};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);

        shiftsIn = {
            {0, 1, 1},
            {0, 1, 0}
        };
        lenIn = 4;
        totalShiftsOutExpected = {0, 0, 0, 0};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);

        shiftsIn = {
            {0, 3, 1},
            {1, 2, 0}
        };
        lenIn = 4;
        totalShiftsOutExpected = {1, -1, 0, 1};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);
    }

    void testFillTotalShiftsVec() {
        Solution soln = Solution();
        vector <vector <int>> shiftsIn;
        int lenIn;
        vector <int> totalShiftsOutExpected, totalShiftsOutComputed;

        shiftsIn = {
            {0, 1, 1}
        };
        lenIn = 4;
        totalShiftsOutExpected = {1, 1, 0, 0};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        soln.fillTotalShiftsVec(totalShiftsOutComputed);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);

        shiftsIn = {
            {0, 1, 0}
        };
        lenIn = 4;
        totalShiftsOutExpected = {-1, -1, 0, 0};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        soln.fillTotalShiftsVec(totalShiftsOutComputed);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);

        shiftsIn = {
            {0, 1, 1},
            {0, 1, 0}
        };
        lenIn = 4;
        totalShiftsOutExpected = {0, 0, 0, 0};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        soln.fillTotalShiftsVec(totalShiftsOutComputed);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);

        shiftsIn = {
            {0, 3, 1},
            {1, 2, 0}
        };
        lenIn = 4;
        totalShiftsOutExpected = {1, 0, 0, 1};
        totalShiftsOutComputed = soln.createTotalShiftsVec(lenIn, shiftsIn);
        soln.fillTotalShiftsVec(totalShiftsOutComputed);
        assert(totalShiftsOutExpected == totalShiftsOutComputed);
    }

    void testShiftingLetters() {
        Solution soln = Solution();
        string strIn;
        vector <vector <int>> shiftsIn;
        string strOutExpected, strOutComputed;

        strIn = "abc";
        shiftsIn = {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}};
        strOutExpected = "ace";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);
        assert(strOutExpected == strOutComputed);

        strIn = "dztz";
        shiftsIn = {{0, 0, 0}, {1, 1, 1}};
        strOutExpected = "catz";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);
        assert(strOutExpected == strOutComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testMoveAlphabet();
    test.testCreateTotalShiftsVec();
    test.testFillTotalShiftsVec();

    return 0;
}
