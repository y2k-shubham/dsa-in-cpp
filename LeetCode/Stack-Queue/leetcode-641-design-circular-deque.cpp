// LeetCode-641: https://leetcode.com/problems/design-circular-deque
// note that Front() & Rear() functions have to handle empty queue case

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class MyCircularDeque {    
private:
    int front;
    int rear;
    vector <int> vec;
    int len;
    
    int getSize() {
        if (isEmpty()) {
            return 0;
        }
        
        if (this->front <= this->rear) {
            return this->rear - this->front + 1;
        } else {
            return (len - this->front) + (this->rear + 1);
        }
    }
    
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        this->len = k;
        
        vector <int> vec(this->len);
        this->vec = vec;
        
        this->front = -1;
        this->rear = -1;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (isFull()) {
            return false;
        }
        
        if (isEmpty()) {
            this->front = 0;
            this->rear = 0;
        } else {
            this->front = (this->front == 0) ? (this->len - 1) : (this->front - 1);
        }
        
        this->vec[this->front] = value;
        
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        
        if (isEmpty()) {
            this->front = 0;
            this->rear = 0;
        } else {
            this->rear = (this->rear + 1) % this->len;
        }
        
        this->vec[this->rear] = value;
        
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        
        if (getSize() == 1) {
            this->front = -1;
            this->rear = -1;
        } else {
            this->front = (this->front + 1) % this->len;
        }
        
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        
        if (getSize() == 1) {
            this->front = -1;
            this->rear = -1;
        } else {
            this->rear = (this->rear == 0) ? (this->len - 1) : (this->rear - 1);
        }
        
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        
        return this->vec[this->front];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        if (isEmpty()) {
            return -1;
        }
        
        return this->vec[this->rear];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return this->front == -1;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return getSize() == this->len;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
