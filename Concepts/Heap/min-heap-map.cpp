// https://www.youtube.com/watch?v=oP2-8ysT3QQ&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j&index=4&t=89s
// https://www.youtube.com/watch?v=t0Cq6tVNRBA

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

using namespace std;

class MinHeapMap {
   private:
    // instance variables
    vector<int> hVec;
    map<int, set<int> > hMap;
    int crrSize;
    int capacity;
    // constants
    static const int DEFAULT_CAP = 100;

    // private abbreviation functions
    int parentInd(int ind) {
        return ((ind - 1) / 2);
    }

    int lChildInd(int ind) {
        return ((2 * ind) + 1);
    }

    int rChildInd(int ind) {
        return ((2 * ind) + 2);
    }

    bool exists(int ind) {
        return ind < crrSize;
    }

    bool hasParent(int ind) {
        return ind != 0;
    }

    bool hasLChild(int ind) {
        return exists(ind) && (lChildInd(ind) < crrSize);
    }

    bool hasRChild(int ind) {
        return exists(ind) && (rChildInd(ind) < crrSize);
    }

    int parent(int ind) {
        if (exists(ind)) {
            return hVec[parentInd(ind)];
        } else {
            throw out_of_range("attempting to retrieve parent of non-existent index");
        }
    }

    int lChild(int ind) {
        if (exists(ind)) {
            if (exists(lChildInd(ind))) {
                return hVec[lChildInd(ind)];
            } else {
                throw out_of_range("attempting to retrieve non-existent left child");
            }
        } else {
            throw out_of_range("attempting to retrieve left child of non-existent index");
        }
    }

    int rChild(int ind) {
        if (exists(ind)) {
            if (exists(rChildInd(ind))) {
                return hVec[rChildInd(ind)];
            } else {
                throw out_of_range("attempting to retrieve non-existent right child");
            }
        } else {
            throw out_of_range("attempting to retrieve right child of non-existent index");
        }
    }

    // private helper functions
    void swap(int i, int j) {
        if (exists(i) && exists(j)) {
            int tmp = hVec[i];

            hMap[hVec[i]].erase(i);
            hVec[i] = hVec[j];
            hMap[hVec[i]].insert(i);

            hMap[hVec[j]].erase(j);
            hVec[j] = tmp;
            hMap[hVec[j]].insert(j);
        } else {
            throw out_of_range("attempting to swap values between non-existent indices");
        }
    }

    void ensureCapacity() {
        if (crrSize == capacity) {
            capacity = capacity * 2;
            hVec.resize(capacity);
        }
    }

    // private core functions
    void heapifyUp(int ind) {
        if (exists(ind)) {
            if (hVec[ind] < parent(ind)) {
                swap(ind, parentInd(ind));
                heapifyUp(parentInd(ind));
            }
        } else {
            throw out_of_range("attempting to up-heapify non-existent index");
        }
    }

    void heapifyDown(int ind) {
        if (exists(ind)) {
            if (hasLChild(ind)) {
                int minChildInd = lChildInd(ind);
                if (hasRChild(ind)) {
                    minChildInd = (lChild(ind) < rChild(ind)) ? lChildInd(ind) : rChildInd(ind);
                }

                if (hVec[minChildInd] < hVec[ind]) {
                    swap(minChildInd, ind);
                    // cout << "making recursive call to minHeapifyDown for ind = " + to_string(minChildInd) << endl;
                    heapifyDown(minChildInd);
                }
            }
        } else {
            throw out_of_range("attempting to down-heapify non-existent index = " + to_string(ind));
        }
    }

   public:
    bool empty() {
        return size() == 0;
    }

    int size() {
        return crrSize;
    }

    int top() {
        if (empty()) {
            throw out_of_range("attempting to access top of empty heap");
        } else {
            return hVec[0];
        }
    }

    void push(int ele) {
        ensureCapacity();

        crrSize++;
        hVec[crrSize - 1] = ele;
        hMap[ele].insert(crrSize - 1);

        heapifyUp(crrSize - 1);
    }

    int pop() {
        if (!empty()) {
            int topEle = top();

            swap(0, crrSize - 1);

            hMap[topEle].erase(crrSize - 1);
            crrSize--;

            if (crrSize > 0) {
                // cout << "calling heapifyDown on root node = " + to_string(top());
                heapifyDown(0);
            }

            return topEle;
        } else {
            throw out_of_range("attempting to pop element from empty heap");
        }
    }

