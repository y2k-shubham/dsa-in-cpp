// LeetCode-946: https://leetcode.com/problems/validate-stack-sequences/

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    bool canPush(vector<int>& pushed, int iPush, stack<int>& stk) {
        return iPush < pushed.size();
    }

    void doPush(vector<int>& pushed, int& iPush, stack<int>& stk) {
        stk.push(pushed[iPush++]);
    }

    bool canPop(vector<int>& popped, int iPop, stack<int>& stk) {
        return (iPop < popped.size()) && !stk.empty() && (popped[iPop] == stk.top());
    }

    void doPop(vector<int>& popped, int& iPop, stack<int>& stk) {
        stk.pop();
        iPop++;
    }

   public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;

        int iPush = 0;
        int iPop = 0;
        int len = pushed.size();

        int iter = 0;
        while (canPop(popped, iPop, stk) || canPush(pushed, iPush, stk)) {
            // printf("\niter=%d, len=%d, iPush=%d, iPop=%d\n", iter, len, iPush, iPop);

            while (canPop(popped, iPop, stk)) {
                // printf("popping popped[iPop=%d] = %d\n", iPop, popped[iPop]);
                doPop(popped, iPop, stk);
            }

            while (canPush(pushed, iPush, stk)) {
                // printf("pushing pushed[iPush=%d] = %d\n", iPush, pushed[iPush]);
                doPush(pushed, iPush, stk);

                if (canPop(popped, iPop, stk)) {
                    break;
                }
            }
        }

        // printf("\nreturning %s\n", (stk.empty() ? "true" : "false"));
        // printf("----------\n");

        return stk.empty();
    }
};
