// LeetCode-294: https://leetcode.com/problems/flip-game-ii/
// Simple but not that easy

// Solution by Kevin Naughton Jr: https://www.youtube.com/watch?v=rjOTv7dzqC8
// BitMask suggestion by LetsCode: https://www.youtube.com/watch?v=AvkWKiDrDuw

// Note: all four implementations are correct
// Oddly enough memoized variant Impl-2 is ever so slightly slower than Impl-1
// Similarly Impl-3 and Impl-4 take roughly same time

#include <string>
#include <unordered_map>

using namespace std;

#define REQUIRED_CHAR '+'
#define REPLACER_CHAR '-'

#define REQUIRED_BIT 1
#define REPLACER_BIT 0
#define REPLACER_BITMASK 3L
#define BITMASK_MAX_LEN 64

class Solution {
private:

    // ----- String Helpers -----

    bool canReplace(string& state, int i) {
        return (state[i] == REQUIRED_CHAR) && (state[i + 1] == REQUIRED_CHAR);
    }

    void replace(string& state, int i) {
        state[i] = REPLACER_CHAR;
        state[i + 1] = REPLACER_CHAR;
    }

    void undoReplace(string& state, int i) {
        state[i] = REQUIRED_CHAR;
        state[i + 1] = REQUIRED_CHAR;
    }

    // ----- Impl-1: no memoization -----

    bool canWinRec1(string& state) {
        int len = state.size();
        if (len < 2) {
            return false;
        }

        for (int i = 0; i < (len - 1); i++) {
            if (canReplace(state, i)) {
                replace(state, i);
                if (!canWinRec1(state)) {
                    undoReplace(state, i);
                    return true;
                }
                undoReplace(state, i);
            }
        }

        return false;
    }

    // ----- Impl-2: memoization -----

    bool canWinRec2(unordered_map<string, bool>& memoMap, string& state) {
        if (memoMap.find(state) != memoMap.end()) {
            return memoMap[state];
        }

        int len = state.size();
        if (len < 2) {
            memoMap[state] = false;
            return false;
        }

        for (int i = 0; i < (len - 1); i++) {
            if (canReplace(state, i)) {
                replace(state, i);

                if (!canWinRec1(state)) {
                    undoReplace(state, i);
                    memoMap[state] = true;
                    return true;
                }

                undoReplace(state, i);
            }
        }

        memoMap[state] = false;
        return false;
    }

    // ----- BitMask Helpers -----

    pair <long long, int> createBitMask(string& state) {
        long long bitMask = 0;
        int len = state.size();

        for (int i = 0; i < len; i++) {
            bitMask <<= 1;
            if (state[i] == REQUIRED_CHAR) {
                bitMask |= REQUIRED_BIT;
            } else {
                bitMask |= REPLACER_BIT;
            }
        }

        return make_pair(bitMask, len);
    }

    int getBit(long long bitMask, int bitPos) {
        return (bitMask >> bitPos) & 1;
    }

    bool canReplace(long long stateBitMask, int bitPos) {
        return (getBit(stateBitMask, bitPos) & getBit(stateBitMask, bitPos + 1)) == 1;
    }

    long long replace(long long stateBitMask, int bitPos) {
        return stateBitMask ^ (REPLACER_BITMASK << bitPos);
    }

    // ----- Impl-3: bitmask -----
    
    bool canWinRec3(long long stateBitMask, int bitMaskLen) {
        if (bitMaskLen < 2) {
            return false;
        }

        for (int i = 0; i < (bitMaskLen - 1); i++) {
            if (canReplace(stateBitMask, i)) {
                stateBitMask = replace(stateBitMask, i);
                if (!canWinRec3(stateBitMask, bitMaskLen)) {
                    // redundant (unused) statement
                    // stateBitMask = replace(stateBitMask, i);
                    return true;
                }
                stateBitMask = replace(stateBitMask, i);
            }
        }

        return false;
    }

    // ----- Impl-4: bitmask with memoization -----

    bool canWinRec4(unordered_map<long long, bool>& memoMap, long long stateBitMask, int bitMaskLen) {
        if (memoMap.find(stateBitMask) != memoMap.end()) {
            return memoMap[stateBitMask];
        }

        if (bitMaskLen < 2) {
            memoMap[stateBitMask] = false;
            return false;
        }

        for (int i = 0; i < (bitMaskLen - 1); i++) {
            if (canReplace(stateBitMask, i)) {
                stateBitMask = replace(stateBitMask, i);
                if (!canWinRec3(stateBitMask, bitMaskLen)) {
                    stateBitMask = replace(stateBitMask, i);
                    memoMap[stateBitMask] = true;
                    return true;
                }
                stateBitMask = replace(stateBitMask, i);
            }
        }

        memoMap[stateBitMask] = false;
        return false;
    }
    
public:
    bool canWin(string currentState) {
        // impl-4
        unordered_map<long long, bool> memoMap;
        return canWinRec4(memoMap, createBitMask(currentState).first, createBitMask(currentState).second);

        // impl-3
        // pair <long long, int> bitMaskPair = createBitMask(currentState);
        // return canWinRec3(bitMaskPair.first, bitMaskPair.second);

        // impl-2
        // unordered_map<string, bool> memoMap;
        // return canWinRec2(memoMap, currentState);

        // impl-1
        // return canWinRec1(currentState);
    }
};
