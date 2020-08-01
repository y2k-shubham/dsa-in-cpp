// https://leetcode.com/problems/word-search/
// pretty dumb problem, but correct implementation takes time, particularly when you are out of practise

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool exists(vector<vector<char>>& board, vector<vector<bool>>& visited, string word, int sInd, int bI, int bJ, bool);
bool exist(vector<vector<char>>& board, string word);
bool existDebug(vector<vector<char>>& board, string word, bool);
void testExistDebug();

int main() {
    testExistDebug();

    return 0;
}

bool exist(vector<vector<char>>& board, string word) {
    return existDebug(board, word, false);
}

void testExistDebug() {
    vector<vector<char>> board;

    board = {};
    assert(existDebug(board, "", false) == true);

    board = {{}};
    assert(existDebug(board, "", false) == true);

    board = {};
    assert(existDebug(board, "123", false) == false);

    board = {{}};
    assert(existDebug(board, "234", false) == false);

    // printf("1\n");
    board = {{'a'}};
    assert(existDebug(board, "a", false) == true);

    // printf("2\n");
    board = {{'b'}};
    assert(existDebug(board, "a", false) == false);

    // printf("3\n");
    board = {
        {'a'},
        {'p'}};
    assert(existDebug(board, "ap", false) == true);

    // printf("4\n");
    board = {{'a', 'p'}};
    assert(existDebug(board, "ap", false) == true);

    // printf("5\n");
    board = {
        {'a', 'b'},
        {'p', 'q'}};
    assert(existDebug(board, "abq", false) == true);

    // printf("6\n");
    board = {
        {'a', 'b'},
        {'p', 'q'}};
    assert(existDebug(board, "abb", false) == false);

    // printf("7\n");
    board = {
        {'a', 'b'},
        {'p', 'q'}};
    assert(existDebug(board, "app", false) == false);

    // printf("8\n");
    board = {
        {'a', 'b'},
        {'p', 'q'}};
    assert(existDebug(board, "qpa", false) == true);
}

bool existDebug(vector<vector<char>>& board, string word, bool debug) {
    if (word.empty()) {
        return true;
    } else if (board.empty() || board[0].empty()) {
        return false;
    } else {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<bool>> visited(rows);
        for (int i = 0; i < rows; i++) {
            vector<bool> visRow(cols, false);
            visited[i] = visRow;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (exists(board, visited, word, 0, i, j, debug)) {
                    return true;
                }
            }
        }

        return false;
    }
}

bool exists(vector<vector<char>>& board, vector<vector<bool>>& visited, string word, int sInd, int bI, int bJ, bool debug) {
    if (debug) {
        printf("\n----------\n");
        printf("sInd = %d, [bI=%d][bJ=%d]\n", sInd, bI, bJ);
    }
    if (sInd >= ((int)word.size())) {
        if (debug) {
            printf("word consumed, returning true\n");
        }
        return true;
    } else if (word.at(sInd) == board[bI][bJ]) {
        if (sInd == (((int)word.size()) - 1)) {
            if (debug) {
                printf("last character matched, returning true\n");
            }
            return true;
        } else {
            if (debug) {
                printf("s[%d]=%c = board[%d][%d]=%c, checking further\n", sInd, word.at(sInd), bI, bJ, board[bI][bJ]);
            }
            visited[bI][bJ] = true;

            bool found = false;
            int newRow;
            int newCol;

            // top
            newRow = bI - 1;
            newCol = bJ;
            if (newRow >= 0 && !visited[newRow][newCol]) {
                found = found || exists(board, visited, word, sInd + 1, newRow, newCol, debug);
            }
            if (found) {
                return true;
            }

            // right
            newRow = bI;
            newCol = bJ + 1;
            int cols = ((int)visited[0].size());
            if (newCol < cols && !visited[newRow][newCol]) {
                found = found || exists(board, visited, word, sInd + 1, newRow, newCol, debug);
            }
            if (found) {
                return true;
            }

            // bottom
            newRow = bI + 1;
            newCol = bJ;
            int rows = ((int)visited.size());
            if (newRow < rows && !visited[newRow][newCol]) {
                found = found || exists(board, visited, word, sInd + 1, newRow, newCol, debug);
            }
            if (found) {
                return true;
            }

            // left
            newRow = bI;
            newCol = bJ - 1;
            if (newCol >= 0 && !visited[newRow][newCol]) {
                found = found || exists(board, visited, word, sInd + 1, newRow, newCol, debug);
            } else if (debug) {
                printf("newCol=%d\nnewCol > 0=%s\tvisited[newRow=%d][newCol=%d]=%s\n", newCol, ((newCol > 0) ? "true" : "false"), newRow, newCol, (visited[newRow][newCol] ? "true" : "false"));
            }
            if (found) {
                return true;
            }

            visited[bI][bJ] = false;
            return false;
        }
    } else {
        if (debug) {
            printf("s[%d]=%c != board[%d][%d]=%c, returning false\n", sInd, word.at(sInd), bI, bJ, board[bI][bJ]);
        }
        return false;
    }
}