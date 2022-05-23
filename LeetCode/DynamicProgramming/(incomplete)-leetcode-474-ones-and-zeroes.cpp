// LeetCode-474: https://leetcode.com/problems/ones-and-zeroes/
// AlgorithmsMadeEasy: https://www.youtube.com/watch?v=qkUZ87NCYSw
// incomplete

#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <utility>

using namespace std;

class Solution {
private:
    vector<vector<vector<int> > > memoMat;

    void createMemoMat(int num1s, int num0s, int numStrs) {
        vector<vector<vector<int> > > memoMat(numStrs);

        for (int i = 0; i <= numStrs; i++) {
            vector<vector<int> > memoMatGrid(num0s + 1);

            for (int j = 0; j <= num0s; j++) {
                vector<int> memoMatRow(num1s + 1, INT_MIN);
                memoMatGrid[j] = memoMatRow;
            }

            memoMat[i] = memoMatGrid;
        }

        this->memoMat = memoMat;
    }

    pair<int, int> findFreqs(string& str) {
        int num1s = 0;
        int num0s = 0;

        for (auto it = str.begin(); it != str.end(); it++) {
            if (*it == '0') {
                num0s++;
            } else {
                num1s++;
            }
        }

        return {num0s, num1s};
    }

    vector<pair<int, int> > buildCountsVec(vector<string>& vec) {
        int len = vec.size();

        vector<pair<int, int> > countsVec(len);
        for (int i = 0; i < len; i++) {
            countsVec[i] = findFreqs(vec[i]);
        }

        return countsVec;
    }

    int findLargestSubsetSize(
            int remNum1s,
            int remNum0s,
            vector<pair<int, int> >& superset,
            int crrIdx
    ) {
        tuple<int, int, int> memoKey = {remNum0s, remNum1s, crrIdx};

        if (memoMat[crrIdx][remNum0s][remNum1s] != INT_MIN) {
            return memoMat[crrIdx][remNum0s][remNum1s];
        }

        int len = superset.size();
        if ((crrIdx >= len) || (remNum1s == 0) || (remNum0s == 0)) {
            memoMat[crrIdx][remNum0s][remNum1s] = 0;
            return 0;
        }
        if ((remNum1s < 0) || (remNum0s < 0)) {
            memoMat[crrIdx][remNum0s][remNum1s] = -1;
            return -1;
        }

        int excRes = findLargestSubsetSize(
                remNum1s,
                remNum0s,
                superset,
                crrIdx + 1
        );

        int incRes = INT_MIN;
        int newRemNum0s = remNum0s - superset[crrIdx].first;
        int newRemNum1s = remNum1s - superset[crrIdx].second;
        if ((newRemNum0s >= 0) && (newRemNum1s >= 0)) {
            incRes = findLargestSubsetSize(
                    newRemNum1s,
                    newRemNum0s,
                    superset,
                    crrIdx + 1
            ) + 1;
        }

        int crrRes = max(excRes, incRes);
        memoMat[crrIdx][remNum0s][remNum1s] = crrRes;

        return crrRes;
    }

public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        createMemoMat(n, m, strs.size());

        vector<pair<int, int> > countsVec = buildCountsVec(strs);
        return findLargestSubsetSize(
                n,
                m,
                countsVec,
                0
        ) + 1;
    }
};
