// LeetCode-225: https://leetcode.com/problems/implement-stack-using-queues/

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

class MyStack {
   private:
    queue<int> q1;
    queue<int> q2;

    int getInsertQue() {
        bool isQ1Empty = q1.empty();
        bool isQ2Empty = q2.empty();

        if (isQ1Empty && isQ2Empty) {
            return 1;
        } else if (isQ2Empty) {
            return 1;
        } else {
            return 2;
        }
    }

    int getLastEle(queue<int>& insertQue, queue<int>& auxilaryQue) {
        while (insertQue.size() > 1) {
            auxilaryQue.push(insertQue.front());
            insertQue.pop();
        }

        int lastEle = insertQue.front();
        insertQue.pop();

        return lastEle;
    }

   public:
    MyStack() {
    }

    void push(int x) {
        if (getInsertQue() == 1) {
            q1.push(x);
        } else {
            q2.push(x);
        }
    }

    int pop() {
        if (getInsertQue() == 1) {
            return getLastEle(q1, q2);
        } else {
            return getLastEle(q2, q1);
        }
    }

    int top() {
        int lastEle = pop();
        push(lastEle);

        return lastEle;
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
