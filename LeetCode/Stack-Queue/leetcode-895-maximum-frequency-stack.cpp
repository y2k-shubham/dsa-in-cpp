// LeetCode-895: https://leetcode.com/problems/maximum-frequency-stack/
// AlgorithmsMadeEasy: https://www.youtube.com/watch?v=0fRmVjxopiE

#include <climits>
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class FreqStack {
   private:
    unordered_map<int, stack<int> > freqStack;
    unordered_map<int, int> freqMap;
    int maxFreq;

   public:
    FreqStack() {
        this->maxFreq = 0;
    }

    void push(int val) {
        int crrFreq = this->freqMap[val];
        int newFreq = crrFreq + 1;

        this->freqMap[val] = newFreq;
        this->maxFreq = max(this->maxFreq, newFreq);

        this->freqStack[newFreq].push(val);
    }

    int pop() {
        int maxFreqEle = this->freqStack[this->maxFreq].top();
        this->freqMap[maxFreqEle]--;

        this->freqStack[this->maxFreq].pop();
        if (this->freqStack[this->maxFreq].empty()) {
            this->maxFreq--;
        }

        return maxFreqEle;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
