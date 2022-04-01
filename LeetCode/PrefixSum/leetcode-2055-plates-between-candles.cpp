// LeetCode-2055: https://leetcode.com/problems/plates-between-candles/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    vector<int> buildNextCandleOnLeftVec(string &str) {
        int len = str.size();

        vector<int> nextCandleLeftVec(len);

        int prevCandleIdx = -1;
        for (int i = 0; i < len; i++) {
            if (str.at(i) == '|') {
                prevCandleIdx = i;
            }
            nextCandleLeftVec[i] = prevCandleIdx;
        }

        return nextCandleLeftVec;
    }

    vector<int> buildNextCandleOnRightVec(string &str) {
        int len = str.size();

        vector<int> nextCandleRightVec(len);

        int prevCandleIdx = len;
        for (int i = len - 1; i >= 0; i--) {
            if (str.at(i) == '|') {
                prevCandleIdx = i;
            }
            nextCandleRightVec[i] = prevCandleIdx;
        }

        return nextCandleRightVec;
    }

    vector<int> buildNumPlatesLeftVec(string &str) {
        int len = str.size();

        vector<int> numPlatesLeftVec(len);

        int numPlatesLeft = 0;
        for (int i = 0; i < len; i++) {
            if (str.at(i) == '*') {
                numPlatesLeft++;
            }

            numPlatesLeftVec[i] = numPlatesLeft;
        }

        return numPlatesLeftVec;
    }

    int
    findNumPlatesBetweenCandlesInWindow(string &str,
                                        vector<int> &nextCandleLeftVec,
                                        vector<int> &nextCandleRightVec,
                                        vector<int> &numPlatesLeftVec,
                                        int lo,
                                        int hi) {
        int len = hi - lo + 1;
        if (len < 3) {
            return 0;
        }

        int leftCandleIdx = nextCandleRightVec[lo];
        int rightCandleIdx = nextCandleLeftVec[hi];

        int numPlates = 0;
        // this if-expression is important
        if (leftCandleIdx < rightCandleIdx) {
            numPlates = numPlatesLeftVec[rightCandleIdx] - numPlatesLeftVec[leftCandleIdx];
        }

        return numPlates;
    }

public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>> &queries) {
        vector<int> nextCandleLeftVec = buildNextCandleOnLeftVec(s);
        vector<int> nextCandleRightVec = buildNextCandleOnRightVec(s);
        vector<int> numPlatesLeftVec = buildNumPlatesLeftVec(s);

        int numQueries = queries.size();
        vector<int> answer(numQueries);

        for (int i = 0; i < queries.size(); i++) {
            answer[i] = findNumPlatesBetweenCandlesInWindow(
                    s, nextCandleLeftVec, nextCandleRightVec, numPlatesLeftVec,
                    queries[i][0], queries[i][1]
            );
        }

        return answer;
    }
};
