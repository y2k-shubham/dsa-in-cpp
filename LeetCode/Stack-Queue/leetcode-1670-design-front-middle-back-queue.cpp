// LeetCode-1670: https://leetcode.com/problems/design-front-middle-back-queue/

#include <list>
#include <sstream>
#include <cstdio>
#include <iostream>

using namespace std;

class FrontMiddleBackQueue {
private:
    list<int> q1;
    list<int> q2;
    ostringstream oss;

    bool debug = false;

    void moveEleBackToFront(list<int>& fromQ, list<int>& toQ) {
        if (fromQ.empty()) {
            return;
        }

        toQ.push_front(fromQ.back());
        fromQ.pop_back();
    }

    void balanceQsBeforePushMiddle() {
        if (q1.size() == q2.size()) {
            return;
        }

        moveEleBackToFront(q1, q2);
    }

    void balanceQs() {
        while (q1.size() < q2.size()) {
            q1.push_back(q2.front());
            q2.pop_front();
        }

        while (((int) q1.size()) > (((int) q2.size()) + 1)) {
            q2.push_front(q1.back());
            q1.pop_back();
        }
    }

    void showQ(list<int>& q, const char* name) {
        printf("%s que is:-\n", name);

        while (!q.empty()) {
            printf("%d ", q.front());
            q.pop_front();
        }
        cout << endl;
    }

    void showQs() {
        list<int> q1 = this->q1;
        showQ(q1, "q1");

        list<int> q2 = this->q2;
        showQ(q2, "q2");
    }

    void showBigSeparator() {
        printf("\n=================\n");
    }

    void showSmallSeparator() {
        printf("\n. . . . . . . . .\n");
    }

    void debugNormalLog(string msg, bool begin) {
        if (begin) {
            showBigSeparator();
        } else {
            showSmallSeparator();
        }

        cout << msg << endl;
        showSmallSeparator();
        showQs();

        if (begin) {
            showSmallSeparator();
        } else {
            showBigSeparator();
        }
    }

    void debugSkipLog(string msg) {
        showBigSeparator();
        cout << msg << endl;
        showBigSeparator();
    }

public:
    friend class FrontMiddleBackQueueTest;

    FrontMiddleBackQueue() {

    }

    void pushFront(int val) {
        q1.push_front(val);
        if (debug) {
            oss.str("");
            oss << "after pushFront(" << val << ")";
            debugNormalLog(oss.str(), true);
        }

        balanceQs();
        if (debug) {
            oss.str("");
            oss << "after balanceQs()";
            debugNormalLog(oss.str(), false);
        }
    }

    void pushMiddle(int val) {
        balanceQsBeforePushMiddle();
        if (debug) {

        }

        q1.push_back(val);
        if (debug) {
            oss.str("");
            oss << "after pushMiddle(" << val << ")";
            debugNormalLog(oss.str(), true);
        }

        balanceQs();
        if (debug) {
            oss.str("");
            oss << "after balanceQs()";
            debugNormalLog(oss.str(), false);
        }
    }

    void pushBack(int val) {
        q2.push_back(val);
        if (debug) {
            oss.str("");
            oss << "after pushBack(" << val << ")";
            debugNormalLog(oss.str(), true);
        }

        balanceQs();
        if (debug) {
            oss.str("");
            oss << "after balanceQs()";
            debugNormalLog(oss.str(), false);
        }
    }

    int popFront() {
        int ele = -1;
        if (!q1.empty()) {
            ele = q1.front();
            q1.pop_front();
            if (debug) {
                oss.str("");
                oss << "after popFront() = " << ele;
                debugNormalLog(oss.str(), true);
            }

            balanceQs();
            if (debug) {
                oss.str("");
                oss << "after balanceQs()";
                debugNormalLog(oss.str(), false);
            }
        } else {
            if (debug) {
                oss.str("");
                oss << "skipping popFront() as q1 is empty";
                debugSkipLog(oss.str());
            }
        }

        return ele;
    }

    int popMiddle() {
        int ele = -1;
        if (!q1.empty()) {
            ele = q1.back();
            q1.pop_back();
            if (debug) {
                oss.str("");
                oss << "after popMiddle() = " << ele;
                debugNormalLog(oss.str(), true);
            }

            balanceQs();
            if (debug) {
                oss.str("");
                oss << "after balanceQs()";
                debugNormalLog(oss.str(), false);
            }
        } else {
            if (debug) {
                oss.str("");
                oss << "skipping popMiddle() as q1 is empty";
                debugSkipLog(oss.str());
            }
        }

        return ele;
    }

    int popBack() {
        int ele = -1;
        if (!q2.empty()) {
            ele = q2.back();
            q2.pop_back();
            if (debug) {
                oss.str("");
                oss << "after q2.popBack() = " << ele;
                debugNormalLog(oss.str(), true);
            }

            balanceQs();
            if (debug) {
                oss.str("");
                oss << "after balanceQs()";
                debugNormalLog(oss.str(), false);
            }
        } else if (!q1.empty()) {
            ele = q1.back();
            q1.pop_back();
            if (debug) {
                oss.str("");
                oss << "after q1.popBack() = " << ele;
                debugNormalLog(oss.str(), true);
            }

            balanceQs();
            if (debug) {
                oss.str("");
                oss << "after balanceQs()";
                debugNormalLog(oss.str(), false);
            }
        } else {
            if (debug) {
                oss.str("");
                oss << "skipping popBack() as both q1 & q2 are empty";
                debugSkipLog(oss.str());
            }
        }

        return ele;
    }
};

class FrontMiddleBackQueueTest {
public:
    void testFrontMiddleBackQueue() {
        FrontMiddleBackQueue fmbQ = FrontMiddleBackQueue();
        fmbQ.debug = true;

        fmbQ.pushFront(1);
        fmbQ.pushBack(2);

        fmbQ.pushMiddle(3);
        fmbQ.pushMiddle(4);

        fmbQ.popFront();
        fmbQ.popMiddle();
        fmbQ.popMiddle();
        fmbQ.popBack();
        fmbQ.popFront();
    }
};

int main() {
    FrontMiddleBackQueueTest fmbqTest = FrontMiddleBackQueueTest();
    fmbqTest.testFrontMiddleBackQueue();
    return 0;
}

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */
