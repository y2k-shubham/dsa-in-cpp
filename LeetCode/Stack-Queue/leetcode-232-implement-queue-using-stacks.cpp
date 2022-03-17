// LeetCode-232: https://leetcode.com/problems/implement-queue-using-stacks/
// unoptimized, brute-force solution

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
   private:
    stack<int> stk1;
    stack<int> stk2;
    int pushStk;
    int popStk;

    void transferElesUtil(stack<int>& srcStk, stack<int>& dstStk) {
        while (!srcStk.empty()) {
            dstStk.push(srcStk.top());
            srcStk.pop();
        }
    }

    void checkAndTransferElesIfRequired() {
        if (popStk == 1) {
            if (stk1.empty() && !stk2.empty()) {
                transferElesUtil(stk2, stk1);
            }
        } else {
            if (stk2.empty() && !stk1.empty()) {
                transferElesUtil(stk1, stk2);
            }
        }
    }

   public:
    MyQueue() {
        pushStk = 1;
        popStk = 2;
    }

    void push(int x) {
        if (pushStk == 1) {
            stk1.push(x);
        } else {
            stk2.push(x);
        }
    }

    int pop() {
        checkAndTransferElesIfRequired();

        int poppedEle;
        if (popStk == 1) {
            poppedEle = stk1.top();
            stk1.pop();
        } else {
            poppedEle = stk2.top();
            stk2.pop();
        }

        return poppedEle;
    }

    int peek() {
        checkAndTransferElesIfRequired();

        int peekedEle;
        if (popStk == 1) {
            peekedEle = stk1.top();
        } else {
            peekedEle = stk2.top();
        }

        return peekedEle;
    }

    bool empty() {
        return stk1.empty() && stk2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
