// LeetCode-150: https://leetcode.com/problems/evaluate-reverse-polish-notation/
// Companies: [Amazon][Google][Meta][Citadel][tcs][Bloomberg][Microsoft][Grammarly][LinkedIn][Apple][Anduril][Apollo.io][Canonical][Infosys][Oracle][Goldman Sachs]

// Whoa: just adding 'const' keywords in a bunch of places (as suggested by CLion) improved
// LC submission runtime from 5 ms (5 %tile) to 1 ms (58 %tile)

#include <vector>
#include <unordered_set>
#include <string>
#include <stack>

using namespace std;

#define ADD_OP_STR "+"
#define SUBTRACT_OP_STR "-"
#define MULTIPLY_OP_STR "*"
#define DIVIDE_OP_STR "/"

enum MyOperator {
    Add,
    Subtract,
    Multiply,
    Divide,
    UNKNOWN
};

class Solution {
private:
    const unordered_set <string> operators = {
        ADD_OP_STR,
        SUBTRACT_OP_STR,
        MULTIPLY_OP_STR,
        DIVIDE_OP_STR
    };
    stack <int> myStack;

    // ----- helpers-1 : parsing helpers -----

    bool isOperator(const string& token) const {
        return operators.find(token) != operators.end();
    }

    MyOperator parseOperator(const string& oper) const {
        if (!isOperator(oper)) {
            return MyOperator::UNKNOWN;
        }

        if (oper == ADD_OP_STR) {
            return MyOperator::Add;
        } else if (oper == SUBTRACT_OP_STR) {
            return MyOperator::Subtract;
        } else if (oper == MULTIPLY_OP_STR) {
            return MyOperator::Multiply;
        } else if (oper == DIVIDE_OP_STR) {
            return MyOperator::Divide;
        } else {
            return MyOperator::UNKNOWN;
        }
    }

    // ----- helpers-2 : stack operations -----

    int retrieveOperand() {
        int operand = myStack.top();
        myStack.pop();
        return operand;
    }

    pair <int, int> retrieveOperands() {
        int secondOperand = retrieveOperand();
        int firstOperand = retrieveOperand();

        return {firstOperand, secondOperand};
    }

    // ----- helpers-3 : calculations -----

    void op(MyOperator oper) {
        switch (oper) {
            case MyOperator::Add:
                opAdd();
                break;

            case MyOperator::Subtract:
                opSubtract();
                break;

            case MyOperator::Multiply:
                opMultiply();
                break;

            case MyOperator::Divide:
                opDivide();
                break;

            default:
                // should throw an exception
                break;
        }
    }

    void opAdd() {
        pair <int, int> operands = retrieveOperands();
        int result = operands.first + operands.second;
        myStack.push(result);
    }

    void opSubtract() {
        pair <int, int> operands = retrieveOperands();
        int result = operands.first - operands.second;
        myStack.push(result);
    }

    void opMultiply() {
        pair <int, int> operands = retrieveOperands();
        int result = operands.first * operands.second;
        myStack.push(result);
    }

    void opDivide() {
        pair <int, int> operands = retrieveOperands();
        int result = operands.first / operands.second;
        myStack.push(result);
    }

public:
    int evalRPN(const vector<string>& tokens) {
        for (const string& token : tokens) {
            MyOperator oper = parseOperator(token);

            if (oper == MyOperator::UNKNOWN) {
                int operand = stoi(token);
                myStack.push(operand);
            } else {
                op(oper);
            }
        }

        return myStack.top();
    }
};