    bool contains(int ele) {
        return !hMap[ele].empty();
    }

    void update(int crrVal, int newVal) {
        if (contains(crrVal)) {
            if (crrVal != newVal) {
                int firstInd = *(hMap[crrVal].begin());
                hMap[crrVal].erase(firstInd);

                hVec[firstInd] = newVal;
                hMap[newVal].insert(firstInd);

                if (newVal < crrVal) {
                    heapifyUp(firstInd);
                } else {
                    heapifyDown(firstInd);
                }
            }
        } else {
            throw invalid_argument("attempting to update value of non-existent element");
        }
    }

    // friend tester class
    friend class TestMinHeapMap;

    // constructor
    MinHeapMap() {
        capacity = DEFAULT_CAP;
        crrSize = 0;
        hVec.resize(capacity);
    }
};

class TestMinHeapMap {
   public:
    void testMap() {
        map<int, set<int> > m;
        m[0].insert(4);
        m[0].insert(3);
        set<int> out = {3, 4};
        assert(m[0] == out);
    }

    void testEmpty() {
        MinHeapMap h = MinHeapMap();

        assert(h.empty());

        h.push(0);
        assert(h.empty() == false);

        h.pop();
        assert(h.empty());
    }

    void testSize() {
        MinHeapMap h = MinHeapMap();

        assert(h.size() == 0);

        h.push(0);
        assert(h.size() == 1);

        h.push(0);
        assert(h.size() == 2);

        h.pop();
        assert(h.size() == 1);

        h.pop();
        assert(h.size() == 0);
    }

    void testPush() {
        MinHeapMap h = MinHeapMap();

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
        MinHeapMap h = MinHeapMap();

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

    void testContains() {
        MinHeapMap h = MinHeapMap();

        assert(h.contains(4) == false);

        h.push(9);
        // 9
        assert(h.contains(4) == false);

        assert(h.pop() == 9);
        //
        assert(h.contains(4) == false);

        h.push(4);
        // 4
        assert(h.contains(4) == true);

        h.push(2);
        // 2 4
        assert(h.contains(4) == true);

        h.push(7);
        // 2 4 7
        assert(h.contains(4) == true);

        assert(h.pop() == 2);
        // 4 7
        assert(h.contains(4) == true);

        assert(h.pop() == 4);
        // 7
        assert(h.contains(4) == false);

        h.push(3);
        // 3 7
        assert(h.contains(4) == false);
    }

    void testUpdate() {
        MinHeapMap h = MinHeapMap();
        //

        bool exceptionThrown = false;
        try {
            h.update(0, 1);
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        h.push(4);
        // 4
        h.push(1);
        // 1 4

        exceptionThrown = false;
        try {
            h.update(9, 5);
        } catch (...) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        h.update(1, 1);
        // 1 4
        assert(h.pop() == 1);
        // 4
        assert(h.pop() == 4);
        //
        assert(h.empty());

        h.push(4);
        // 4
        h.push(1);
        // 1 4
        h.update(1, -1);
        // -1 4
        assert(h.top() == -1);

        h.push(4);
        // -1 4 4
        assert(h.top() == -1);
        // -1 4 4

        h.push(3);
        // -1 3 4 4
        h.update(4, 2);
        // -1 2 3 4
        h.update(4, 0);
        // -1 0 2 3
        h.update(2, 9);
        // -1 0 3 9
        assert(h.pop() == -1);
        // 0 3 9

        h.update(3, 8);
        // 0 8 9
        assert(h.pop() == 0);
        // 8 9

        h.push(7);
        // 7 8 9
        h.push(2);
        // 2 7 8 9
        h.update(8, 4);
        // 2 4 7 9
        assert(h.pop() == 2);
        // 4 7 9
        assert(h.top() == 4);
        // 4 7 9

        h.update(9, -2);
        // -2 4 7
        assert(h.pop() == -2);
        // 4 7

        h.update(7, 0);
        // 0 4
        assert(h.pop() == 0);
        // 4
        h.update(4, 3);
        // 3
        assert(h.top() == 3);

        h.update(3, 5);
        // 5
        assert(h.pop() == 5);
        //
        assert(h.empty());
    }
};

int main() {
    TestMinHeapMap tester = TestMinHeapMap();
    tester.testMap();

    tester.testEmpty();
    tester.testSize();
    tester.testPush();
    tester.testPop();
    tester.testContains();
    tester.testUpdate();

    return 0;
}
