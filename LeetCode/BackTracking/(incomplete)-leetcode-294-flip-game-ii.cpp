// LeetCode-294: https://leetcode.com/problems/flip-game-ii/
// incomplete

#include <vector>
#include <string>
#include <cassert>

using namespace std;

#define NULL_CHAR '\0'
#define REQUIRED_CHAR '+'
#define REPLACER_CHAR '-'

enum class MovePossible {
    Possible_CrrPos,
    Possible_NextPos,
    NotPossible
};

enum class Turn {
    Player_1,
    Player_2
};

enum class Win {
    Player_1,
    Player_2
};

class Solution {
private:
    // ------ player related helpers -------

    Win getCurrentTurnWinner(const Turn turn) {
        return (turn == Turn::Player_1) ? Win::Player_1 : Win::Player_2;
    }

    Win getNextTurnWinner(const Turn turn) {
        return (getCurrentTurnWinner(turn) == Win::Player_1) ? Win::Player_2 : Win::Player_1;
    }

    Turn getOpponent(const Turn turn) {
        return (turn == Turn::Player_1) ? Turn::Player_2 : Turn::Player_1;
    }

    // ------ sequence pre-compute helpers -------

    bool isRequiredChar(const char ch) {
        return ch == REQUIRED_CHAR;
    }

    vector<int> buildNextPossibleMoveIdxVec(string& str) {
        int len = str.size();
        vector<int> nextMoveIdxVec(len, INT_MAX);
        if (len <= 2) {
            return nextMoveIdxVec;
        }

        char prevChar = NULL_CHAR;
        int nextMoveIdx = INT_MAX;
        for (int i = len - 1; i >= 1; i--) {
            char crrChar = str[i];
            if (isRequiredChar(crrChar) && isRequiredChar(prevChar)) {
                nextMoveIdx = i;
            }
            nextMoveIdxVec[i - 1] = nextMoveIdx;

            prevChar = crrChar;
        }

        return nextMoveIdxVec;
    }

    // ------ move related helpers -------

    bool isMovePossibleInCrrPos(string& state, const int pos) {
        const bool isWithinSize = (pos + 1) < state.length();
        const bool hasTwoPlusSigns = isWithinSize && (state[pos] == '+' && state[pos + 1] == '+');

        return isWithinSize && hasTwoPlusSigns;
    }

    bool isMovePossibleInNextPos(const vector<int>& nextPossibleMovePosIdxVec, string& str, const int pos) {
        const int nextPossibleMovePos = nextPossibleMovePosIdxVec[pos];
        return (nextPossibleMovePos != INT_MAX) && (nextPossibleMovePos <= pos);
    }

    MovePossible isMovePossible(
        string& state,
        const vector<int>& nextPossibleMovePosIdxVec,
        const int pos,
        const Turn turn) {
        if (pos >= state.length()) {
            return MovePossible::Possible_CrrPos;
        } else if (isMovePossibleInCrrPos(state, pos)) {
            return MovePossible::Possible_CrrPos;
        } else if (isMovePossibleInNextPos(nextPossibleMovePosIdxVec, state, pos)) {
            return MovePossible::Possible_NextPos;
        } else {
            return MovePossible::NotPossible;
        }
    }

    pair<int, Turn> makeMove(
        string& state,
        const int pos,
        const Turn turn) {
        state[pos] = REPLACER_CHAR;
        state[pos + 1] = REPLACER_CHAR;
        return make_pair(pos, getOpponent(turn));
    }

    pair<int, Turn> undoMove(
        string& state,
        const int pos,
        const Turn turn) {
        state[pos] = REQUIRED_CHAR;
        state[pos + 1] = REQUIRED_CHAR;
        return make_pair(pos, turn);
    }

    // ------ main recursive function -------

    Win winRec(
        const vector<int>& nextPossibleMovePosIdxVec,
        string& state,
        const int pos,
        const Turn turn) {
        const MovePossible movePossible = isMovePossible(state, nextPossibleMovePosIdxVec, pos, turn);
        if (movePossible == MovePossible::NotPossible) {
            return getNextTurnWinner(turn);
        } else if (movePossible == MovePossible::Possible_NextPos) {
            return winRec(nextPossibleMovePosIdxVec, state, nextPossibleMovePosIdxVec[pos], turn);
        }

        const pair<int, Turn> move = makeMove(state, pos, turn);
        const Win winner = winRec(nextPossibleMovePosIdxVec, state, move.first, move.second);

        undoMove(state, move.first, move.second);
        return winner;
    }

public:
    friend class SolutionTest;

    bool canWin(string currentState) {
        int len = currentState.length();
        if (len <= 2) {
            return false;
        }

        const vector<int> nextPossibleMovePosIdxVec = buildNextPossibleMoveIdxVec(currentState);
        const int startPos = isMovePossibleInCrrPos(currentState, 0) ? 0 : nextPossibleMovePosIdxVec[0];
        if (startPos == INT_MAX) {
            return false;
        }

        const Win winPos1 = winRec(nextPossibleMovePosIdxVec, currentState, startPos, Turn::Player_1);
        Win winPos2 = {};
        if ((winPos1 != Win::Player_1) && isMovePossibleInCrrPos(currentState, startPos + 1)) {
            winPos2 = winRec(nextPossibleMovePosIdxVec, currentState, startPos + 1, Turn::Player_1);
        }

        return (winPos1 == Win::Player_1) || (winPos2 == Win::Player_1);
    }
};

class SolutionTest {
public:
    void testBuildNextPossibleMoveIdxVec() {
        // test cases generated using Amazon Q

        Solution solution = Solution();
        string strIn;
        vector<int> nextPossibleMoveIdxVecOutExpected, nextPossibleMoveIdxVecOutComputed;

        // single pair "++"
        strIn = "++";
        nextPossibleMoveIdxVecOutExpected = {0, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // no valid move: single char
        strIn = "+";
        nextPossibleMoveIdxVecOutExpected = {INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // no valid move: all minus
        strIn = "---";
        nextPossibleMoveIdxVecOutExpected = {INT_MAX, INT_MAX, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // no valid move: alternating
        strIn = "+-+-";
        nextPossibleMoveIdxVecOutExpected = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // multiple consecutive plusses
        strIn = "+++";
        nextPossibleMoveIdxVecOutExpected = {0, 1, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // move at end
        strIn = "-++";
        nextPossibleMoveIdxVecOutExpected = {1, 1, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // move at start, not at end
        strIn = "++-";
        nextPossibleMoveIdxVecOutExpected = {0, INT_MAX, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // multiple separate pairs
        strIn = "++-++";
        nextPossibleMoveIdxVecOutExpected = {0, 3, 3, 3, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // all plusses
        strIn = "++++";
        nextPossibleMoveIdxVecOutExpected = {0, 1, 2, INT_MAX};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);

        // empty string
        strIn = "";
        nextPossibleMoveIdxVecOutExpected = {};
        nextPossibleMoveIdxVecOutComputed = solution.buildNextPossibleMoveIdxVec(strIn);
        assert(nextPossibleMoveIdxVecOutExpected == nextPossibleMoveIdxVecOutComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testBuildNextPossibleMoveIdxVec();

    return 0;
}
