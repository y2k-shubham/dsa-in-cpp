// LeetCode-739: https://leetcode.com/problems/daily-temperatures/

#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
private:

    static vector <int> createNgeRightIdxVec(const vector <int>& myVec) {
        int len = myVec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {0};
        }

        stack <pair<int, int>> ngeRightEleIdxStk;
        vector <int> ngeRightIdxVec(len);

        for (int i = len - 1; i >= 0; i--) {
            int crrVal = myVec[i];

            while (!ngeRightEleIdxStk.empty() && (ngeRightEleIdxStk.top().first <= crrVal)) {
                ngeRightEleIdxStk.pop();
            }

            int ngeRightIdx = ngeRightEleIdxStk.empty() ? INT_MAX : ngeRightEleIdxStk.top().second;
            ngeRightIdxVec[i] = ngeRightIdx;

            ngeRightEleIdxStk.push({crrVal, i});
        }

        return ngeRightIdxVec;
    }

    static vector <int> createNgeRightIdxDiffVec(const vector <int>& ngeRightIdxVec) {
        int len = ngeRightIdxVec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {0};
        }

        vector <int> ngeRightIdxDiffVec(len);
        for (int i = len - 1; i >= 0; i--) {
            int ngeRightIdxDiff = (ngeRightIdxVec[i] == INT_MAX) ? 0 : (ngeRightIdxVec[i] - i);
            ngeRightIdxDiffVec[i] = ngeRightIdxDiff;
        }

        return ngeRightIdxDiffVec;
    }

public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector <int> ngeRightIdxVec = createNgeRightIdxVec(temperatures);

        vector <int> ngeRightIdxDiffVec = createNgeRightIdxDiffVec(ngeRightIdxVec);
        return ngeRightIdxDiffVec;
    }
};

