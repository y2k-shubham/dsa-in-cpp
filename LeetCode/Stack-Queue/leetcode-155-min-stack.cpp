// LeetCode-155: https://leetcode.com/problems/min-stack/

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

class MinStack {
   private:
    stack<int> eleStack;
    stack<int> minEleStack;

   public:
    MinStack() {
    }

    void push(int val) {
        eleStack.push(val);

        int crrMin = minEleStack.empty() ? val : minEleStack.top();
        if (val < crrMin) {
            minEleStack.push(val);
        } else {
            minEleStack.push(crrMin);
        }
    }

    void pop() {
        eleStack.pop();
        minEleStack.pop();
    }

    int top() {
        return eleStack.top();
    }

    int getMin() {
        return minEleStack.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
