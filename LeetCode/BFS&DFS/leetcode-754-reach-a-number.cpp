// LeetCode-754: https://leetcode.com/problems/reach-a-number/
// LC Monthly Challenge (Dec 2020) : https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3583/

#include <cassert>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    int calcNumSteps(int target) {
        queue<int> posnQue;
        posnQue.push(0);

        bool found = false;
        int moveNo = 0;
        while (!found) {
            int queLen = posnQue.size();
            moveNo++;

            for (int i = 1; i <= queLen; i++) {
                int posn = posnQue.front();
                posnQue.pop();

                if (posn + moveNo == target) {
                    return moveNo;
                } else {
                    posnQue.push(posn + moveNo);
                }

                if (posn - moveNo == target) {
                    return moveNo;
                } else {
                    posnQue.push(posn - moveNo);
                }
            }
        }

        return -1;
    }

   public:
    int reachNumber(int target) {
        return calcNumSteps(target);
    }

    friend class TestSolution;
};

class TestSolution {
   public:
    void testCalcNumSteps() {
        Solution soln = Solution();
        int target;
        int movesOutExpected;
        int movesOutComputed;

        target = 1;
        movesOutExpected = 1;
        movesOutComputed = soln.calcNumSteps(target);
        assert(movesOutExpected == movesOutComputed);

        target = 3;
        movesOutExpected = 2;
        movesOutComputed = soln.calcNumSteps(target);
        assert(movesOutExpected == movesOutComputed);

        target = 2;
        movesOutExpected = 3;
        movesOutComputed = soln.calcNumSteps(target);
        assert(movesOutExpected == movesOutComputed);

        // this doesnt complete in even 10 seconds
        target = -1000000000;
        movesOutExpected = 3;  // result unknown
        movesOutComputed = soln.calcNumSteps(target);
        cout << movesOutComputed << endl;
        assert(movesOutExpected == movesOutComputed);
    }
};

int main() {
    TestSolution testSoln = TestSolution();
    testSoln.testCalcNumSteps();

    return 0;
}
