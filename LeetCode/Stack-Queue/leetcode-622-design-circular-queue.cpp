// LeetCode-622: https://leetcode.com/problems/design-circular-queue/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3696/
// note that Front() & Rear() functions have to handle empty queue case

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class MyCircularQueue {
   private:
    int front;
    int rear;
    int len;
    vector<int> vec;

    int currentSize() {
        if (isEmpty()) {
            return 0;
        }
        if (isFull()) {
            return this->len;
        }

        if (this->front <= this->rear) {
            // normal case
            return (this->rear - this->front + 1);
        } else {
            // reversed case
            return (this->len - this->front) + (this->rear + 1);
        }
    }

   public:
    MyCircularQueue(int k) {
        this->len = k;

        vector<int> vec(len);
        this->vec = vec;

        this->front = -1;
        this->rear = -1;
    }

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }

        if (currentSize() == 0) {
            // advance both front & rear
            this->front = 0;
            this->rear = 0;
        } else {
            // advance rear
            this->rear = (this->rear + 1) % this->len;
        }
        // add value
        this->vec[this->rear] = value;

        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }

        if (currentSize() == 1) {
            // mark que empty
            this->front = -1;
            this->rear = -1;
        } else {
            // advance front
            this->front = (this->front + 1) % this->len;
        }

        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }

        return this->vec[this->front];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }

        return this->vec[this->rear];
    }

    bool isEmpty() {
        return this->front == -1;
    }

    bool isFull() {
        return this->front == ((this->rear + 1) % this->len);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
