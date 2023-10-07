// LeetCode-2038: https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/

#include <iostream>
#include <cassert>
#include <utility>

using namespace std;

class Solution {
private:
    // 'inline' and 'const' improve runtime percentile from 9% to 43%
    inline pair<int, int> eatChars(string& str, int iLo, const char ch) {
        if ((iLo < 0) || (iLo >= str.size())) {
            return {str.size(), 0};
        }

        int i;
        int numChars = 0;
        for (i = iLo; (i < str.size()) && (str.at(i) == ch); i++) {
            numChars++;
        }

        return {i, numChars};
    }

    pair<int, int> countMoves(string& str) {
        if (str.size() < 3) {
            return {0, 0};
        }

        int numMovesA = 0;
        int numMovesB = 0;

        for (int i = 0; i < str.size();) {
            pair<int, int> resA = eatChars(str, i, 'A');
            if (resA.second >= 3) {
                numMovesA += resA.second - 2;
            }
            i = resA.first;

            pair<int, int> resB = eatChars(str, i, 'B');
            if (resB.second >= 3) {
                numMovesB += resB.second - 2;
            }
            i = resB.first;
        }

        return {numMovesA, numMovesB};
    }

public:
    friend class SolutionTest;

    bool winnerOfGame(string colors) {
        pair<int, int> numMoves = countMoves(colors);

        return numMoves.first > numMoves.second;
    }
};

class SolutionTest {
public:
    void testEatChars() {
        Solution soln = Solution();
        string str;
        int iLo;
        char ch;
        pair<int, int> outExpected, outComputed;

        str = "";
        iLo = 0;
        ch = 'A';
        outExpected = {0, 0};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "";
        iLo = -1;
        ch = 'A';
        outExpected = {0, 0};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "";
        iLo = 1;
        ch = 'A';
        outExpected = {0, 0};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "A";
        iLo = 0;
        ch = 'A';
        outExpected = {1, 1};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "A";
        iLo = 0;
        ch = 'B';
        outExpected = {0, 0};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AA";
        iLo = 0;
        ch = 'A';
        outExpected = {2, 2};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AA";
        iLo = 1;
        ch = 'A';
        outExpected = {2, 1};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AB";
        iLo = 0;
        ch = 'A';
        outExpected = {1, 1};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AB";
        iLo = 0;
        ch = 'B';
        outExpected = {0, 0};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AB";
        iLo = 1;
        ch = 'B';
        outExpected = {2, 1};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AABABB";
        iLo = 0;
        ch = 'A';
        outExpected = {2, 2};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AABABB";
        iLo = 2;
        ch = 'B';
        outExpected = {3, 1};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AABABB";
        iLo = 3;
        ch = 'A';
        outExpected = {4, 1};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AABABB";
        iLo = 4;
        ch = 'B';
        outExpected = {6, 2};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);

        str = "AABABB";
        iLo = 6;
        ch = 'A';
        outExpected = {6, 0};
        outComputed = soln.eatChars(str, iLo, ch);
        assert(outExpected == outComputed);
    }

    void testCountMoves() {
        Solution soln = Solution();
        string str;
        pair<int, int> outExpected, outComputed;

        str = "";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "A";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "B";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AA";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "BB";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AAB";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "ABB";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AABB";
        outExpected = {0, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AAABA";
        outExpected = {1, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AAABBBAA";
        outExpected = {1, 1};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AAABBBBAA";
        outExpected = {1, 2};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AAABBBBAABBA";
        outExpected = {1, 2};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "AAABABB";
        outExpected = {1, 0};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);

        str = "ABBBBBBBAAA";
        outExpected = {1, 5};
        outComputed = soln.countMoves(str);
        assert(outExpected == outComputed);
    }

    void testWinnerOfGame() {
        Solution soln = Solution();
        string colors;
        bool outExpected, outComputed;

        colors = "AAABABB";
        outExpected = true;
        outComputed = soln.winnerOfGame(colors);
        assert(outExpected == outComputed);

        colors = "AA";
        outExpected = false;
        outComputed = soln.winnerOfGame(colors);
        assert(outExpected == outComputed);

        colors = "ABBBBBBBAAA";
        outExpected = false;
        outComputed = soln.winnerOfGame(colors);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testEatChars();
    solnTest.testCountMoves();
    solnTest.testWinnerOfGame();

    return 0;
}
