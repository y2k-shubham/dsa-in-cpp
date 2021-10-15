// LeetCode-1472: https://leetcode.com/problems/design-browser-history/

#include <cstdio>
#include <iostream>
#include <list>

using namespace std;

class BrowserHistory {
   private:
    list<string> backHistory;  // we push back / pop back in it
    list<string> fwdHistory;   // we push front / pop front in it (or reset it)

   public:
    BrowserHistory(string homepage) {
        this->backHistory.push_back(homepage);
    }

    void visit(string url) {
        this->backHistory.push_back(url);
        this->fwdHistory.clear();
    }

    string back(int steps) {
        for (int i = 1; (this->backHistory.size() > 1) && (i <= steps); i++) {
            string crrPage = this->backHistory.back();
            this->backHistory.pop_back();
            this->fwdHistory.push_front(crrPage);
        }

        return this->backHistory.back();
    }

    string forward(int steps) {
        for (int i = 1; (!this->fwdHistory.empty()) && (i <= steps); i++) {
            string nextPage = this->fwdHistory.front();
            this->fwdHistory.pop_front();
            this->backHistory.push_back(nextPage);
        }

        return this->backHistory.back();
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
