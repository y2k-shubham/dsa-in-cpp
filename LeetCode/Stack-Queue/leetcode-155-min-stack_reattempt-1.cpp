// LeetCode-155: https://leetcode.com/problems/min-stack/
// Companies: [Google][Amazon][Microsoft][Meta][Bloomberg][Infosys][Snowflake][Apple][Oracle][Yandex][Paytm][tcs][LinkedIn][Salesforce][Lyft][Walmart Labs][Nvidia]

// unclear why this one is slower than two-stack approach (one for actual numbers other for min number till now)

#include <stack>
#include <utility>

using namespace std;

class MinStack {
private:
    stack <pair <int, int> > mStack;

public:
    MinStack() {
        mStack = stack <pair <int, int> >();
    }

    void push(int value) {
        if (mStack.empty()) {
            mStack.push({value, value});
            return;
        }

        int crrMin = mStack.top().second;
        int newMin = min(crrMin, value);
        mStack.push({value, newMin});
    }

    void pop() {
        mStack.pop();
    }

    int top() {
        return mStack.top().first;
    }

    int getMin() {
        return mStack.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
