// LeetCode-1654: https://leetcode.com/problems/minimum-jumps-to-reach-home/
// wrong answer: for 2nd test case our answer is correct, LC says its not possible

// UPDATE: looking at comments it appears that LC hasn't called it out but there's a max upper-bound
// beyond which we can't go, even if it leads to a valid path

#include <vector>
#include <climits>
#include <queue>
#include <utility>
#include <unordered_set>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

#define BEGIN_POSN 0
#define MAX 2002

class Solution {
private:
    vector<bool> isForbiddenMap;
    vector<int> minReachStepsMap;
    vector<int> prevPosnMap;
    queue<int> posnsToExploreQue;
    int dest;
    bool debug;

    unordered_set<int> createPosnsToExploreSet() {
        queue<int> posnsToExploreQue = this->posnsToExploreQue;

        unordered_set<int> posnsToExploreSet;
        while (!posnsToExploreQue.empty()) {
            posnsToExploreSet.insert(posnsToExploreQue.front());
            posnsToExploreQue.pop();
        }

        return posnsToExploreSet;
    }

    void showMinReachStepsMap(int crrPosn) {
        printf("Forb:\t");
        for (int i = 0; i <= this->dest + 2; i++) {
            if (isForbiddenMap[i]) {
                printf("X\t");
            } else {
                printf("\t");
            }
        }
        cout << endl;

        printf("Idx:\t");
        for (int i = 0; i <= this->dest + 2; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Steps:\t");
        for (int i = 0; i <= this->dest + 2; i++) {
            if (minReachStepsMap[i] == INT_MAX) {
                printf("-\t");
            } else {
                printf("%d\t", minReachStepsMap[i]);
            }
        }
        cout << endl;


        unordered_set<int> posnsToExploreSet = createPosnsToExploreSet();

        printf("Posns\t");
        for (int i = 0; i <= this->dest + 2; i++) {
            if (i == crrPosn) {
                printf("^\t");
            } else if (i == this->dest) {
                printf("D\t");
            } else if (posnsToExploreSet.find(i) != posnsToExploreSet.end()) {
                printf(".\t");
            } else {
                printf("\t");
            }
        }
        cout << endl;
    }

    void showPath() {
        if (minReachStepsMap[dest] == INT_MAX) {
            printf("cannot reach destination\n");
        }

        stack<int> stk;
        int crrPosn = dest;
        while ((crrPosn != BEGIN_POSN) && (prevPosnMap[crrPosn] != crrPosn)) {
            stk.push(crrPosn);
            crrPosn = prevPosnMap[crrPosn];
        }
        stk.push(BEGIN_POSN);

        printf("path to reach is:-\n");
        while (!stk.empty()) {
            if (stk.size() == 1) {
                printf("%d\n", stk.top());
            } else {
                printf("%d -> ", stk.top());
            }

            stk.pop();
        }
    }

    void buildIsForbiddenMap(vector<int>& forbidden) {
        vector<bool> isForbiddenMap(MAX, false);
        for (vector<int>::iterator i = forbidden.begin(); i != forbidden.end(); i++) {
            isForbiddenMap[*i] = true;
        }

        this->isForbiddenMap = isForbiddenMap;
    }

    void createMinBuildReachStepsMap() {
        vector<int> minReachStepsMap(MAX, INT_MAX);
        minReachStepsMap[0] = 0;

        this->minReachStepsMap = minReachStepsMap;
    }

    void createPrevPosnMap() {
        vector<int> prevPosnMap(MAX, INT_MAX);
        prevPosnMap[BEGIN_POSN] = BEGIN_POSN;

        this->prevPosnMap = prevPosnMap;
    }

    void calcMinReachSteps(int fwdStep, int backStep) {
        posnsToExploreQue.push(BEGIN_POSN);

        int iter = 1;
        while (!posnsToExploreQue.empty()) {
            int crrPosn = posnsToExploreQue.front();
            posnsToExploreQue.pop();
            int crrPosnReachSteps = minReachStepsMap[crrPosn];

            if (debug) {
                printf("/////////////////////////////////////\n");
                printf("---------------backStep=%d, fwdStep=%d-------------\n", backStep, fwdStep);
                printf("/////////////////////////////////////\n");

                printf("------------iter=%d begin------------\n", iter);
                showMinReachStepsMap(crrPosn);
            }

            if (crrPosnReachSteps == INT_MAX) {
                // some invalid (unreachable so far) entry added in queue
                continue;
            }

            int fwdPosn = crrPosn + fwdStep;
            if ((fwdPosn < MAX) && !isForbiddenMap[fwdPosn] && (minReachStepsMap[fwdPosn] > (crrPosnReachSteps + 1))) {
                minReachStepsMap[fwdPosn] = crrPosnReachSteps + 1;
                prevPosnMap[fwdPosn] = crrPosn;
                posnsToExploreQue.push(fwdPosn);
            }

            int backPosn = crrPosn - backStep;
            if ((backPosn > BEGIN_POSN) && !isForbiddenMap[backPosn] && (minReachStepsMap[backPosn] > (crrPosnReachSteps + 1))) {
                minReachStepsMap[backPosn] = crrPosnReachSteps + 1;
                prevPosnMap[backPosn] = crrPosn;
                posnsToExploreQue.push(backPosn);
            }

            if (debug) {
                showMinReachStepsMap(crrPosn);
                printf("------------iter=%d end------------\n", iter);
            }

            iter++;
        }
    }

public:
    friend class SolutionTest;

    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        if (x == BEGIN_POSN) {
            return 0;
        }
        this->dest = x;

        buildIsForbiddenMap(forbidden);
        createMinBuildReachStepsMap();
        createPrevPosnMap();

        calcMinReachSteps(a, b);

        return (minReachStepsMap[x] == INT_MAX) ? -1 : minReachStepsMap[x];
    }
};

class SolutionTest {
public:
    void testMinimumJumps() {
        Solution soln = Solution();
        vector<int> forbidden;
        int a, b, x;
        int outExpected, outComputed;

        forbidden = {14, 4, 18, 1, 15};
        a = 3;
        b = 15;
        x = 9;
        outExpected = 3;
        outComputed = soln.minimumJumps(forbidden, a, b, x);
        assert(outExpected == outComputed);

        // our answer is correct: LC says it's not possible
//        soln.debug = true;
        forbidden = {8, 3, 16, 6, 12, 20};
        a = 15;
        b = 13;
        x = 11;
        outExpected = -1;
        outComputed = soln.minimumJumps(forbidden, a, b, x);
        printf("outComputed = %d\n", outComputed);
        soln.showPath();
        assert(outExpected == outComputed);
//        soln.debug = false;

        forbidden = {1, 6, 2, 14, 5, 17, 4};
        a = 16;
        b = 9;
        x = 7;
        outExpected = 2;
        outComputed = soln.minimumJumps(forbidden, a, b, x);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinimumJumps();

    return 0;
}
