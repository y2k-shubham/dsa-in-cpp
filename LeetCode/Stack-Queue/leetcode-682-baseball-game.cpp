// LeetCode-682: https://leetcode.com/problems/baseball-game/
// straight-forward problem; should skip looking

#include <stack>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool debug = true;

    // unused method
    int stackPopTop(stack<int>& stk) {
        if (stk.empty()) {
            return INT_MIN;
        }

        int top = stk.top();
        stk.pop();
        return top;
    }

    pair<int, int> stackTop2(stack<int>& stk) {
        int top1 = stk.top();
        stk.pop();

        int top2 = stk.top();

        stk.push(top1);
        return {top1, top2};
    }

    int stackSum(stack<int>& stk) {
        int sum = 0;

        while (!stk.empty()) {
            sum += stk.top();
            stk.pop();
        }

        return sum;
    }

    void stackShow(stack<int> stk) {
        printf("stack is:-\n");

        while (!stk.empty()) {
            printf("%d\t", stk.top());
            stk.pop();
        }
        cout << endl;
    }

public:
    const string SUM_OP = "+";
    const string DOUBLE_OP = "D";
    const string INVALIDATE_OP = "C";

    int calPoints(vector<string>& ops) {
        stack<int> stk;

        for (int i = 0; i < ops.size(); i++) {
            string op = ops[i];

            if (op == SUM_OP) {
                pair<int, int> top2 = stackTop2(stk);
                int sum = top2.first + top2.second;
                stk.push(sum);
            } else if (op == DOUBLE_OP) {
                int prev = stk.top();
                int _double = prev * 2;
                stk.push(_double);
            } else if (op == INVALIDATE_OP) {
                stk.pop();
            } else {
                int score = stoi(op);
                stk.push(score);
            }

            if (debug) {
                printf("\nafter ops[i=%d] = '%s'\n", i, op.c_str());
                stackShow(stk);
            }
        }

        return stackSum(stk);
    }
};
