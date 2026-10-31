// LeetCode-36: https://leetcode.com/problems/valid-sudoku/
// Companies: [Amazon][Google][Meta][Bloomberg][tcs][Apple][Quince][Riot Games][Microsoft][Udemy][Confluent][Samsara][Uber][Zoho][PayPal][Oracle][Walmart Labs][Goldman Sachs]

#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

#define BOARD_SIDE_LEN 9
#define BOX_SIDE_LEN 3
#define EMPTY_CHAR '.'
#define ZERO_CHAR '0'

class Solution {
private:
    pair <bool, vector <int>> createRowMembershipVec(vector<vector<char>>& board) {
        vector <int> rowMembershipVec(BOARD_SIDE_LEN);

        for (int i = 0; i < BOARD_SIDE_LEN; i++) {
            int rowMembershipBitmask = 0;
            for (int j = 0; j < BOARD_SIDE_LEN; j++) {
                if (board[i][j] == EMPTY_CHAR) {
                    // empty cell, skip
                    continue;
                }

                int digit = board[i][j] - ZERO_CHAR;
                int digitBitmask = 1 << digit;

                if ((rowMembershipBitmask & digitBitmask) != 0) {
                    // found repeated digit in this row
                    return {false, {}};
                }

                rowMembershipBitmask |= digitBitmask;
            }
            rowMembershipVec[i] = rowMembershipBitmask;
        }

        return {true, rowMembershipVec};
    }

    pair <bool, vector <int>> createColMembershipVec(vector<vector<char>>& board) {
        vector <int> colMembershipVec(BOARD_SIDE_LEN);

        for (int j = 0; j < BOARD_SIDE_LEN; j++) {
            int colMembershipBitmask = 0;
            for (int i = 0; i < BOARD_SIDE_LEN; i++) {
                if (board[i][j] == EMPTY_CHAR) {
                    // empty cell, skip
                    continue;
                }

                int digit = board[i][j] - ZERO_CHAR;
                int digitBitmask = 1 << digit;

                if ((colMembershipBitmask & digitBitmask) != 0) {
                    // found repeated digit in this col
                    return {false, {}};
                }

                colMembershipBitmask |= digitBitmask;
            }
            colMembershipVec[j] = colMembershipBitmask;
        }

        return {true, colMembershipVec};
    }

    bool isValidBox(vector<vector<char>>& board, int box) {
        int iLo = BOX_SIDE_LEN * (box / BOX_SIDE_LEN);
        int jLo = (box % BOX_SIDE_LEN) * BOX_SIDE_LEN;

        // printf("------validating box=%d------\n", box);

        int boxMembershipBitmask = 0;
        for (int i = iLo; i < (iLo + BOX_SIDE_LEN); i++) {
            for (int j = jLo; j < (jLo + BOX_SIDE_LEN); j++) {
                if (board[i][j] == EMPTY_CHAR) {
                    // empty cell, skip
                    continue;
                }

                int digit = board[i][j] - ZERO_CHAR;
                // printf("at board[i=%d][j=%d] = '%c' = %d\n", i, j, board[i][j], digit);
                int digitBitmask = 1 << digit;

                if ((boxMembershipBitmask & digitBitmask) != 0) {
                    // found repeated digit in this box
                    return false;
                }

                boxMembershipBitmask |= digitBitmask;
            }
        }

        return true;
    }

public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // row membership vec pre-computation
        pair <bool, vector <int> > rowMembershipResult = createRowMembershipVec(board);
        if (!rowMembershipResult.first) {
            // early-return: found duplicates in some row
            return false;
        }
        vector <int> rowMembershipVec = rowMembershipResult.second;

        // col membership vec pre-computation
        pair <bool, vector <int> > colMembershipResult = createColMembershipVec(board);
        if (!colMembershipResult.first) {
            // early-return: found duplicates in some col
            return false;
        }
        vector <int> colMembershipVec = colMembershipResult.second;

        // 'box' numberings depicted below
        // [0, 1, 2]
        // [3, 4, 5]
        // [6, 7, 8]
        for (int box = 0; box < BOARD_SIDE_LEN; box++) {
            if (!isValidBox(board, box)) {
                return false;
            }
        }

        return true;
    }
};
