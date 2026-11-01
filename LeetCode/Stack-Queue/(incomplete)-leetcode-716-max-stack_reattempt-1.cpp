// LeetCode-716: https://leetcode.com/problems/max-stack/
// Premium
// Companies: [LinkedIn][Walmart Labs][Amazon][Lyft][Google][Meta][TikTok][Woven by Toyota][Nutanix]

// incomplete

#include <stack>
#include <map>

using namespace std;

class MaxStack {
private:
    stack <int> mStack;
    map <int, int> mFreqMap;

public:
    MaxStack() {
        mStack = stack<int>();
        mFreqMap.clear();
    }

    void push(int x) {
        mStack.push(x);
        mFreqMap[x]++;
    }

    int pop() {
        int x = mStack.top();

        mStack.pop();
        mFreqMap[x]--;

        return x;
    }

    int top() {
        return mStack.top();
    }

    int peekMax() {
        return mFreqMap.rbegin()->first;
    }

    int popMax() {

    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */
