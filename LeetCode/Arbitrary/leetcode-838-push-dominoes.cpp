// LeetCode-838: https://leetcode.com/problems/push-dominoes/
// NickWhite: https://www.youtube.com/watch?v=Z2x-zalsebs

// good question
// - optimal solution is also easy to implement but not very obvious
// - brute-force BFS solution is inefficient and difficult to implement

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
private:
    vector<char> convertToVec(string& str) {
        vector<char> vec(str.begin(), str.end());
        return vec;
    }

    string convertToStr(vector<char>& vec) {
        string str(vec.begin(), vec.end());
        return str;
    }

    vector<int> buildNextRFallDominoOnLeftVec(vector<char>& vec) {
        int len = vec.size();

        vector<int> nextRFallDominoOnLeftVec(len, -1);
        int lastRFallDominoIdx = INT_MIN;
        for (int i = 0; i < len; i++) {
            char ch = vec[i];
            if (ch == 'R') {
                lastRFallDominoIdx = i;
            } else if (ch == 'L') {
                lastRFallDominoIdx = INT_MIN;
            }

            nextRFallDominoOnLeftVec[i] = lastRFallDominoIdx;
        }

        return nextRFallDominoOnLeftVec;
    }

    vector<int> buildNextLFallDominoOnRightVec(vector<char>& vec) {
        int len = vec.size();

        vector<int> nextLFallDominoOnRightVec(len, len);
        int lastLFallDominoIdx = INT_MAX;
        for (int i = len - 1; i >= 0; i--) {
            char ch = vec[i];
            if (ch == 'L') {
                lastLFallDominoIdx = i;
            } else if (ch == 'R') {
                lastLFallDominoIdx = INT_MAX;
            }
            nextLFallDominoOnRightVec[i] = lastLFallDominoIdx;
        }

        return nextLFallDominoOnRightVec;
    }

    vector<char> buildUpdatedVec(
            vector<char>& orgVec,
            vector<int>& nextRFallDominoOnLeftVec,
            vector<int>& nextLFallDominoOnRightVec
    ) {
        int len = orgVec.size();

        vector<char> updatedVec = orgVec;
        for (int i = 0; i < len; i++) {
            if (updatedVec[i] != '.') {
                continue;
            }

            int leftRFallDominoDist = (nextRFallDominoOnLeftVec[i] >= 0) ? (i - nextRFallDominoOnLeftVec[i]) : INT_MAX;
            int rightLFallDominoDist = (nextLFallDominoOnRightVec[i] < len) ? (nextLFallDominoOnRightVec[i] - i)
                                                                            : INT_MAX;

            if (leftRFallDominoDist < rightLFallDominoDist) {
                updatedVec[i] = 'R';
            } else if (leftRFallDominoDist > rightLFallDominoDist) {
                updatedVec[i] = 'L';
            } else {
                // do nothing
            }
        }

        return updatedVec;
    }

public:
    string pushDominoes(string dominoes) {
        vector<char> vec = convertToVec(dominoes);

        vector<int> nextRFallDominoOnLeftVec = buildNextRFallDominoOnLeftVec(vec);
        vector<int> nextLFallDominoOnRightVec = buildNextLFallDominoOnRightVec(vec);

        vector<char> updatedVec = buildUpdatedVec(
                vec,
                nextRFallDominoOnLeftVec,
                nextLFallDominoOnRightVec
        );
        string updatedStr = convertToStr(updatedVec);

        return updatedStr;
    }
};
