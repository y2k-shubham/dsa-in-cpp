// LeetCode-1239: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
// bitmasking + backtracking (brute-force)

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
private:
    int convertToBitMap(string str) {
        int bitMap = 0;
        for (char ch: str) {
            int bit = 1 << (ch - 'a');
            if (bitMap & bit) {
                return -1;
            }

            bitMap |= bit;
        }

        return bitMap;
    }

    vector <pair<int, int>> convertToBitMaps(vector <string>& strs) {
        vector <pair<int, int>> bitMaps;
        for (string str: strs) {
            int bitMap = convertToBitMap(str);
            if (bitMap != -1) {
                bitMaps.push_back({bitMap, str.size()});
            }
        }

        return bitMaps;
    }

    void showVec(vector <pair<int, int>>& vec) {
        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val-1:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i].first);
        }
        cout << endl;

        printf("Val-2:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i].second);
        }
        cout << endl;
    }

    int maxLen(vector <pair<int, int>>& bitMaps, int crrIdx, int crrBitMask) {
        int len = bitMaps.size();
        if (crrIdx >= len) {
            return 0;
        }

        int crrBitMap = bitMaps[crrIdx].first;
        int crrStrLen = bitMaps[crrIdx].second;

        int crrExcLen = maxLen(bitMaps, crrIdx + 1, crrBitMask); // skip current string;
        int crrIncLen = 0;

        bool hasOverlap = (crrBitMask & crrBitMap) > 0;
        if (!hasOverlap) {
            crrIncLen = maxLen(bitMaps, crrIdx + 1, crrBitMask | crrBitMap) + crrStrLen;
        }

        return max(crrExcLen, crrIncLen);
    }

public:
    friend class SolutionTest;

    int maxLength(vector <string>& arr) {
        vector <pair<int, int>> bitMaps = convertToBitMaps(arr);
        // showVec(bitMaps);
        return maxLen(bitMaps, 0, 0);
    }
};

class SolutionTest {
public:
    void debugConvertToBitMaps() {
        Solution soln = Solution();

        vector <string> strs = {"", "a", "ab", "abc", "abcd", "ad", "z"};
        vector <pair<int, int>> bitMaps = soln.convertToBitMaps(strs);
        soln.showVec(bitMaps);
    }

    void testMaxLength() {
        Solution soln = Solution();
        vector <string> vecIn;
        int outExpected, outComputed;

        vecIn = {"un", "iq", "ue"};
        outExpected = 4;
        outComputed = soln.maxLength(vecIn);
//        printf("outExpected = %d, outComputed = %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vecIn = {"cha", "r", "act", "ers"};
        outExpected = 6;
        outComputed = soln.maxLength(vecIn);
//        printf("outExpected = %d, outComputed = %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vecIn = {"abcdefghijklmnopqrstuvwxyz"};
        outExpected = 26;
        outComputed = soln.maxLength(vecIn);
//        printf("outExpected = %d, outComputed = %d\n", outExpected, outComputed);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

//    solnTest.debugConvertToBitMaps();
    solnTest.testMaxLength();

    return 0;
}
