// LeetCode-1653: https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/
// O(n) time & space; but barely accepted: speed & space both bottom 5 %tile

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
private:
    void showVec(string &str, vector<pair<int, int> > &countsSumVec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < countsSumVec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Str:\t");
        for (int i = 0; i < str.size(); i++) {
            printf("%c\t", str.at(i));
        }
        cout << endl;

        printf("a:\t");
        for (int i = 0; i < countsSumVec.size(); i++) {
            printf("[%d]\t", countsSumVec[i].first);
        }
        cout << endl;

        printf("b:\t");
        for (int i = 0; i < countsSumVec.size(); i++) {
            printf("[%d]\t", countsSumVec[i].second);
        }
        cout << endl;
    }

    vector<pair<int, int> > buildCountPrefSumVec(string &str) {
        int len = str.size();

        vector<pair<int, int> > countPrefSumVec(len);

        pair<int, int> prevCount = {0, 0};
        for (int i = 0; i < len; i++) {
            pair<int, int> crrCount = prevCount;
            if (str.at(i) == 'a') {
                crrCount.first++;
            } else {
                crrCount.second++;
            }

            countPrefSumVec[i] = crrCount;
            prevCount = crrCount;
        }

        return countPrefSumVec;
    }

    vector<pair<int, int> > buildCountSuffSumVec(string &str) {
        int len = str.size();

        vector<pair<int, int> > countSuffSumVec(len);

        pair<int, int> prevCount = {0, 0};
        for (int i = len - 1; i >= 0; i--) {
            pair<int, int> crrCount = prevCount;
            if (str.at(i) == 'a') {
                crrCount.first++;
            } else {
                crrCount.second++;
            }

            countSuffSumVec[i] = crrCount;
            prevCount = crrCount;
        }

        return countSuffSumVec;
    }

    int calcRemovalsKeepLeftARightB(
            vector<pair<int, int> > &countPrefSum,
            vector<pair<int, int> > &countSuffSum,
            int idx) {
        // remove all B's from left (including current index)
        int bRemovalCount = countPrefSum[idx].second;

        // remove all A's from right (after current index)
        int len = countSuffSum.size();
        int aRemovalCount = (idx == (len - 1)) ? 0 : countSuffSum[idx + 1].first;

        return bRemovalCount + aRemovalCount;
    }

    int calcRemovalsKeepOnlyA(
            vector<pair<int, int> > &countPrefSum,
            vector<pair<int, int> > &countSuffSum,
            int idx
    ) {
        // remove all B's from left (including current index)
        int bRemovalCountLeft = countPrefSum[idx].second;

        // remove all B's from right (after current index)
        int len = countSuffSum.size();
        int bRemovalCountRight = (idx == (len - 1)) ? 0 : countSuffSum[idx + 1].second;

        return bRemovalCountLeft + bRemovalCountRight;
    }

    int calcRemovalsKeepOnlyB(
            vector<pair<int, int> > &countPrefSum,
            vector<pair<int, int> > &countSuffSum,
            int idx
    ) {
        // remove all A's from left (including current index)
        int aRemovalCountLeft = countPrefSum[idx].first;

        // remove all A's from right (after current index)
        int len = countSuffSum.size();
        int aRemovalCountRight = (idx == (len - 1)) ? 0 : countSuffSum[idx + 1].first;

        return aRemovalCountLeft + aRemovalCountRight;
    }

public:
    friend class SolutionTest;

    int minimumDeletions(string s) {
        int len = s.size();
        if (len <= 1) {
            return 0;
        }

        vector<pair<int, int>> countPrefSumVec = buildCountPrefSumVec(s);
        vector<pair<int, int>> countSuffSumVec = buildCountSuffSumVec(s);

        int minDeletionsGlobal = INT_MAX;
        for (int i = 0; i < len; i++) {
            int countKeepLeftARightB = calcRemovalsKeepLeftARightB(countPrefSumVec, countSuffSumVec, i);
            int countKeepOnlyA = calcRemovalsKeepOnlyA(countPrefSumVec, countSuffSumVec, i);
            int countKeepOnlyB = calcRemovalsKeepOnlyB(countPrefSumVec, countSuffSumVec, i);

            int minDeletionsCrr = min(countKeepLeftARightB, min(countKeepOnlyA, countKeepOnlyB));
            minDeletionsGlobal = min(minDeletionsGlobal, minDeletionsCrr);
        }

        return minDeletionsGlobal;
    }
};

class SolutionTest {
public:
    void testBuildCountPrefSumVec() {
        Solution soln = Solution();
        string strIn;
        vector<pair<int, int> > outExpected, outComputed;

        strIn = "";
        outExpected = {};
        outComputed = soln.buildCountPrefSumVec(strIn);
        assert(outExpected == outComputed);

        strIn = "a";
        outExpected = {{1, 0}};
        outComputed = soln.buildCountPrefSumVec(strIn);
        assert(outExpected == outComputed);

        strIn = "aab";
        outExpected = {{1, 0},
                       {2, 0},
                       {2, 1}};
        outComputed = soln.buildCountPrefSumVec(strIn);
        assert(outExpected == outComputed);
    }

    void testBuildCountSuffSumVec() {
        Solution soln = Solution();
        string strIn;
        vector<pair<int, int> > outExpected, outComputed;

        strIn = "";
        outExpected = {};
        outComputed = soln.buildCountSuffSumVec(strIn);
        assert(outExpected == outComputed);

        strIn = "a";
        outExpected = {{1, 0}};
        outComputed = soln.buildCountSuffSumVec(strIn);
        assert(outExpected == outComputed);

        strIn = "aab";
        outExpected = {{2, 1},
                       {1, 1},
                       {0, 1}};
        outComputed = soln.buildCountSuffSumVec(strIn);
        assert(outExpected == outComputed);
    }

    void testMinimumDeletions() {
        Solution soln = Solution();
        string strIn;
        int outExpected, outComputed;

        strIn = "";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "a";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "b";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "aa";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "bb";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "ab";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "aba";
        outExpected = 1;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "aab";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "abb";
        outExpected = 0;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "ba";
        outExpected = 1;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "baa";
        outExpected = 1;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "baaba";
        outExpected = 2;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "aababbab";
        outExpected = 2;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);

        strIn = "bbaaaaabb";
        outExpected = 2;
        outComputed = soln.minimumDeletions(strIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildCountPrefSumVec();
    solnTest.testBuildCountSuffSumVec();
    solnTest.testMinimumDeletions();

    return 0;
}
