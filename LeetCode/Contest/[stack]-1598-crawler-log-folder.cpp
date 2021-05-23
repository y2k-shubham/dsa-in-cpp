// weekly contest 208: https://leetcode.com/contest/weekly-contest-208/problems/crawler-log-folder/

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
    const int TYPE_NOOP = 0;
    const int TYPE_CHILD = 1;
    const int TYPE_PARENT = 2;
    const string DIR_ROOT = "root/";

   private:
    stack<string> dirStack;

    void initStack() {
        this->dirStack.push(DIR_ROOT);
    }

    int decipherOpType(string op) {
        if (op == "./") {
            return TYPE_NOOP;
        } else if (op == "../") {
            return TYPE_PARENT;
        } else {
            return TYPE_CHILD;
        }
    }

    void performOp(string op) {
        int opType = decipherOpType(op);
        switch (opType) {
            case 0:
                break;

            case 1:
                this->dirStack.push(op);
                break;

            case 2:
                if (this->dirStack.size() > 1) {
                    this->dirStack.pop();
                } else {
                    // illegal
                }
                break;

            default:
                // illegal
                break;
        }
    }

   public:
    int minOperations(vector<string>& logs) {
        initStack();

        for (int i = 0; i < logs.size(); i++) {
            string op = logs[i];
            performOp(op);
        }

        return ((int)this->dirStack.size()) - 1;
    }
};
