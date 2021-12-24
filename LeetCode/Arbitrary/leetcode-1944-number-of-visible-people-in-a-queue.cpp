// LeetCode-1944: https://leetcode.com/problems/number-of-visible-people-in-a-queue/
// hard problem
// note that for simplification, they've said that all heights will be unique

// runs fine on Mac, gives segfault on LC submission (addressSanitizer: heap-buffer-overflow on address)

#include <cassert>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug;

    void showVec(vector<int>& vec, string name) {
        printf("\n%s vec is:-\n", name.c_str());

        printf("ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    vector<int> buildNgeLeft(vector<int>& heights, vector<int>& numPersons) {
        int len = heights.size();
        if (len == 0) {
            return {};
        }

        vector<int> ngeLeft(len, -1);
        stack<int> stk;
        for (int i = 0; i < len; i++) {
            int crrEle = heights[i];
            while (!stk.empty() && (heights[stk.top()] < crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeLeft[i] = stk.top();
                numPersons[stk.top()]++;
            }

            stk.push(i);
        }

        return ngeLeft;
    }

    vector<int> buildNgeRight(vector<int>& heights) {
        int len = heights.size();
        if (len == 0) {
            return {};
        }

        vector<int> ngeRight(len, len);
        stack<int> stk;
        for (int i = len; i >= 0; i--) {
            int crrEle = heights[i];

            while (!stk.empty() && (heights[stk.top()] < crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeRight[i] = stk.top();
            }

            stk.push(i);
        }

        return ngeRight;
    }

    void fillNumPersonsRtoL(vector<int>& heights, vector<int>& ngeRight, vector<int>& numPersons) {
        int len = heights.size();
        if (len == 0) {
            return;
        }

        for (int i = len - 1; i >= 0; i--) {
            if ((ngeRight[i] < len) && (heights[i] != heights[ngeRight[i]])) {
                // numPersons[i] += 1 + numPersons[ngeRight[i]];
                numPersons[i]++;
            }
        }
    }

   public:
    friend class SolutionTest;

    vector<int> canSeePersonsCount(vector<int>& heights) {
        if (this->debug) {
            showVec(heights, "heights");
        }

        int len = heights.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {0};
        }

        vector<int> numPersons(len, 0);

        vector<int> ngeRight = buildNgeRight(heights);
        if (this->debug) {
            showVec(ngeRight, "ngeRight");
        }

        fillNumPersonsRtoL(heights, ngeRight, numPersons);
        if (this->debug) {
            showVec(numPersons, "after ngeRightFill, numPersons");
        }

        vector<int> ngeLeft = buildNgeLeft(heights, numPersons);
        if (this->debug) {
            showVec(ngeLeft, "ngeLeft");
            showVec(numPersons, "after ngeLeftFill, numPersons");
        }

        return numPersons;
    }
};

class SolutionTest {
   public:
    void testCanSeePersonsCount() {
        Solution soln = Solution();
        vector<int> inHeights;
        vector<int> outNumPersonsExpected, outNumPersonsComputed;

        inHeights = {};
        outNumPersonsExpected = {};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        inHeights = {3};
        outNumPersonsExpected = {0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        // soln.debug = true;
        inHeights = {10, 6, 8, 5, 11, 9};
        outNumPersonsExpected = {3, 1, 2, 1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);
        // soln.debug = false;

        inHeights = {5, 1, 2, 3, 10};
        outNumPersonsExpected = {4, 1, 1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        // soln.debug = true;
        inHeights = {4, 5};
        outNumPersonsExpected = {1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);
        // soln.debug = false;

        inHeights = {5, 4};
        outNumPersonsExpected = {1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        // invalid test case because all heights are supposed to be unique
        // soln.debug = true;
        inHeights = {6, 6};
        outNumPersonsExpected = {1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);
        // soln.debug = false;

        inHeights = {6, 4, 5};
        outNumPersonsExpected = {2, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        inHeights = {6, 5, 4};
        outNumPersonsExpected = {1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        inHeights = {5, 4, 6};
        outNumPersonsExpected = {2, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        inHeights = {5, 6, 4};
        outNumPersonsExpected = {1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        inHeights = {4, 6, 5};
        outNumPersonsExpected = {1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        inHeights = {4, 3, 5};
        outNumPersonsExpected = {2, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);

        // soln.debug = true;
        inHeights = {1, 2, 3, 4};
        outNumPersonsExpected = {1, 1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);
        // soln.debug = false;

        inHeights = {4, 3, 2, 1};
        outNumPersonsExpected = {1, 1, 1, 0};
        outNumPersonsComputed = soln.canSeePersonsCount(inHeights);
        assert(outNumPersonsExpected == outNumPersonsComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCanSeePersonsCount();

    return 0;
}
