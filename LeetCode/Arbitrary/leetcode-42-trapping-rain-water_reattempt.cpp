// LeetCode 42: trapping rain water
// https://leetcode.com/problems/trapping-rain-water/
// https://www.geeksforgeeks.org/trapping-rain-water/
// https://www.interviewbit.com/problems/rain-water-trapped/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>  // for using std::accumulate(..)
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl
             << endl;
    }

    void showIdxVec(vector<int>& valVec, vector<int>& idxVec, string name) {
        int len = idxVec.size();

        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < idxVec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < idxVec.size(); i++) {
            printf("%d\t", idxVec[i]);
        }
        cout << endl;

        printf("Deref:\t");
        for (int i = 0; i < idxVec.size(); i++) {
            int idx = idxVec[i];
            if ((0 <= idx) && (idx < len)) {
                printf("%d\t", valVec[idx]);
            } else {
                printf("-\t");
            }
        }
        cout << endl
             << endl;
    }

    vector<int> buildNgeLeft(vector<int>& vec) {
        int len = vec.size();

        vector<int> ngeLeftVec(len);
        ngeLeftVec[0] = -1;

        stack<int> stk;
        stk.push(0);

        for (int i = 1; i < len; i++) {
            int crrEle = vec[i];

            while (!stk.empty() && (vec[stk.top()] < crrEle)) {
                stk.pop();
            }

            ngeLeftVec[i] = stk.empty() ? -1 : stk.top();

            stk.push(i);
        }

        return ngeLeftVec;
    }

    vector<int> buildNgeRight(vector<int>& vec) {
        int len = vec.size();

        vector<int> ngeRightVec(len);
        ngeRightVec[len - 1] = len;

        stack<int> stk;
        stk.push(len - 1);

        for (int i = len - 2; i >= 0; i--) {
            int crrEle = vec[i];

            while (!stk.empty() && (vec[stk.top()] < crrEle)) {
                stk.pop();
            }

            ngeRightVec[i] = stk.empty() ? len : stk.top();

            stk.push(i);
        }

        return ngeRightVec;
    }

    void fillWaterLeftToRight(
        vector<int>& bars,
        vector<int>& barsNgeRight,
        vector<int>& water) {
        int len = bars.size();

        for (int i = 0; i < len; i++) {
            int ngeRightIdx = barsNgeRight[i];
            if ((ngeRightIdx == i + 1) || (ngeRightIdx == len)) {
                continue;
            }

            int crrBarHeight = bars[i];
            for (i = i + 1; i < ngeRightIdx; i++) {
                water[i] = max(water[i], crrBarHeight - bars[i]);
            }

            i--;
        }
    }

    void fillWaterRightToLeft(
        vector<int>& bars,
        vector<int>& barsNgeLeft,
        vector<int>& water) {
        int len = bars.size();

        for (int i = len - 1; i >= 0; i--) {
            int ngeLeftIdx = barsNgeLeft[i];
            if ((ngeLeftIdx == i - 1) || (ngeLeftIdx == -1)) {
                continue;
            }

            int crrBarHeight = bars[i];
            for (i = i - 1; i > ngeLeftIdx; i--) {
                water[i] = max(water[i], crrBarHeight - bars[i]);
            }

            i++;
        }
    }

   public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len <= 2) {
            return 0;
        }

        vector<int> ngeLeft = buildNgeLeft(height);
        vector<int> ngeRight = buildNgeRight(height);

        if (this->debug) {
            showVec(height, "height");
            showIdxVec(height, ngeLeft, "ngeLeft");
            showIdxVec(height, ngeRight, "ngeRight");
        }

        vector<int> water(len, 0);

        fillWaterLeftToRight(height, ngeRight, water);
        fillWaterRightToLeft(height, ngeLeft, water);

        int totalWater = accumulate(water.begin(), water.end(), 0);
        return totalWater;
    }
};
