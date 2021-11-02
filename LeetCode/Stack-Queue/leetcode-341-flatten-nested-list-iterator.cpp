// LeetCode-341: https://leetcode.com/problems/flatten-nested-list-iterator/

#include <climits>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
   public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
   private:
    stack<pair<vector<NestedInteger>, int> > stk;

   public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        this->stk.push({nestedList, 0});
    }

    int next() {
        pair<vector<NestedInteger>, int> top = this->stk.top();
        this->stk.pop();

        vector<NestedInteger> list = top.first;
        int len = list.size();
        int idx = top.second;

        if (idx >= len) {
            return this->next();
        }

        NestedInteger nextItem = list[idx++];
        if (idx < len) {
            this->stk.push({list, idx});
        }

        if (nextItem.isInteger()) {
            return nextItem.getInteger();
        } else {
            this->stk.push({nextItem.getList(), 0});
            return this->next();
        }
    }

    bool hasNext() {
        // check if stack empty
        if (this->stk.empty()) {
            return false;
        }

        // retrieve stack top
        pair<vector<NestedInteger>, int> top = this->stk.top();
        this->stk.pop();

        vector<NestedInteger> list = top.first;
        int len = list.size();
        int idx = top.second;

        // check if list in stack top empty
        if ((len == 0) || (idx >= len)) {
            // if yes, then recurse (check next item in stack)
            return this->hasNext();
        }

        // retrieve first item from list retrieved from stack
        NestedInteger nextItem = list[idx++];
        if (idx < len) {
            // push back list into stack
            this->stk.push({list, idx});
        }

        if (nextItem.isInteger()) {
            // if it is single integer
            // (1) push it back into stack (2) return true
            this->stk.push({{nextItem}, 0});
            return true;
        } else {
            // if it is yet another nested list
            // (1) push it back into stack (2) recurse
            this->stk.push({nextItem.getList(), 0});
            return this->hasNext();
        }
    }
};

/**
Your NestedIterator object will be instantiated and called as such:
NestedIterator i(nestedList);
while (i.hasNext()) cout << i.next();
 */
