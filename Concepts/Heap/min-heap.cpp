// https://www.youtube.com/watch?v=t0Cq6tVNRBA

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class MinHeap {
   private:
    // instance variables
    vector<int> hVec;
    int size;
    int cap;
    // constants
    static const int DEFAULT_CAP = 100;

    // private abbreviation functions
    int lCInd(int ind) {
        return ((2 * ind) + 1);
    }

    int rCInd(int ind) {
        return ((2 * ind) + 2);
    }

    int pInd(int ind) {
        return ((ind - 1) / 2);
    }

    bool exists(int ind) {
        return ind < size;
    }

    bool hasLC(int ind) {
        if (exists(ind)) {
            return lCInd(ind) < size;
        } else {
            return false;
        }
    }

    bool hasRC(int ind) {
        if (exists(ind)) {
            return rCInd(ind) < size;
        } else {
            return false;
        }
    }

    bool hasP(int ind) {
        return ind != 0;
    }

    int lC(int ind) {
        if (hasLC(ind)) {
            return hVec[lCInd(ind)];
        } else {
            throw out_of_range("attempting to access non-existent left child");
        }
    }

    int rC(int ind) {
        if (hasRC(ind)) {
            return hVec[rCInd(ind)];
        } else {
            throw out_of_range("attempting to access non-existent right child");
        }
    }

    int p(int ind) {
        if (hasP(ind)) {
            return hVec[pInd(ind)];
        } else {
            throw out_of_range("attempting to access parent of root node");
        }
    }

    // private helper functions
    void ensureCap() {
        if (size == cap) {
            cap = cap * 2;
            hVec.resize(cap, -1);
        }
    }

    void swap(int i, int j) {
        if (exists(i) && exists(j)) {
            int tmp = hVec[i];
            hVec[i] = hVec[j];
            hVec[j] = tmp;
        } else {
            throw out_of_range("attempting to swap values of non-existent indices");
        }
    }

    // private core methods
    void heapifyUp(int ind) {
        if (hasP(ind)) {
            if (hVec[ind] < p(ind)) {
                swap(ind, pInd(ind));
                heapifyUp(pInd(ind));
            }
        }
    }

    void heapifyDown(int ind) {
        if (hasLC(ind)) {
            int minCInd = lCInd(ind);
            if (hasRC(ind)) {
                minCInd = (lC(ind) < rC(ind)) ? lCInd(ind) : rCInd(ind);
            }

            if (hVec[minCInd] < hVec[ind]) {
                swap(minCInd, ind);
                heapifyDown(minCInd);
            }
        }
    }

   public:
    // public function / method
    int top() {
        if (size > 0) {
            return hVec[0];
        } else {
            throw out_of_range("attempting to read element from empty heap");
        }
    }

    void push(int ele) {
        ensureCap();

        ++size;
        hVec[size - 1] = ele;

        heapifyUp(size - 1);
    }

    int pop() {
        if (size > 0) {
            int topEle = top();

            swap(0, size - 1);
            // important to decrement size before calling minHeapify
            size--;

            heapifyDown(0);

            return topEle;
        } else {
            throw new out_of_range("attempting to extract element from empty heap");
        }
    }

    // friend tester class
    friend class MinHeapTester;

    // constructor
    MinHeap() {
        cap = DEFAULT_CAP;
        size = 0;
        hVec.resize(cap, -1);
    }
};

class MinHeapTester {
   public:
    void testLCInd() {
        MinHeap h = MinHeap();
        assert(h.lCInd(0) == 1);
        assert(h.lCInd(1) == 3);
        assert(h.lCInd(2) == 5);
    }

    void testRCInd() {
        MinHeap h = MinHeap();
        assert(h.rCInd(0) == 2);
        assert(h.rCInd(1) == 4);
        assert(h.rCInd(2) == 6);
    }

    void testPInd() {
        MinHeap h = MinHeap();
        assert(h.pInd(1) == 0);
        assert(h.pInd(2) == 0);
        assert(h.pInd(3) == 1);
        assert(h.pInd(4) == 1);
        assert(h.pInd(5) == 2);
        assert(h.pInd(6) == 2);
    }

    void testPush() {
        MinHeap h = MinHeap();

        bool exceptionThrown = false;
        try {
            h.top();
        } catch (const out_of_range& e) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        h.push(9);
        assert(h.top() == 9);

        h.push(4);
        assert(h.top() == 4);

        h.push(2);
        assert(h.top() == 2);

        h.push(7);
        assert(h.top() == 2);

        h.push(3);
        assert(h.top() == 2);

        h.push(1);
        assert(h.top() == 1);

        h.push(8);
        assert(h.top() == 1);
    }

    void testPop() {
        MinHeap h = MinHeap();

        bool exceptionThrown = false;
        try {
            h.pop();
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        h.push(9);
        // 9
        assert(h.pop() == 9);
        //

        h.push(4);
        // 4

        h.push(2);
        // 2 4

        h.push(7);
        // 2 4 7

        assert(h.pop() == 2);
        // 4 7
        assert(h.pop() == 4);
        // 7

        h.push(3);
        // 3 7

        assert(h.pop() == 3);
        // 7

        assert(h.pop() == 7);
        //

        exceptionThrown = false;
        try {
            h.pop();
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        h.push(7);
        // 7

        h.push(1);
        // 1 7
        h.push(8);
        // 1 7 8

        assert(h.pop() == 1);
        // 7 8
        assert(h.pop() == 7);
        // 8
        assert(h.pop() == 8);
        //

        exceptionThrown = false;
        try {
            h.pop();
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);
    }
};

int main() {
    MinHeapTester t = MinHeapTester();
    t.testLCInd();
    t.testRCInd();
    t.testPInd();
    t.testPush();
    t.testPop();

    return 0;
}
