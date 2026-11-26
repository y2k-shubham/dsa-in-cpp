// LeetCode-3360: https://leetcode.com/problems/stone-removal-game/

#define TURN_ALICE 1
#define FIRST_TURN_STONES 10

class Solution {
private:
    bool isAliceTurn(int turn) {
        return turn == TURN_ALICE;
    }

public:
    bool canAliceWin(int n) {
        int remStones = n;
        int turn = TURN_ALICE;
        int crrTurnReqStones = FIRST_TURN_STONES;

        while (remStones > 0) {
            // IMPORTANT: this if-block is necessary
            if (remStones < crrTurnReqStones) {
                // if alice's turn, she lost (and same for bob)
                return !isAliceTurn(turn);
            }

            remStones -= crrTurnReqStones;
            crrTurnReqStones--;
            turn = 1 - turn;
        }

        // if alice's turn, she lost (and same for bob)
        return !isAliceTurn(turn);
    }
};
