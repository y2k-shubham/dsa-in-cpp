// LeetCode-1381: https://leetcode.com/problems/design-a-stack-with-increment-operation/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int> > convertToVec(stack<pair<int, int> > stk) {
    int len = stk.size();
    if (len == 0) {
        return {};
    }

    vector<pair<int, int> > vec(len);

    int i = 0;
    while (!stk.empty()) {
        vec[i++] = stk.top();
        stk.pop();
    }

    reverse(vec.begin(), vec.end());

    return vec;
}

void showMap(map<int, pair<int, int> >& mMap) {
    printf("incOps map is:-\n");
    for (map<int, pair<int, int> >::iterator it = mMap.begin(); it != mMap.end(); it++) {
        printf("%d -> [%d, %d]\n", it->first, it->second.first, it->second.second);
    }
}

class CustomStack {
   private:
    int maxSize;
    int opIdx;
    map<int, pair<int, int> > incOps;
    stack<pair<int, int> > stk;
    bool debug;

    vector<pair<int, int> > getStackVec() {
        return convertToVec(this->stk);
    }

    void showIncOps() {
        showMap(this->incOps);
    }

    void setDebug(bool debug) {
        this->debug = debug;
    }

    void reset() {
        this->opIdx = 0;
        this->incOps.clear();

        stack<pair<int, int> > stk;
        this->stk = stk;

        this->debug = false;
    }

   public:
    friend class CustomStackTest;

    CustomStack(int maxSize) {
        this->maxSize = maxSize;
        this->opIdx = 0;
        this->debug = false;
    }

    void push(int x) {
        // invalid push op: stack full check
        if (this->stk.size() >= this->maxSize) {
            return;
        }

        // increment operation counter
        this->opIdx++;

        // persist element in stack along with operation counter
        this->stk.push({this->opIdx, x});
    }

    int pop() {
        // stack empty check
        int crrValPosn = this->stk.size();
        if (crrValPosn <= 0) {
            return -1;
        }

        // increment operation counter
        this->opIdx++;

        // extract value to be popped & it's insertion index
        int crrVal = this->stk.top().second;
        int crrValInsertIdx = this->stk.top().first;
        this->stk.pop();

        int totalAddend = 0;
        if (!this->incOps.empty()) {
            // find all increment ops applied before insertion of crrVal
            map<int, pair<int, int> >::iterator it = this->incOps.upper_bound(crrValInsertIdx);
            if (this->debug) {
                if (it == this->incOps.end()) {
                    printf("end\n");
                } else {
                    printf("%d -> [%d, %d]\n", it->first, it->second.first, it->second.second);
                }
            }

            // sum up all increment ops having k >= crrValPosn
            // (that is which are supposed to impact crrVal)
            while (it != this->incOps.end()) {
                if (it->second.first >= crrValPosn) {
                    totalAddend += it->second.second;
                }
                it++;
            }
        }

        // if stack became empty, clear all existing increment operations
        if (this->stk.empty()) {
            this->incOps.clear();
        }

        // return incremented value of crrVal
        return crrVal + totalAddend;
    }

    void increment(int k, int val) {
        // invalid increment op (stack empty check)
        if (this->stk.empty()) {
            return;
        }

        // increment operation counter
        this->opIdx++;

        // if stack doesn't have k elements, all elements will be incremented
        int adjustedK = min(k, (int)this->stk.size());

        // persist increment operation in map
        this->incOps[this->opIdx] = {adjustedK, val};
    }
};

class CustomStackTest {
   public:
    void testPush() {
        CustomStack cStk = CustomStack(3);
        vector<pair<int, int> > vecOutExpected;
        vector<pair<int, int> > vecOutComputed;

        vecOutExpected = {};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);

        cStk.push(21);

        vecOutExpected = {{1, 21}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);

        cStk.push(9);

        vecOutExpected = {{1, 21}, {2, 9}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);

        cStk.push(16);

        vecOutExpected = {{1, 21}, {2, 9}, {3, 16}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);

        cStk.push(7);

        vecOutExpected = {{1, 21}, {2, 9}, {3, 16}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
    }

    void testPop() {
        CustomStack cStk = CustomStack(3);
        vector<pair<int, int> > vecOutExpected;
        vector<pair<int, int> > vecOutComputed;
        map<int, pair<int, int> > incOpsOutExpected;
        map<int, pair<int, int> > incOpsOutComputed;
        int popOutExpected;
        int popOutComputed;

        vecOutExpected = {};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        popOutExpected = -1;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);
        incOpsOutExpected = {};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.push(4);

        vecOutExpected = {{1, 4}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        popOutExpected = 4;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);
        incOpsOutExpected = {};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.increment(3, 1);

        vecOutExpected = {};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        popOutExpected = -1;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);
        incOpsOutExpected = {};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.push(11);
        cStk.increment(3, 1);

        // cStk.setDebug(true);
        vecOutExpected = {{3, 11}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {{4, {1, 1}}};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);
        popOutExpected = 12;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);
        // cStk.setDebug(false);

        cStk.push(11);
        cStk.increment(3, 1);
        cStk.increment(2, 3);

        // cStk.setDebug(true);
        vecOutExpected = {{6, 11}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {{7, {1, 1}}, {8, {1, 3}}};
        incOpsOutComputed = cStk.incOps;
        // cStk.showIncOps();
        assert(incOpsOutExpected == incOpsOutComputed);
        popOutExpected = 15;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);
        // cStk.setDebug(false);

        // LeetCode sample test-case
        cStk.reset();

        cStk.push(1);
        cStk.push(2);

        popOutExpected = 2;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);

        cStk.push(2);
        cStk.push(3);
        cStk.push(4);

        cStk.increment(5, 100);
        cStk.increment(2, 100);

        popOutExpected = 103;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);

        popOutExpected = 202;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);

        popOutExpected = 201;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);

        popOutExpected = -1;
        popOutComputed = cStk.pop();
        assert(popOutExpected == popOutComputed);
    }

    void testIncrement() {
        CustomStack cStk = CustomStack(3);
        vector<pair<int, int> > vecOutExpected;
        vector<pair<int, int> > vecOutComputed;
        map<int, pair<int, int> > incOpsOutExpected;
        map<int, pair<int, int> > incOpsOutComputed;

        vecOutExpected = {};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.increment(3, 2);

        vecOutExpected = {};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.push(3);

        vecOutExpected = {{1, 3}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.increment(2, 9);

        vecOutExpected = {{1, 3}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {{2, {1, 9}}};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);

        cStk.increment(5, 4);

        vecOutExpected = {{1, 3}};
        vecOutComputed = cStk.getStackVec();
        assert(vecOutExpected == vecOutComputed);
        incOpsOutExpected = {{2, {1, 9}}, {3, {1, 4}}};
        incOpsOutComputed = cStk.incOps;
        assert(incOpsOutExpected == incOpsOutComputed);
    }
};

int main() {
    CustomStackTest cStkTest = CustomStackTest();

    cStkTest.testPush();
    cStkTest.testIncrement();
    cStkTest.testPop();

    return 0;
}

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
