// LeetCode-1239: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
// bitmasking + permutations

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

#define NUM_BITS 32

class Solution {
private:
    bool debug = false;

    inline int convertToBitMap(string& str) {
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

    vector<pair<int, int>> convertToBitMaps(vector<string>& strs) {
        vector<pair<int, int>> bitMaps;
        for (string str: strs) {
            int bitMap = convertToBitMap(str);
            if (bitMap != -1) {
                bitMaps.push_back({bitMap, str.size()});
            }
        }

        return bitMaps;
    }

    void showVec(vector<pair<int, int>>& vec) {
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

    inline int pickAndCalcLen(vector<pair<int, int>>& bitMaps, int permutationIdx) {
        int len = 0;
        int bitMask = 0;

        // find most significant bit of integer: https://www.geeksforgeeks.org/find-significant-set-bit-number/
        // __builtin_clz : https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
        int msbIndex = NUM_BITS - __builtin_clz(permutationIdx) - 1;
        for (int i = 0; i <= msbIndex; i++) {
            if (permutationIdx & (1 << i)) {
                if (debug) {
                    printf("for size=%d & permutationIdx=%d, trying to access index i=%d\n", bitMaps.size(), permutationIdx, i);
                }

                if ((bitMask & bitMaps[i].first) != 0) {
                    return 0;
                }

                bitMask = bitMask | bitMaps[i].first;
                len += bitMaps[i].second;
            }
        }

        return len;
    }

public:
    friend class SolutionTest;

    int maxLength(vector<string>& arr) {
        vector<pair<int, int>> bitMaps = convertToBitMaps(arr);
        if (bitMaps.empty()) {
            return 0;
        }
        if (bitMaps.size() == 1) {
            return bitMaps[0].second;
        }

        // it is important to take bitMaps.size() instead of arr.size()
        int numPermutations = 1 << bitMaps.size(); // 2 ^ len

        int maxLen = 0;
        for (int i = 1; i < numPermutations; i++) {
            maxLen = max(maxLen, pickAndCalcLen(bitMaps, i));
        }

        return maxLen;
    }
};

class SolutionTest {
public:
    void debugConvertToBitMaps() {
        Solution soln = Solution();

        vector<string> strs = {"", "a", "ab", "abc", "abcd", "ad", "z"};
        vector<pair<int, int>> bitMaps = soln.convertToBitMaps(strs);
        soln.showVec(bitMaps);
    }

    void testMaxLength() {
        Solution soln = Solution();
        vector<string> vecIn;
        int outExpected, outComputed;

        soln.debug = false;

        vecIn = {"un", "iq", "ue"};
        outExpected = 4;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

        vecIn = {"cha", "r", "act", "ers"};
        outExpected = 6;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

        vecIn = {"cha", "r", "act", "ers", "y"};
        outExpected = 7;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

        vecIn = {"cha", "r", "act", "ers", "y", "pvnf"};
        outExpected = 11;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

        vecIn = {"cha", "r", "act", "ers", "y", "pvnfr"};
        outExpected = 9;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

        vecIn = {"abcdefghijklmnopqrstuvwxyz"};
        outExpected = 26;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

        vecIn = {"aa","bb"};
        outExpected = 0;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);

//        soln.debug = true;
        vecIn = {"zog","nvwsuikgndmfexxgjtkb","nxko"};
        outExpected = 0;
        outComputed = soln.maxLength(vecIn);
        assert(outExpected == outComputed);
        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxLength();

    return 0;
}
