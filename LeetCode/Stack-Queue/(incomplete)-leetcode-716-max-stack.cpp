// LeetCode-716: https://leetcode.com/problems/max-stack/
// Premium
// Companies: [LinkedIn][Walmart Labs][Amazon][Lyft][Google][Meta][TikTok][Woven by Toyota][Nutanix]

// incomplete

/**
 * Fails on following input:
 * ["MaxStack","push","peekMax","push","peekMax","push","pop","pop","push","peekMax","push","popMax","top","push","push","peekMax","popMax","popMax"]
 * [[],[92],[],[54],[],[22],[],[],[-57],[],[-24],[],[],[26],[-71],[],[],[]]
 *
 * Expected:
 * [null,null,92,null,92,null,22,54,null,92,null,92,-24,null,null,26,26,-24]
 */

#include <stack>
#include <unordered_map>
#include <queue>

using namespace std;

class MaxStack {
private:
    stack <int> mStack;
    priority_queue<int> mMaxHeap;
    unordered_map<int, int> mFreqMap;

    void tryRemoveFromStackTop(int x) {
        if (mStack.top() == x) {
            mStack.pop();
        }
    }

    void tryRemoveFromHeapTop(int x) {
        if (mMaxHeap.top() == x) {
            mMaxHeap.pop();
        }
    }

public:
    MaxStack() {
        mStack = stack <int>();
        mMaxHeap = priority_queue<int>();
        mFreqMap.clear();
    }

    void push(int x) {
        // add to stack
        mStack.push(x);

        // add to max-heap
        mMaxHeap.push(x);

        // add to freq-map
        mFreqMap[x]++;
    }

    int pop() {
        // read top-most element
        int x = mStack.top();

        // remove from stack
        mStack.pop();

        // remove from max-heap
        tryRemoveFromHeapTop(x);

        // remove from freq-map
        mFreqMap[x]--;

        return x;
    }

    int top() {
        int x;
        int freq;

        do {
            x = mStack.top();
            freq = mFreqMap[x];

            if (freq <= 0) {
                // remove from stack
                mStack.pop();

                // remove from max-heap
                tryRemoveFromHeapTop(x);
            }
        } while (!mStack.empty() && (freq <= 0));

        return x;
    }

    int peekMax() {
        int x;
        int freq;

        do {
            x = mMaxHeap.top();
            freq = mFreqMap[x];

            if (freq <= 0) {
                // remove from max-heap
                mMaxHeap.pop();

                // remove from stack
                tryRemoveFromStackTop(x);
            }
        } while (!mMaxHeap.empty() && (freq <= 0));

        return x;
    }

    int popMax() {
        // read max element
        int x = mMaxHeap.top();

        // remove from heap
        mMaxHeap.pop();

        // remove from stack
        tryRemoveFromStackTop(x);

        // remove from freq-map
        mFreqMap[x]--;

        return x;
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
