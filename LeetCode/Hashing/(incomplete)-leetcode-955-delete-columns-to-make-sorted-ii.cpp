// LeetCode-955: https://leetcode.com/problems/delete-columns-to-make-sorted-ii/
// definitely not as easy as it seems
// (incomplete)

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_LEN 101
#define STRICTLY_INCREASING 0
#define NON_DECREASING 1
#define DECREASING 2


class Solution {
private:
    bool debug = false;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    void showSkipIndices(unordered_set<int>& skipIndices) {
        printf("skipIndices are:\t");
        for (auto it = skipIndices.begin(); it != skipIndices.end(); it++) {
            printf("%d ", *it);
        }
        cout << endl;
    }

    vector <vector <char>> convertToVecOfVecs(vector <string>& strs) {
        vector <vector <char>> vecOfVecs(strs.size());
        int i = 0;
        for (string str : strs) {
            vector <char> vec(str.begin(), str.end());
            vecOfVecs[i++] = vec;
        }

        return vecOfVecs;
    }

    bool isInSet(unordered_set <int>& mSet, int val) {
        return mSet.find(val) != mSet.end();
    }

    int findLexicographicalSortDegree(
        vector <vector <char>>& vecOfVecs,
        unordered_set <int>& skipIndices,
        int charPosn) {
        int sortDegree = STRICTLY_INCREASING;

        unordered_map <char, int> charFreqCount;
        unordered_map <char, int> charLastIdx;

        char firstStrChar = vecOfVecs[0][charPosn];
        charFreqCount[firstStrChar]++;
        charLastIdx[firstStrChar] = 0;

        for (int i = 1; i < vecOfVecs.size(); i++) {
            if (isInSet(skipIndices, i - 1) || isInSet(skipIndices, i)) {
                continue;
            }

            char prevStrChar = vecOfVecs[i - 1][charPosn];
            char crrStrChar = vecOfVecs[i][charPosn];

            charFreqCount[crrStrChar]++;
            charLastIdx[crrStrChar] = i;

            if (prevStrChar < crrStrChar) {
                // do nothing
            } else if (prevStrChar == crrStrChar) {
                sortDegree = NON_DECREASING;
            } else {
                // no need to check any further strings as we've found one such case which
                // would make us have to skip (erase) charPosn altogether
                return DECREASING;
            }
        }

        // all characters having frequency of 1 can be excluded
        for (auto it = charFreqCount.begin(); it != charFreqCount.end(); it++) {
            if (it->second == 1) {
                skipIndices.insert(charLastIdx[it->first]);
            }
        }

        return sortDegree;
    }

    int findMinDeletionSize(vector <string>& vecOfStrs) {
        int perStringLen = vecOfStrs[0].size();
        vector <vector <char>> vecOfVecs = convertToVecOfVecs(vecOfStrs);

        unordered_set <int> skipIndices;
        int numCharsToDelete = 0;
        for (int i = 0; i < perStringLen; i++) {
            int lexicographicalSortDegree = findLexicographicalSortDegree(vecOfVecs, skipIndices, i);
            if (debug) {
                printf("\n-----at i=%d-----\n", i);
                printf("determined sort degree = %s\n", ((lexicographicalSortDegree == STRICTLY_INCREASING) ? "STRICTLY_INCREASING" : (lexicographicalSortDegree == NON_DECREASING) ? "NON_DECREASING" : "DECREASING"));
                showSkipIndices(skipIndices);
            }

            if (lexicographicalSortDegree == STRICTLY_INCREASING) {
                return numCharsToDelete;
            } else if (lexicographicalSortDegree == NON_DECREASING) {
                continue;
            } else {
                ++numCharsToDelete;
            }
        }

        return numCharsToDelete;
    }

public:
    friend class SolutionTest;

    int minDeletionSize(vector <string>& strs) {
        return findMinDeletionSize(strs);
    }
};

class SolutionTest {
public:
    void testMinDeletionSize() {
        Solution soln = Solution();
        vector <string> vecOfStrsIn;
        int deletionsOutExpected, deletionsOutComputed;

        vecOfStrsIn = {"ca","bb","ac"};
        deletionsOutExpected = 1;
        deletionsOutComputed = soln.minDeletionSize(vecOfStrsIn);
        assert(deletionsOutExpected == deletionsOutComputed);

        vecOfStrsIn = {"xc","yb","za"};
        deletionsOutExpected = 0;
        deletionsOutComputed = soln.minDeletionSize(vecOfStrsIn);
        assert(deletionsOutExpected == deletionsOutComputed);

        vecOfStrsIn = {"zyx","wvu","tsr"};
        deletionsOutExpected = 3;
        deletionsOutComputed = soln.minDeletionSize(vecOfStrsIn);
        assert(deletionsOutExpected == deletionsOutComputed);

        vecOfStrsIn = {"cmx","bpy","aoz"};
        deletionsOutExpected = 2;
        deletionsOutComputed = soln.minDeletionSize(vecOfStrsIn);
        assert(deletionsOutExpected == deletionsOutComputed);

        soln.enableDebug();
        vecOfStrsIn = {"abx","agz","bgc","bfc"};
        deletionsOutExpected = 1;
        deletionsOutComputed = soln.minDeletionSize(vecOfStrsIn);
        assert(deletionsOutExpected == deletionsOutComputed);
        soln.disableDebug();
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinDeletionSize();

    return 0;
}
