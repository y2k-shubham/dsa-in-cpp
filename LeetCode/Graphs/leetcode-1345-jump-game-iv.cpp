// LeetCode-1345: https://leetcode.com/problems/jump-game-iv/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

using namespace std;

// taken from Concepts/Heap/min-heap-map.cpp
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

    // constructor
    MinHeapMap() {
        capacity = DEFAULT_CAP;
        crrSize = 0;
        hVec.resize(capacity);
    }
};

class Solution {
   private:
    map<int, set<int> > buildEleIndsMap(vector<int>& vec) {
        map<int, set<int> > eleIndsMap;
        for (int i = 0; i < vec.size(); i++) {
            eleIndsMap[vec[i]].insert(i);
        }
        return eleIndsMap;
    }

   public:
    int minJumps(vector<int>& arr) {
      
    }

    friend class TestSolution;
};

class TestSolution {
   public:
    void testBuildEleIndsMap() {
        Solution soln = Solution();
        vector<int> vec;
        map<int, set<int> > mapOutExpected;
        map<int, set<int> > mapOutComputed;

        vec = {};
        mapOutExpected = {};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);

        vec = {9};
        mapOutExpected = {{9, {0}}};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);

        vec = {9, 5};
        mapOutExpected = {{9, {0}}, {5, {1}}};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);

        vec = {9, 5, 8};
        mapOutExpected = {{9, {0}}, {5, {1}}, {8, {2}}};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);

        vec = {9, 5, 8, 5};
        mapOutExpected = {{9, {0}}, {5, {1, 3}}, {8, {2}}};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);

        vec = {9, 5, 8, 5, 1};
        mapOutExpected = {{9, {0}}, {5, {1, 3}}, {8, {2}}, {1, {4}}};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);

        vec = {9, 5, 8, 5, 1, 8};
        mapOutExpected = {{9, {0}}, {5, {1, 3}}, {8, {2, 5}}, {1, {4}}};
        mapOutComputed = soln.buildEleIndsMap(vec);
        assert(mapOutExpected == mapOutComputed);
    }
};

int main() {
    TestSolution testSoln = TestSolution();
    testSoln.testBuildEleIndsMap();

    return 0;
}
