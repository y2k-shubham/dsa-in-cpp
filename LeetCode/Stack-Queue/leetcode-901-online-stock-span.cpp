// LeetCode-901: https://leetcode.com/problems/online-stock-span/

#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class StockSpanner {
   private:
    int maxLen = 10001;
    int crrLen;
    vector<int> vec;
    vector<int> ngeLeft;
    stack<int> stk;

    void calcNgeLeft() {
        int crrIdx = this->crrLen - 1;
        int crrEle = this->vec[crrIdx];

        while (!this->stk.empty() && (this->vec[this->stk.top()] <= crrEle)) {
            // printf("i ran %d\n", crrEle);
            this->stk.pop();
        }

        if (this->stk.empty()) {
            this->ngeLeft[crrIdx] = -1;
        } else {
            this->ngeLeft[crrIdx] = this->stk.top();
        }

        this->stk.push(crrIdx);
    }

   public:
    StockSpanner() {
        this->crrLen = 0;

        vector<int> vec(this->maxLen, 0);
        this->vec = vec;

        vector<int> ngeLeft(this->maxLen, INT_MAX);
        this->ngeLeft = ngeLeft;
    }

    int next(int price) {
        this->vec[this->crrLen++] = price;
        int crrIdx = this->crrLen - 1;

        this->calcNgeLeft();

        return crrIdx - this->ngeLeft[crrIdx];
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
